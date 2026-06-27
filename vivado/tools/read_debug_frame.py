#!/usr/bin/env python3
"""
Read and parse hardware auto-debug frames from Basys3 FPGA via FTDI Channel B.

The FPGA sends a 32-byte debug frame every ~8.9s automatically (independent
of CPU). This script listens for frames, syncs on the 5 markers
(0xAA...0x55...0x33...0xCC...0x0A), and decodes the hardware state.
Frame focuses on SPI Flash disk diagnosis + CPU write activity.

Frame format (32 bytes):
  [0]  0xAA  sync marker 1
  [1]  status1: {ever_uart_write, ever_thr_write, ever_device_read,
                 lsr_read, tx_state_rdy, fifo_nonempty, txState[1:0]}
  [2]  last_read_addr[31:24]
  [3]  last_read_addr[23:16]
  [4]  last_read_addr[15:8]
  [5]  last_read_addr[7:0]
  [6]  last_read_rdata[7:0]   (CPU read data low byte)
  [7]  last_read_rdata[15:8]  (CPU read data byte 1 — detect 0x00 disk data)
  [8]  0x55  sync marker 2
  [9]  {spi_state[3:0], data_ready_cnt[3:0]}
  [10] data_ready_cnt[11:4]
  [11] flash_addr[22:16]      (expect 0x30 = SPI offset 0x300000)
  [12] flash_addr[15:8]
  [13] flash_addr[7:0]
  [14] disk_blockno[7:0]      (CPU-written block number low)
  [15] disk_blockno[15:8]
  [16] 0x33  sync marker 3
  [17] txn_fire_cnt[7:0]
  [18] txn_fire_cnt[15:8]
  [19] {6'd0, txn_fire_cnt[17:16]}
  [20] dbg_disk_hits[7:0]
  [21] spi_byte_cnt[7:0]     (SPI bytes read this sector)
  [22] 0xF0  end marker
  [23] {4'b0, spi_data_ready, disk_read_pending, spi_req_valid, disk_rdy}
  [24] 0xCC  sync marker 4
  [25] last_write_addr[31:24] (last CPU WRITE addr — kernel progress)
  [26] last_write_addr[23:16]
  [27] last_write_addr[15:8]
  [28] last_write_addr[7:0]
  [29] uart_hits[7:0]         (UART register access count)
  [30] clint_hits[7:0]        (CLINT mtime access count)
  [31] 0x0A  end marker 2

Usage: python read_debug_frame.py [duration_seconds]
"""
import sys
import time
import ftd2xx

SPI_STATE_NAMES = {0: 'S_IDLE', 1: 'S_CMD', 2: 'S_ADDR', 4: 'S_READ', 5: 'S_DONE'}


