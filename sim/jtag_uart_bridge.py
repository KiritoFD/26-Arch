#!/usr/bin/env python3
"""
JTAG UART Bridge - PC-side script for communicating with jtag_uart module
on a Xilinx Artix-7 FPGA (Basys3) via Vivado hw_server.

Uses BSCANE2 USER1 to read UART TX data and USER2 to send UART RX data.
Protocol: 9 bits per transfer [valid, data[7:0]]
"""

import subprocess
import sys
import os
import threading
import time
import queue

# ============================================================
# Configuration
# ============================================================
VIVADO_PATH = r"G:\Vivado\2018.3\bin\vivado.bat"
BITSTREAM   = r"G:\GitHub\26-Arch\vivado\test-cpu\project\project_3\project_3.runs\impl_1\basys3_top.bit"
DR_WIDTH    = 9  # 9-bit data register: [valid, data[7:0]]

# ============================================================
# Vivado TCL Interface
# ============================================================
class VivadoJTAG:
    """Manages Vivado TCL session for JTAG UART communication."""

    def __init__(self):
        self.process = None
        self._tcl_lock = threading.Lock()

    def start(self):
        """Launch Vivado in batch mode with TCL stdin/stdout."""
        print("[JTAG] Starting Vivado TCL session...")
        self.process = subprocess.Popen(
            [VIVADO_PATH, "-mode", "tcl"],
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            bufsize=0,
            text=True,
        )
        # Wait for Vivado to initialize
        print("[JTAG] Waiting for Vivado to initialize...")
        self._read_until("Vivado%")
        print("[JTAG] Vivado ready.")

    def _read_until(self, marker, timeout=60):
        """Read from Vivado stdout until marker is found."""
        buf = ""
        start = time.time()
        while True:
            ch = self.process.stdout.read(1)
            if ch:
                buf += ch
                if marker in buf:
                    return buf
            if time.time() - start > timeout:
                raise TimeoutError(f"Timeout waiting for '{marker}', got: {buf[-200:]}")

    def tcl(self, cmd, timeout=30):
        """Execute a TCL command and return the output."""
        with self._tcl_lock:
            self.process.stdin.write(cmd + "\n")
            self.process.stdin.flush()
            result = self._read_until("Vivado%", timeout=timeout)
            # Extract the response between the command echo and the next prompt
            lines = result.strip().split("\n")
            # Remove the command echo (first line) and the prompt (last line)
            if len(lines) > 2:
                return "\n".join(lines[1:-1]).strip()
            return ""

    def connect(self):
        """Connect to hw_server and open JTAG target."""
        print("[JTAG] Connecting to hardware server...")
        self.tcl("open_hw")
        self.tcl("connect_hw_server -url localhost:3121 -allow_non_jtag")
        self.tcl("open_hw_target")
        print("[JTAG] Connected to hardware target.")

        # Set the device (first FPGA device)
        devices = self.tcl("get_hw_devices")
        device_name = None
        for line in devices.split("\n"):
            line = line.strip()
            if "xc7a" in line.lower():
                device_name = line
                break
        if not device_name:
            # Fallback: use first device
            parts = devices.strip().split()
            if parts:
                device_name = parts[0]
        if device_name:
            self.tcl(f"current_hw_device [{device_name}]")
            print(f"[JTAG] Selected device: {device_name}")

        # Program the FPGA
        if os.path.exists(BITSTREAM):
            print(f"[JTAG] Programming FPGA with {BITSTREAM}...")
            self.tcl(f'set_property PROGRAM.FILE {{{BITSTREAM}}} [current_hw_device]')
            self.tcl("program_hw_devices")
            print("[JTAG] FPGA programmed.")
            time.sleep(1)  # Wait for FPGA to initialize
        else:
            print(f"[JTAG] WARNING: Bitstream not found at {BITSTREAM}, skipping programming.")

        # Create USER1 shift instruction (TX data read from FPGA)
        # USER1 IR code for BSCANE2 chain 1 on Artix-7 = 0b001001
        print("[JTAG] Creating USER1 shift instruction (TX read)...")
        self.tcl(
            "create_hw_jtag_shiftinst -shift_in -ir 0b001001 -dr 9 -name user1_tx [current_hw_device]"
        )

        # Create USER2 shift instruction (RX data write to FPGA)
        # USER2 IR code for BSCANE2 chain 2 on Artix-7 = 0b001010
        print("[JTAG] Creating USER2 shift instruction (RX write)...")
        self.tcl(
            "create_hw_jtag_shiftinst -shift_out -ir 0b001010 -dr 9 -name user2_rx [current_hw_device]"
        )

        print("[JTAG] JTAG shift instructions created.")

    def read_tx(self):
        """Read one byte from USER1 (TX FIFO). Returns (valid, byte) or (False, 0)."""
        result = self.tcl("shift_hw_jtag_data user1_tx 9 0")
        # Parse the result - format: "9'hXXX" or decimal
        value = self._parse_dr_value(result)
        valid = bool(value & 0x100)  # Bit 8 = valid
        data = value & 0xFF
        return valid, data

    def write_rx(self, byte_val):
        """Write one byte to USER2 (RX FIFO). Sets valid bit."""
        dr_val = (1 << 8) | (byte_val & 0xFF)  # valid=1, data=byte
        result = self.tcl(f"shift_hw_jtag_data user2_rx 9 {dr_val}")
        return result

    def _parse_dr_value(self, result_str):
        """Parse the DR value from Vivado TCL output."""
        result_str = result_str.strip()
        # Try different formats
        # Format 1: decimal number
        try:
            return int(result_str)
        except ValueError:
            pass
        # Format 2: hex like "9'h1XX"
        if "'" in result_str:
            parts = result_str.split("'")
            if len(parts) >= 2:
                base_char = parts[1][0].lower()
                num_str = parts[1][1:]
                if base_char == 'h':
                    return int(num_str, 16)
                elif base_char == 'b':
                    return int(num_str, 2)
                elif base_char == 'd':
                    return int(num_str, 10)
        # Format 3: just hex digits
        try:
            return int(result_str, 16)
        except ValueError:
            pass
        return 0

    def close(self):
        """Close the Vivado session."""
        if self.process:
            try:
                self.process.stdin.write("exit\n")
                self.process.stdin.flush()
                self.process.wait(timeout=10)
            except Exception:
                self.process.kill()
            self.process = None


