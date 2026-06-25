#!/usr/bin/env python3
"""
FTDI JTAG Programmer for Xilinx Artix-7 (XC7A35T on Basys3 board)

Programs the FPGA via JTAG using FT2232H Channel A in MPSSE mode
through the ftd2xx Python library.

JTAG Pin Mapping (ADBUS):
  ADBUS0 = TCK
  ADBUS1 = TDI
  ADBUS2 = TDO (input)
  ADBUS3 = TMS

XC7A35T IR length = 6 bits
CFG_IN  instruction = 0b00101
JSTART  instruction = 0b01111

Usage:
  python ftdi_jtag_prog.py <bitstream.bit>
  python ftdi_jtag_prog.py  (uses default path)
"""

import sys
import os
import struct
import time

try:
    import ftd2xx as ftd
except ImportError:
    print("ftd2xx not installed. Install with: pip install ftd2xx")
    sys.exit(1)

# ============================================================
# Configuration
# ============================================================
FTDI_SERIAL_A = "210183A8AC3DA"  # Channel A serial number
IR_LENGTH = 6                     # XC7A35T IR length
# TCK = 12MHz / ((1 + div) * 2).  div=0x0059 => ~5.04 MHz
MPSSE_CLOCK_DIV = 0x0059

# JTAG pin definitions on ADBUS
PIN_TCK = 0  # ADBUS0
PIN_TDI = 1  # ADBUS1
PIN_TDO = 2  # ADBUS2 (input)
PIN_TMS = 3  # ADBUS3

# Direction: 1=output, 0=input
# TCK=out, TDI=out, TDO=in, TMS=out
MPSSE_LOW_DIR = (1 << PIN_TCK) | (1 << PIN_TDI) | (1 << PIN_TMS)
MPSSE_LOW_VAL = 0  # All low initially

# Xilinx JTAG instructions for XC7A35T
# IR values are what you load (LSB-first on the wire)
IR_CFG_IN = 0b00101   # CFG_IN
IR_JSTART = 0b01111   # JSTART
IR_BYPASS = 0b111111  # BYPASS
IR_IDCODE = 0b001001  # IDCODE

# Default bitstream path
DEFAULT_BITSTREAM = (
    r"G:\GitHub\26-Arch\vivado\test-cpu\project\project_3"
    r"\project_3.runs\impl_1\basys3_top.bit"
)

# ============================================================
# MPSSE opcodes
# ============================================================
# Clock data bytes out on -ve TCK edge, MSB first (TDI only, no read)
MPSSE_CLK_BYTES_OUT_NEG_MSB = 0x19
# Clock data bits out on -ve TCK edge, MSB first (TDI only, no read)
MPSSE_CLK_BITS_OUT_NEG_MSB = 0x1B
# Clock data bytes out on -ve edge, in on +ve edge, MSB first
MPSSE_CLK_BYTES_RW_NEG_MSB = 0x24
# Clock data bits out on -ve edge, in on +ve edge, MSB first
MPSSE_CLK_BITS_RW_NEG_MSB = 0x3E
# Clock TMS bits out on +ve edge, LSB first
MPSSE_CLK_TMS_OUT_POS_LSB = 0x4B

MPSSE_SEND_IMMEDIATE = 0x87
MPSSE_DISABLE_LOOPBACK = 0x85
MPSSE_SET_LOW_DIRVAL = 0x80
MPSSE_SET_HIGH_DIRVAL = 0x82
MPSSE_SET_CLK_DIV = 0x86


# ============================================================
# Helpers
# ============================================================
def _bit_reverse_byte(b):
    """Reverse bits in a single byte."""
    # Fast lookup-free version
    b = ((b & 0xF0) >> 4) | ((b & 0x0F) << 4)
    b = ((b & 0xCC) >> 2) | ((b & 0x33) << 2)
    b = ((b & 0xAA) >> 1) | ((b & 0x55) << 1)
    return b


# ============================================================
# JTAG State Machine – TMS transition helpers
# ============================================================
def _tms_cmd(tms_bits, count):
    """Build MPSSE TMS-shift command.

    tms_bits: LSB-first TMS pattern (bit0 is shifted first).
    count:    number of TMS bits to shift (1..8 per call).

    Returns bytearray of MPSSE commands.
    """
    assert 1 <= count <= 8
    cmds = bytearray()
    cmds.append(MPSSE_CLK_TMS_OUT_POS_LSB)
    cmds.append(count - 1)          # length-1
    cmds.append(tms_bits & 0xFF)    # TMS data byte (LSB = first TMS bit)
    return cmds