def parse_frame(frame):
    """Parse a 32-byte debug frame and print decoded info."""
    if len(frame) != 32:
        print(f"  [!] Bad frame length: {len(frame)}")
        return

    b = list(frame)

    # Validate markers (5 markers for robust sync)
    if b[0] != 0xAA or b[8] != 0x55 or b[16] != 0x33 or b[22] != 0xF0 or b[24] != 0xCC or b[31] != 0x0A:
        print(f"  [!] Marker mismatch: [{b[0]:02x}]...[{b[8]:02x}]...[{b[16]:02x}]...[{b[22]:02x}]...[{b[24]:02x}]...[{b[31]:02x}]")
        return

    # Byte 1: status bits
    status = b[1]
    ever_uart_write  = (status >> 7) & 1
    ever_thr_write   = (status >> 6) & 1
    ever_device_read = (status >> 5) & 1
    lsr_read         = (status >> 4) & 1
    tx_state_rdy     = (status >> 3) & 1
    tx_fifo_nonempty = (status >> 2) & 1
    tx_state         = status & 0x3

    # Bytes 2-5: full 32-bit last READ address
    full_read_addr = (b[2] << 24) | (b[3] << 16) | (b[4] << 8) | b[5]

    # Bytes 6-7: CPU read rdata low 16 bits
    rdata_low16 = b[6] | (b[7] << 8)

    # Byte 9-10: SPI state + data_ready_cnt (12 bits)
    spi_state = (b[9] >> 4) & 0xF
    data_ready_cnt = (b[9] & 0xF) | (b[10] << 4)

    # Bytes 11-13: flash_addr (23 bits, but we read 24 and mask)
    flash_addr = (b[11] << 16) | (b[12] << 8) | b[13]
    flash_addr &= 0x7FFFFF

    # Bytes 14-15: disk_blockno (16 bits)
    disk_blockno = b[14] | (b[15] << 8)

    # Bytes 17-19: txn_fire_cnt (18 bits)
    txn_cnt = b[17] | (b[18] << 8) | ((b[19] & 0x3) << 16)

    # Byte 20: disk hits
    disk_hits = b[20]

    # Byte 21: spi_byte_cnt
    spi_byte_cnt = b[21]

    # Byte 23: disk state bits
    disk_state = b[23]
    spi_data_ready    = (disk_state >> 3) & 1
    disk_read_pending = (disk_state >> 2) & 1
    spi_req_valid     = (disk_state >> 1) & 1
    disk_rdy          = disk_state & 1

    # Bytes 25-28: last CPU WRITE addr (kernel progress indicator)
    last_write_addr = (b[25] << 24) | (b[26] << 16) | (b[27] << 8) | b[28]

    # Byte 29: UART register access count (low 8 bits)
    uart_hits = b[29]

    # Byte 30: CLINT mtime access count (low 8 bits)
    clint_hits = b[30]

    print(f"  === HARDWARE DEBUG FRAME (32B) ===")
    print(f"  --- CPU reach ---")
    print(f"    ever_uart_write  = {ever_uart_write}  ({'YES' if ever_uart_write else 'NO'})")
    print(f"    ever_thr_write   = {ever_thr_write}  ({'YES wrote THR' if ever_thr_write else 'NO'})")
    print(f"    ever_device_read = {ever_device_read}  ({'YES' if ever_device_read else 'NO'})")
    print(f"    lsr_read         = {lsr_read}")
    print(f"    TX: txState={tx_state} rdy={tx_state_rdy} fifo_nonempty={tx_fifo_nonempty}")
    print(f"  --- LAST READ ---")
    print(f"    addr      = 0x{full_read_addr:08x}")
    a_hi = b[2]
    if a_hi == 0x10:
        if b[4] == 0x00:
            reg_names = ['THR/RHR', 'IER', 'FCR/ISR', 'LCR', 'MCR', 'LSR']
            rn = b[5]
            reg_name = reg_names[rn] if rn < len(reg_names) else f'?{rn}'
            print(f"      -> UART register: {reg_name} (0x100000{rn:02x})")
        elif b[4] == 0x01:
            if b[5] == 0x00:
                print(f"      -> DISK BLOCKNO (0x10001000)")
            elif b[5] == 0x08:
                print(f"      -> DISK STATUS (0x10001008)")
            else:
                print(f"      -> DISK data region (0x10001{b[5]:02x})")
        else:
            print(f"      -> Other 0x10xxxx region")
    elif a_hi == 0x80:
        print(f"      -> RAM region (0x80000000+)  CPU executing from RAM")
    elif a_hi == 0x38:
        print(f"      -> CLINT region (mtime)")
    elif a_hi == 0x00 and full_read_addr == 0:
        print(f"      -> addr=0x00000000 (TRAP LOOP at PC=0!)")
    print(f"    rdata[15:0] = 0x{rdata_low16:04x}  ({'ZERO - disk data empty!' if rdata_low16 == 0 else 'non-zero'})")

    print(f"  === SPI FLASH DISK ===")
    print(f"    SPI FSM state     = {spi_state} ({SPI_STATE_NAMES.get(spi_state, '???')})")
    print(f"    data_ready pulses = {data_ready_cnt}  ({'NO sector reads completed!' if data_ready_cnt == 0 else 'sectors read OK'})")
    print(f"    flash_addr        = 0x{flash_addr:06x}  ({'OK 0x30xxxx' if (flash_addr >> 16) == 0x30 else 'WRONG - not 0x30xxxx!'})")
    expected_flash = 0x300000 + (disk_blockno * 1024)
    print(f"    expected          = 0x{expected_flash:06x}  (block {disk_blockno} * 1024 + 0x300000)")
    print(f"    disk_blockno      = 0x{disk_blockno:04x} ({disk_blockno})")
    print(f"    spi_byte_cnt      = {spi_byte_cnt}  ({'0=idle' if spi_byte_cnt == 0 else 'reading...' if spi_byte_cnt < 4 else 'DONE' if spi_byte_cnt >= 4 else '?'})")
    print(f"  === DISK STATE ===")
    print(f"    disk_rdy          = {disk_rdy}  ({'READY' if disk_rdy else 'BUSY - waiting SPI'})")
    print(f"    spi_req_valid     = {spi_req_valid}  (SPI read request pulse)")
    print(f"    disk_read_pending = {disk_read_pending}  (BRAM read pending)")
    print(f"    spi_data_ready    = {spi_data_ready}  (SPI read completed)")
    print(f"  === COUNTERS ===")
    print(f"    txn_fire_cnt      = {txn_cnt} (0x{txn_cnt:x})")
    print(f"    DISK hits        = {disk_hits}  ({'accessing disk' if disk_hits > 0 else 'no disk access'})")
    print(f"    UART hits         = {uart_hits}  ({'console active' if uart_hits > 0 else 'NO UART access'})")
    print(f"    CLINT hits        = {clint_hits}  ({'timer interrupts ON' if clint_hits > 0 else 'NO timer activity'})")
    print(f"  === CPU WRITE (kernel progress) ===")
    print(f"    last_write_addr   = 0x{last_write_addr:08x}")
    w_hi = b[25]
    if w_hi == 0x10:
        if b[27] == 0x00:
            wreg_names = ['THR/RHR', 'IER', 'FCR/ISR', 'LCR', 'MCR', 'LSR']
            wrn = b[28]
            wreg_name = wreg_names[wrn] if wrn < len(wreg_names) else f'?{wrn}'
            print(f"      -> UART register write: {wreg_name} (0x100000{wrn:02x})")
        elif b[27] == 0x01:
            if b[28] == 0x00:
                print(f"      -> DISK BLOCKNO write (0x10001000) — kernel requesting disk read!")
            elif b[28] == 0x08:
                print(f"      -> DISK STATUS write (0x10001008)")
            else:
                print(f"      -> DISK data write (0x10001{b[28]:02x})")
        else:
            print(f"      -> Other 0x10xxxx write")
    elif w_hi == 0x80:
        print(f"      -> RAM write (0x80000000+) — kernel writing data to RAM")
    elif w_hi == 0x38:
        print(f"      -> CLINT write (mtimecmp)")
    elif w_hi == 0x00 and last_write_addr == 0:
        print(f"      -> NO writes yet (write_addr=0)")
    print(f"  Raw: {' '.join(f'{x:02x}' for x in b)}")


