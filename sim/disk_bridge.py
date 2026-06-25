#!/usr/bin/env python3
"""
UART Virtual Disk Bridge for xv6 on Basys3 FPGA
Single-wire multiplexing protocol:
  FPGA→PC: 0xAA + char (console) | 0xBB + 4B sector (disk read request)
  PC→FPGA: 0xAA + char (keyboard) | 0xBB + 512B data (disk read response)

Usage: python disk_bridge.py [serial_port] [fs_img_path]
  Default: COM4 fs.img
"""

import serial
import struct
import threading
import sys
import os
import time

# Configuration
SERIAL_PORT = sys.argv[1] if len(sys.argv) > 1 else 'COM4'
BAUD_RATE = 115200
FS_IMG = sys.argv[2] if len(sys.argv) > 2 else os.path.join(os.path.dirname(__file__), '..', 'third_party', 'xv6-riscv', 'fs.img')

# Protocol magic bytes
MAGIC_CONSOLE = 0xAA
MAGIC_DISK    = 0xBB

class DiskBridge:
    def __init__(self, port, baud, img_path):
        self.ser = serial.Serial(port, baud, timeout=0.1)
        self.img_path = img_path
        self.img_file = open(img_path, 'rb')
        self.img_size = os.path.getsize(img_path)
        self.running = True
        self.disk_ops = 0
        self.lock = threading.Lock()

    def handle_disk_request(self, sector_num):
        """Read 512 bytes from fs.img and send back with 0xBB prefix."""
        offset = sector_num * 512
        if offset + 512 > self.img_size:
            # Beyond image size, return zeros
            data = b'\x00' * 512
        else:
            self.img_file.seek(offset)
            data = self.img_file.read(512)
            if len(data) < 512:
                data = data + b'\x00' * (512 - len(data))

        # Send: 0xBB + 512 bytes
        with self.lock:
            self.ser.write(bytes([MAGIC_DISK]) + data)
        self.disk_ops += 1
        if self.disk_ops <= 20 or self.disk_ops % 50 == 0:
            print(f"[Disk] Read sector {sector_num} (total: {self.disk_ops})")

    def keyboard_thread(self):
        """Capture keyboard input and send as console packets."""
        print("[Kbd] Keyboard thread started. Type to send to xv6 shell.")
        try:
            while self.running:
                try:
                    ch = sys.stdin.read(1)
                    if ch:
                        with self.lock:
                            self.ser.write(bytes([MAGIC_CONSOLE, ord(ch)]))
                except:
                    time.sleep(0.01)
        except Exception as e:
            print(f"[Kbd] Error: {e}")

    def run(self):
        """Main loop: receive from FPGA and demux."""
        print(f"[Bridge] Serial: {self.ser.port} @ {self.ser.baudrate}bps")
        print(f"[Bridge] Disk image: {self.img_path} ({self.img_size} bytes, {self.img_size//512} sectors)")
        print(f"[Bridge] Protocol: 0xAA=console, 0xBB=disk")
        print(f"[Bridge] Waiting for FPGA...")

        # Start keyboard thread
        t_kb = threading.Thread(target=self.keyboard_thread, daemon=True)
        t_kb.start()

        try:
            while self.running:
                # Read magic byte
                magic = self.ser.read(1)
                if not magic:
                    continue

                if magic[0] == MAGIC_CONSOLE:
                    # Console output from FPGA - print to screen
                    ch = self.ser.read(1)
                    if ch:
                        sys.stdout.buffer.write(ch)
                        sys.stdout.buffer.flush()

                elif magic[0] == MAGIC_DISK:
                    # Disk read request from FPGA
                    sector_bytes = self.ser.read(4)
                    if len(sector_bytes) == 4:
                        sector_num = struct.unpack('<I', sector_bytes)[0]
                        self.handle_disk_request(sector_num)
                    else:
                        print(f"[Disk] Incomplete sector number: {len(sector_bytes)} bytes")

                else:
                    # Unknown magic byte - might be noise, skip
                    pass

        except KeyboardInterrupt:
            print("\n[Bridge] Interrupted by user")
        except Exception as e:
            print(f"[Bridge] Error: {e}")
        finally:
            self.running = False
            self.ser.close()
            self.img_file.close()
            print("[Bridge] Cleaned up")

if __name__ == '__main__':
    bridge = DiskBridge(SERIAL_PORT, BAUD_RATE, FS_IMG)
    bridge.run()