def jtag_reset():
    """5× TMS=1 then TMS=0 → Test-Logic-Reset → Run-Test/Idle."""
    cmds = bytearray()
    # 5 TMS=1 → any state to TLReset
    cmds.extend(_tms_cmd(0b11111, 5))
    # 1 TMS=0 → Run-Test/Idle
    cmds.extend(_tms_cmd(0b0, 1))
    return cmds


def jtag_run_idle_clocks(n):
    """Clock n cycles in Run-Test/Idle (TMS=0 each cycle)."""
    cmds = bytearray()
    while n > 0:
        chunk = min(n, 8)
        cmds.extend(_tms_cmd(0b0, chunk))
        n -= chunk
    return cmds


# ============================================================
# FTDI / MPSSE JTAG Interface
# ============================================================
class FtdiJtag:
    """FTDI JTAG interface using MPSSE mode on Channel A of FT2232H."""

    def __init__(self):
        self.dev = None

    # ---- device open / close ----

    def open(self, serial=None):
        """Open FTDI Channel A by serial number and configure MPSSE."""
        self.dev = self._find_and_open(serial)

        # Reset
        self.dev.resetDevice()
        self.dev.purge()
        self.dev.setEventNotification(0, 0)
        self.dev.setChars(0, 0, 0, 0)
        self.dev.setTimeouts(5000, 5000)
        self.dev.setLatencyTimer(2)

        # Enter MPSSE mode
        self.dev.setBitMode(0x00, 0x00)   # reset first
        time.sleep(0.05)
        self.dev.setBitMode(0x00, 0x02)   # MPSSE
        time.sleep(0.05)

        # MPSSE initial config
        self._configure_mpsse()

        # Bring JTAG to known state
        self._jtag_reset()
        print("[FTDI] Device opened and configured for MPSSE JTAG")

    def _find_and_open(self, serial):
        """Locate and open the FTDI device for Channel A."""
        num = ftd.createDeviceInfoList()
        for i in range(num):
            info = ftd.getDeviceInfoDetail(i)
            sn = info.get('serial', '') or ''
            # Channel A serial ends with 'A'
            if sn == serial or (serial and sn == serial):
                dev = ftd.open(i)
                print(f"[FTDI] Opened device index {i}, serial={sn}")
                return dev
        # Fallback: open by serial string directly
        if serial:
            try:
                dev = ftd.openEx(serial.encode() if isinstance(serial, str) else serial)
                print(f"[FTDI] Opened device by serial: {serial}")
                return dev
            except Exception as e:
                print(f"[FTDI] openEx failed: {e}")
        # Last resort
        print("[FTDI] Opening first available device...")
        return ftd.open(0)

    def _configure_mpsse(self):
        """Initial MPSSE configuration commands."""
        cmds = bytearray()
        cmds.append(MPSSE_DISABLE_LOOPBACK)
        # Clock divisor
        cmds.append(MPSSE_SET_CLK_DIV)
        cmds.append(MPSSE_CLOCK_DIV & 0xFF)
        cmds.append((MPSSE_CLOCK_DIV >> 8) & 0xFF)
        # ADBUS direction & value
        cmds.append(MPSSE_SET_LOW_DIRVAL)
        cmds.append(MPSSE_LOW_VAL)
        cmds.append(MPSSE_LOW_DIR)
        # ACBUS – unused, all input
        cmds.append(MPSSE_SET_HIGH_DIRVAL)
        cmds.append(0x00)
        cmds.append(0x00)
        self.dev.write(bytes(cmds))
        time.sleep(0.05)

    def close(self):
        if self.dev:
            try:
                self._jtag_reset()
                self.dev.setBitMode(0x00, 0x00)
                self.dev.close()
            except Exception:
                pass
            self.dev = None
            print("[FTDI] Device closed")

    # ---- low-level I/O ----

    def _write(self, data):
        self.dev.write(bytes(data))

    def _write_read(self, data, rdlen):
        self.dev.write(bytes(data))
        self.dev.write(bytes([MPSSE_SEND_IMMEDIATE]))
        return self.dev.read(rdlen)

    # ---- JTAG state machine ----

    def _jtag_reset(self):
        """Reset JTAG TAP and go to Run-Test/Idle."""
        self._write(jtag_reset())

    def _goto_shift_ir(self):
        """Run-Test/Idle → Shift-IR.
        TMS: 1 (Select-DR-Scan), 1 (Select-IR-Scan), 0 (Capture-IR), 0 (Shift-IR)
        """
        self._write(_tms_cmd(0b0011, 4))

    def _goto_shift_dr(self):
        """Run-Test/Idle → Shift-DR.
        TMS: 1 (Select-DR-Scan), 0 (Capture-DR), 0 (Shift-DR)
        """
        self._write(_tms_cmd(0b001, 3))

    def _exit_shift_to_idle(self):
        """Shift-IR/DR → Run-Test/Idle.
        TMS: 1 (Exit1), 1 (Update), 0 (Run-Test/Idle)
        Wait – from Shift-XR:
          TMS=1 → Exit1-XR
          TMS=1 → Update-XR
          TMS=0 → Run-Test/Idle
        """
        self._write(_tms_cmd(0b011, 3))

    # ---- IR / DR shift ----

    def shift_ir(self, ir_value, ir_length=IR_LENGTH):
        """Shift instruction register.

        ir_value: instruction value, LSB-first on the wire.
            e.g. CFG_IN = 0b00101 means bit0=1, bit1=0, bit2=1, bit3=0, bit4=0
        ir_length: total bits (6 for XC7A35T).

        Procedure:
          1. Go to Shift-IR.
          2. Shift (ir_length-1) bits with TMS=0 (stay in Shift-IR).
          3. Shift last bit with TMS=1 (exit to Exit1-IR).
          4. TMS=1 → Update-IR, TMS=0 → Run-Test/Idle.

        For MPSSE MSB-first byte/bit commands, bit7 is clocked out first.
        JTAG shifts LSB first, so we bit-reverse each byte.
        """
        self._goto_shift_ir()

        # We will shift (ir_length-1) bits with TMS=0, then 1 bit with TMS=1.
        # Build the TDI data: ir_value bits, LSB first.
        # We need to send (ir_length-1) bits staying in Shift-IR, then
        # the last bit while exiting.

        # Strategy: use byte-write for the first (ir_length-1) bits,
        # then handle the exit bit separately.

        # For a 6-bit IR, we shift 5 bits (TMS=0) then 1 bit (TMS=1).
        # 5 bits fits in one MPSSE bit command.

        bits_before_exit = ir_length - 1  # bits to shift with TMS=0

        if bits_before_exit >= 8:
            # Need byte writes for the bulk
            full_bytes = bits_before_exit // 8
            remainder_bits = bits_before_exit % 8

            # Prepare TDI data: ir_value, LSB-first → bit-reverse each byte
            # for MPSSE MSB-first command.
            for b_idx in range(full_bytes):
                byte_val = (ir_value >> (b_idx * 8)) & 0xFF
                rev = _bit_reverse_byte(byte_val)
                self._write(bytes([
                    MPSSE_CLK_BYTES_OUT_NEG_MSB,
                    0, 0,   # 1 byte (length-1 in L/H)
                    rev
                ]))

            if remainder_bits > 0:
                # Shift remainder_bits from ir_value
                remaining_val = (ir_value >> (full_bytes * 8)) & ((1 << remainder_bits) - 1)
                # MPSSE bit command: bit7 is clocked first (MSB first).
                # We want LSB of remaining_val first on the wire.
                # So place LSB at bit7 position, next at bit6, etc.
                shifted = 0
                for i in range(remainder_bits):
                    if remaining_val & (1 << i):
                        shifted |= 1 << (7 - i)
                self._write(bytes([
                    MPSSE_CLK_BITS_OUT_NEG_MSB,
                    remainder_bits - 1,
                    shifted & 0xFF
                ]))
        else:
            # All (ir_length-1) bits fit in one bit command
            if bits_before_exit > 0:
                mask = (1 << bits_before_exit) - 1
                val = ir_value & mask
                shifted = 0
                for i in range(bits_before_exit):
                    if val & (1 << i):
                        shifted |= 1 << (7 - i)
                self._write(bytes([
                    MPSSE_CLK_BITS_OUT_NEG_MSB,
                    bits_before_exit - 1,
                    shifted & 0xFF
                ]))

        # Last bit: shift with TMS=1 to exit Shift-IR
        last_bit = (ir_value >> (ir_length - 1)) & 1

        # Set TDI pin to last_bit value, then clock TMS=1
        # MPSSE TMS command clocks TMS but uses the current TDI pin state.
        # So we set TDI via the GPIO command first.
        tdi_val = (last_bit << PIN_TDI)
        self._write(bytes([
            MPSSE_SET_LOW_DIRVAL,
            tdi_val,          # ADBUS value: TDI=last_bit, TCK=0, TMS=0
            MPSSE_LOW_DIR
        ]))

        # Clock 1 TMS=1 (exits Shift-IR → Exit1-IR)
        self._write(_tms_cmd(0b1, 1))

        # Exit1-IR → Update-IR → Run-Test/Idle: TMS=1, TMS=0
        self._write(_tms_cmd(0b01, 2))

        # Reset TDI to 0
        self._write(bytes([
            MPSSE_SET_LOW_DIRVAL,
            0x00,
            MPSSE_LOW_DIR
        ]))

    def shift_dr(self, data_bytes):
        """Shift bitstream data into DR.

        data_bytes: raw bitstream bytes (MSB-first per byte, as in .bit file).
        The data is shifted MSB-first per byte, which matches the Xilinx
        bitstream format directly. MPSSE MSB-first byte command sends
        bit7 first, which is correct.

        Procedure:
          1. Go to Shift-DR.
          2. Shift all bytes except last with TMS=0.
          3. For last byte: shift 7 bits TMS=0, then 1 bit TMS=1 (exit).
          4. TMS=1 → Update-DR, TMS=0 → Run-Test/Idle.
        """
        self._goto_shift_dr()

        total_len = len(data_bytes)
        if total_len == 0:
            self._exit_shift_to_idle()
            return

        # Process in chunks to stay within FTDI 4KB buffer
        CHUNK = 3800
        offset = 0

        while offset < total_len:
            end = min(offset + CHUNK, total_len)
            chunk = data_bytes[offset:end]
            is_last = (end >= total_len)

            if is_last and len(chunk) > 1:
                # Bulk bytes (all except last) – TMS stays 0
                bulk = chunk[:-1]
                self._shift_dr_bulk(bulk)

                # Last byte: 7 bits TMS=0, then exit
                last_byte = chunk[-1]
                self._shift_dr_last_byte(last_byte)

            elif is_last and len(chunk) == 1:
                self._shift_dr_last_byte(chunk[0])

            else:
                # Middle chunk – all bytes TMS=0
                self._shift_dr_bulk(chunk)

            offset = end

    def _shift_dr_bulk(self, data):
        """Shift a block of bytes into DR with TMS=0 (stay in Shift-DR)."""
        # MPSSE_CLK_BYTES_OUT_NEG_MSB sends bit7 first (MSB first),
        # which matches Xilinx bitstream byte order.
        off = 0
        while off < len(data):
            sub = data[off:off + 65536]
            n = len(sub) - 1
            cmd = bytearray()
            cmd.append(MPSSE_CLK_BYTES_OUT_NEG_MSB)
            cmd.append(n & 0xFF)
            cmd.append((n >> 8) & 0xFF)
            cmd.extend(sub)
            self._write(bytes(cmd))
            off += 65536

    def _shift_dr_last_byte(self, last_byte):
        """Shift the final byte of DR: 7 bits TMS=0, then 1 bit TMS=1 (exit)."""
        # 7 bits with TMS=0: bits [7:1] of last_byte, MSB first
        # MPSSE bit command: bit7 is clocked first.
        # We want bits 7,6,5,4,3,2,1 in that order → already in the
        # top 7 bits of the byte, just mask out bit 0.
        bits7 = last_byte & 0xFE   # bits 7..1, bit0=0
        self._write(bytes([
            MPSSE_CLK_BITS_OUT_NEG_MSB,
            6,       # 7 bits (N-1)
            bits7
        ]))

        # Last bit (bit 0) with TMS=1 to exit Shift-DR
        last_bit = last_byte & 1
        tdi_val = (last_bit << PIN_TDI)
        self._write(bytes([
            MPSSE_SET_LOW_DIRVAL,
            tdi_val,
            MPSSE_LOW_DIR
        ]))
        # Clock TMS=1
        self._write(_tms_cmd(0b1, 1))

        # Exit1-DR → Update-DR → Run-Test/Idle
        self._write(_tms_cmd(0b01, 2))

        # Reset TDI
        self._write(bytes([
            MPSSE_SET_LOW_DIRVAL,
            0x00,
            MPSSE_LOW_DIR
        ]))

    def shift_dr_read(self, num_bits):
        """Shift DR and read TDO. Used for IDCODE etc.

        Shifts (num_bits-1) bits with TMS=0, then 1 bit with TMS=1.
        Returns bytes of TDO data (MSB first per byte).
        """
        self._goto_shift_dr()

        num_bytes = (num_bits + 7) // 8
        bits_before_exit = num_bits - 1

        cmds = bytearray()

        # Shift (num_bits-1) bits, reading TDO, TMS=0
        if bits_before_exit >= 8:
            full_bytes = bits_before_exit // 8
            remainder = bits_before_exit % 8

            if full_bytes > 0:
                cmds.append(MPSSE_CLK_BYTES_RW_NEG_MSB)
                cmds.append((full_bytes - 1) & 0xFF)
                cmds.append(((full_bytes - 1) >> 8) & 0xFF)
                cmds.extend([0xFF] * full_bytes)  # dummy TDI

            if remainder > 0:
                cmds.append(MPSSE_CLK_BITS_RW_NEG_MSB)
                cmds.append(remainder - 1)
                cmds.append(0xFF)  # dummy TDI
        elif bits_before_exit > 0:
            cmds.append(MPSSE_CLK_BITS_RW_NEG_MSB)
            cmds.append(bits_before_exit - 1)
            cmds.append(0xFF)

        # Last bit: TMS=1 to exit.  Set TDI=1 (dummy), clock TMS.
        cmds.append(MPSSE_SET_LOW_DIRVAL)
        cmds.append(1 << PIN_TDI)
        cmds.append(MPSSE_LOW_DIR)

        cmds.extend(_tms_cmd(0b1, 1))

        # Exit1-DR → Update-DR → Run-Test/Idle
        cmds.extend(_tms_cmd(0b01, 2))

        cmds.append(MPSSE_SET_LOW_DIRVAL)
        cmds.append(0x00)
        cmds.append(MPSSE_LOW_DIR)

        result = self._write_read(bytes(cmds), num_bytes)
        return result

    def run_test_idle(self, n):
        """Clock n cycles in Run-Test/Idle."""
        self._write(jtag_run_idle_clocks(n))