# ============================================================
# Main UART Bridge Loop
# ============================================================
def tx_reader(jtag, tx_queue):
    """Continuously read USER1 to get UART TX data from FPGA."""
    print("[TX Reader] Starting...")
    while True:
        try:
            valid, data = jtag.read_tx()
            if valid:
                ch = chr(data) if 0x20 <= data < 0x7F else f"\\x{data:02x}"
                tx_queue.put(data)
                sys.stdout.write(ch if 0x20 <= data < 0x7F else f"\\x{data:02x}")
                sys.stdout.flush()
        except Exception as e:
            print(f"\n[TX Reader] Error: {e}", file=sys.stderr)
            time.sleep(0.1)


def rx_writer(jtag, rx_queue):
    """Write bytes from rx_queue to USER2 to send to FPGA."""
    print("[RX Writer] Starting...")
    while True:
        try:
            byte_val = rx_queue.get(timeout=0.1)
            jtag.write_rx(byte_val)
        except queue.Empty:
            continue
        except Exception as e:
            print(f"\n[RX Writer] Error: {e}", file=sys.stderr)
            time.sleep(0.1)


def keyboard_reader(rx_queue):
    """Read keyboard input and put bytes into rx_queue."""
    print("[Keyboard] Starting (press keys to send to FPGA, Ctrl+C to quit)...")
    try:
        while True:
            ch = sys.stdin.read(1)
            if ch:
                rx_queue.put(ord(ch))
            else:
                time.sleep(0.01)
    except KeyboardInterrupt:
        print("\n[Keyboard] Interrupted.")


def main():
    print("=" * 60)
    print("JTAG UART Bridge for Basys3 (XC7A35T)")
    print("=" * 60)

    jtag = VivadoJTAG()
    tx_queue = queue.Queue()
    rx_queue = queue.Queue()

    try:
        # Start and connect
        jtag.start()
        jtag.connect()

        # Start reader/writer threads
        tx_thread = threading.Thread(target=tx_reader, args=(jtag, tx_queue), daemon=True)
        rx_thread = threading.Thread(target=rx_writer, args=(jtag, rx_queue), daemon=True)
        kb_thread = threading.Thread(target=keyboard_reader, args=(rx_queue,), daemon=True)

        tx_thread.start()
        rx_thread.start()
        kb_thread.start()

        print("\n[JTAG UART] Bridge active. UART output from FPGA:")
        print("-" * 40)

        # Keep main thread alive
        while True:
            time.sleep(1)

    except KeyboardInterrupt:
        print("\n\n[JTAG UART] Shutting down...")
    except Exception as e:
        print(f"\n[JTAG UART] Fatal error: {e}", file=sys.stderr)
    finally:
        jtag.close()
        print("[JTAG UART] Done.")


if __name__ == "__main__":
    main()