def main():
    duration = int(sys.argv[1]) if len(sys.argv) > 1 else 15
    print(f"=== FPGA Auto-Debug Frame Reader (32-byte) ===")
    print(f"Duration: {duration}s, Baud: 115200, 8N1")
    print(f"Listening for 0xAA...0x55...0x33...0xCC...0x0A frame markers...")

    n = ftd2xx.createDeviceInfoList()
    print(f"FTDI devices found: {n}")

    dev = ftd2xx.open(1)
    info = dev.getDeviceInfo()
    desc = info.get('description', b'?')
    if isinstance(desc, bytes):
        desc = desc.decode('ascii', errors='ignore')
    print(f"Opened device 1: {desc}")

    dev.resetDevice()
    dev.setBaudRate(115200)
    dev.setDataCharacteristics(8, 0, 0)
    dev.setFlowControl(0x0000, 0, 0)
    dev.setTimeouts(100, 100)
    dev.setLatencyTimer(2)
    dev.purge(1 | 2)
    print(f"FTDI ready. Listening for frames...\n")

    buf = bytearray()
    frames_found = 0
    t0 = time.time()

    while time.time() - t0 < duration:
        try:
            n = dev.getQueueStatus()
            if n and n > 0:
                data = dev.read(n)
                for b in data:
                    byte = b if isinstance(b, int) else ord(b)
                    buf.append(byte)

                # Try to find frame: 5 markers at 0, 8, 16, 22, 24, 31
                while len(buf) >= 32:
                    if (buf[0] == 0xAA and buf[8] == 0x55
                            and buf[16] == 0x33 and buf[22] == 0xF0
                            and buf[24] == 0xCC and buf[31] == 0x0A):
                        # Valid frame found!
                        frame = bytes(buf[:32])
                        frames_found += 1
                        print(f"\n[Frame #{frames_found} @ t={time.time()-t0:.2f}s]")
                        parse_frame(frame)
                        del buf[:32]
                    else:
                        # Shift by 1 byte, keep searching
                        del buf[0]
            else:
                time.sleep(0.005)
        except KeyboardInterrupt:
            print("\n[Interrupted]")
            break
        except Exception as e:
            print(f"\n[Read error: {e}]")
            time.sleep(0.5)

    dev.close()
    print(f"\n=== Summary: {frames_found} frames decoded in {duration}s ===")
    if frames_found == 0:
        print("No frames found. Possible causes:")
        print("  1. FPGA not powered / not programmed with debug build")
        print("  2. FTDI Channel B not connected / wrong device")
        print("  3. UART TX pin not wired to FTDI RX")
        print("  4. Baud rate mismatch (expected 115200)")
        print(f"  5. Raw bytes received: {list(buf[:32])}")


if __name__ == '__main__':
    main()