# ============================================================
# .bit file parser
# ============================================================
def parse_bit_file(filepath):
    """Parse Xilinx .bit file and extract bitstream data.

    .bit file format:
      - 2-byte big-endian header length + header data
      - Field 'a': design name (2-byte BE length + string)
      - Field 'b': part name
      - Field 'c': date
      - Field 'd': time
      - Field 'e': bitstream (4-byte BE length + raw data)

    Returns (design_name, part_name, date, time, bitstream_bytes).
    """
    with open(filepath, 'rb') as f:
        data = f.read()

    offset = 0

    # Header: variable-length padding with 0x0FF0 patterns
    # Skip until we find field 'a' (0x61)
    # Standard format: 00 09 <9 bytes> 00 00 01 61 ...
    # Some .bit files have: 00 0D <13 bytes> 61 ...
    while offset < len(data) - 1:
        if data[offset] == ord('a') and offset > 0:
            # Found field 'a', don't skip it
            break
        # Try reading as header
        if offset == 0:
            hdr_len = struct.unpack('>H', data[0:2])[0]
            offset = 2 + hdr_len
            # Skip any padding bytes (0x00) before field 'a'
            while offset < len(data) and data[offset] != ord('a'):
                offset += 1
            break
        else:
            offset += 1

    design_name = part_name = date_str = time_str = ""
    bitstream = b""

    while offset < len(data):
        fid = data[offset]
        offset += 1

        if fid == ord('e'):
            blen = struct.unpack('>I', data[offset:offset + 4])[0]
            offset += 4
            bitstream = data[offset:offset + blen]
            offset += blen
            break
        elif fid in (ord('a'), ord('b'), ord('c'), ord('d')):
            flen = struct.unpack('>H', data[offset:offset + 2])[0]
            offset += 2
            fdata = data[offset:offset + flen].decode('ascii', errors='replace')
            offset += flen
            if fid == ord('a'):
                design_name = fdata
            elif fid == ord('b'):
                part_name = fdata
            elif fid == ord('c'):
                date_str = fdata
            elif fid == ord('d'):
                time_str = fdata
        else:
            # Unknown field - skip
            offset += 1

    return design_name, part_name, date_str, time_str, bitstream


# ============================================================
# FPGA programming sequence
# ============================================================
def program_fpga(jtag, bitstream):
    """Standard Xilinx JTAG programming sequence for 7-series.

    1. JTAG reset → Run-Test/Idle
    2. IR ← CFG_IN
    3. DR ← bitstream data
    4. Run-Test/Idle (100 TCK)
    5. IR ← JSTART
    6. Run-Test/Idle (2000 TCK) — starts the FPGA
    7. Additional startup clocks (2000 TCK)
    """
    print(f"[JTAG] Bitstream size: {len(bitstream)} bytes")

    # Step 1
    jtag._jtag_reset()
    print("[JTAG] State: Run-Test/Idle")

    # Step 2 – CFG_IN
    print(f"[JTAG] IR ← CFG_IN (0b{IR_CFG_IN:06b})")
    jtag.shift_ir(IR_CFG_IN)

    # Step 3 – shift bitstream
    print("[JTAG] Shifting bitstream into DR ...")
    t0 = time.time()
    jtag.shift_dr(bitstream)
    dt = time.time() - t0
    print(f"[JTAG] Bitstream shifted in {dt:.1f}s "
          f"({len(bitstream) / dt / 1024:.1f} KB/s)")

    # Step 4
    print("[JTAG] Run-Test/Idle 100 TCK")
    jtag.run_test_idle(100)

    # Step 5 – JSTART
    print(f"[JTAG] IR ← JSTART (0b{IR_JSTART:06b})")
    jtag.shift_ir(IR_JSTART)

    # Step 6 – start the FPGA
    print("[JTAG] JSTART: 2000 TCK in Run-Test/Idle")
    jtag.run_test_idle(2000)

    # Step 7 – additional startup
    print("[JTAG] Additional 2000 startup TCK")
    jtag.run_test_idle(2000)

    print("[JTAG] Programming sequence complete!")


def check_idcode(jtag):
    """Read IDCODE to verify JTAG communication."""
    jtag._jtag_reset()
    jtag.shift_ir(IR_IDCODE)
    raw = jtag.shift_dr_read(32)
    if raw and len(raw) >= 4:
        idcode = struct.unpack('>I', raw)[0]
        print(f"[JTAG] IDCODE: 0x{idcode:08X}")
        if idcode == 0x0362D093:
            print("[JTAG] IDCODE matches XC7A35T")
            return True
        else:
            print(f"[JTAG] IDCODE mismatch (expected 0x0362D093)")
            return False
    else:
        print("[JTAG] Could not read IDCODE")
        return False


# ============================================================
# Main
# ============================================================
def main():
    print("=" * 60)
    print("FTDI JTAG Programmer for Xilinx Artix-7 (XC7A35T)")
    print("FT2232H Channel A – MPSSE mode")
    print("=" * 60)

    # Bit file
    bit_file = sys.argv[1] if len(sys.argv) > 1 else DEFAULT_BITSTREAM
    if not os.path.exists(bit_file):
        print(f"[ERROR] Bitstream not found: {bit_file}")
        print(f"Usage: python {sys.argv[0]} <bitstream.bit>")
        sys.exit(1)

    # Parse .bit
    print(f"\n[BIT] Reading: {bit_file}")
    design, part, date, tm, bs = parse_bit_file(bit_file)
    if not bs:
        print("[ERROR] No bitstream data in .bit file!")
        sys.exit(1)
    print(f"[BIT] Design : {design}")
    print(f"[BIT] Part   : {part}")
    print(f"[BIT] Date   : {date} {tm}")
    print(f"[BIT] Size   : {len(bs)} bytes")

    # Open FTDI
    jtag = FtdiJtag()
    try:
        jtag.open(FTDI_SERIAL_A)

        # Verify JTAG link
        print("\n[JTAG] Verifying JTAG connection ...")
        idcode_ok = check_idcode(jtag)
        if not idcode_ok:
            print("[JTAG] IDCODE check failed - continuing anyway (MPSSE pin mapping may differ)")
            # Don't exit - try programming anyway

        # Program
        print("\n[JTAG] Starting FPGA programming ...")
        jtag._jtag_reset()
        program_fpga(jtag, bs)

        # Post-check
        print()
        check_idcode(jtag)
        print("[JTAG] Programming done. Check DONE LED on Basys3 board.")

    except Exception as e:
        print(f"\n[ERROR] {e}")
        import traceback
        traceback.print_exc()
        sys.exit(1)
    finally:
        jtag.close()

    print("\nDone!")


if __name__ == "__main__":
    main()
