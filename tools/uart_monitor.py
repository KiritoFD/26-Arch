#!/usr/bin/env python3
"""
xv6 UART Monitor for Basys3 via FT2232H D2XX
Channel A (FPGA RsTx/RsRx) is in D2XX UART mode (no COM port).
This tool reads/writes via ftd2xx.dll directly.

Usage: python uart_monitor.py [baud_rate]
Default baud: 115200 (FPGA: 25MHz cpu_clk / 217 bitTmr = 115207)
"""
import sys
import os
import threading
import time
import ctypes
from ctypes import wintypes

# FTD2XX constants
FT_OK = 0
FT_OPEN_BY_DESCRIPTION = 2
FT_BITS_8 = 8
FT_STOP_BITS_1 = 0
FT_PARITY_NONE = 0
FT_FLOW_NONE = 0
FT_PURGE_RX = 1
FT_PURGE_TX = 2

# Load DLL
try:
    ftd2xx = ctypes.WinDLL("ftd2xx.dll")
except OSError:
    print("ERROR: ftd2xx.dll not found. Install FTDI D2XX drivers.")
    sys.exit(1)

# API signatures
ftd2xx.FT_CreateDeviceInfoList.argtypes = [ctypes.POINTER(wintypes.DWORD)]
ftd2xx.FT_CreateDeviceInfoList.restype = wintypes.DWORD

ftd2xx.FT_Open.argtypes = [ctypes.c_int, ctypes.POINTER(ctypes.c_void_p)]
ftd2xx.FT_Open.restype = wintypes.DWORD

ftd2xx.FT_OpenEx.argtypes = [ctypes.c_void_p, wintypes.DWORD, ctypes.POINTER(ctypes.c_void_p)]
ftd2xx.FT_OpenEx.restype = wintypes.DWORD

ftd2xx.FT_Close.argtypes = [ctypes.c_void_p]
ftd2xx.FT_Close.restype = wintypes.DWORD

ftd2xx.FT_Read.argtypes = [ctypes.c_void_p, ctypes.c_void_p, wintypes.DWORD, ctypes.POINTER(wintypes.DWORD)]
ftd2xx.FT_Read.restype = wintypes.DWORD

ftd2xx.FT_Write.argtypes = [ctypes.c_void_p, ctypes.c_void_p, wintypes.DWORD, ctypes.POINTER(wintypes.DWORD)]
ftd2xx.FT_Write.restype = wintypes.DWORD

ftd2xx.FT_SetBaudRate.argtypes = [ctypes.c_void_p, wintypes.ULONG]
ftd2xx.FT_SetBaudRate.restype = wintypes.DWORD

ftd2xx.FT_SetDataCharacteristics.argtypes = [ctypes.c_void_p, ctypes.c_ubyte, ctypes.c_ubyte, ctypes.c_ubyte]
ftd2xx.FT_SetDataCharacteristics.restype = wintypes.DWORD

ftd2xx.FT_SetFlowControl.argtypes = [ctypes.c_void_p, ctypes.c_ushort, ctypes.c_ubyte, ctypes.c_ubyte]
ftd2xx.FT_SetFlowControl.restype = wintypes.DWORD

ftd2xx.FT_SetTimeouts.argtypes = [ctypes.c_void_p, wintypes.ULONG, wintypes.ULONG]
ftd2xx.FT_SetTimeouts.restype = wintypes.DWORD

ftd2xx.FT_Purge.argtypes = [ctypes.c_void_p, wintypes.ULONG]
ftd2xx.FT_Purge.restype = wintypes.DWORD

ftd2xx.FT_ResetDevice.argtypes = [ctypes.c_void_p]
ftd2xx.FT_ResetDevice.restype = wintypes.DWORD

ftd2xx.FT_GetQueueStatus.argtypes = [ctypes.c_void_p, ctypes.POINTER(wintypes.DWORD)]
ftd2xx.FT_GetQueueStatus.restype = wintypes.DWORD

ftd2xx.FT_SetLatencyTimer.argtypes = [ctypes.c_void_p, ctypes.c_ubyte]
ftd2xx.FT_SetLatencyTimer.restype = wintypes.DWORD

ftd2xx.FT_SetBitMode.argtypes = [ctypes.c_void_p, ctypes.c_ubyte, ctypes.c_ubyte]
ftd2xx.FT_SetBitMode.restype = wintypes.DWORD


class FTDeviceInfo(ctypes.Structure):
    _fields_ = [
        ("flags", wintypes.DWORD),
        ("type", wintypes.DWORD),
        ("id", wintypes.DWORD),
        ("locId", wintypes.DWORD),
        ("serialNumber", ctypes.c_char * 16),
        ("description", ctypes.c_char * 64),
        ("ftHandle", ctypes.c_void_p),
    ]


def list_devices():
    """List all FTDI devices, return list of (index, description)."""
    num = wintypes.DWORD(0)
    ftd2xx.FT_CreateDeviceInfoList(ctypes.byref(num))
    devices = []
    if num.value > 0:
        infos = (FTDeviceInfo * num.value)()
        # FT_GetDeviceInfoList
        ftd2xx.FT_GetDeviceInfoList.argtypes = [ctypes.POINTER(FTDeviceInfo), ctypes.POINTER(wintypes.DWORD)]
        ftd2xx.FT_GetDeviceInfoList.restype = wintypes.DWORD
        ftd2xx.FT_GetDeviceInfoList(infos, ctypes.byref(num))
        for i, info in enumerate(infos):
            desc = info.description.decode('ascii', errors='replace')
            devices.append((i, desc))
    return devices


def find_basys3_uart():
    """Find FT2232H Channel A (UART, index 0 usually).
    Basys3 FT2232H: Channel A=UART(RsTx/RsRx), Channel B=JTAG.
    Channel A description typically contains 'A' or is the first device.
    """
    devices = list_devices()
    if not devices:
        return None, "No FTDI devices found"
    # Basys3 shows two interfaces; Channel A is usually index 0
    # Description may be "Digilent USB Device A" or similar
    for idx, desc in devices:
        if 'A' in desc and ('Basys' in desc or 'Digilent' in desc or 'USB' in desc):
            return idx, desc
    # Fallback: return first device
    return devices[0][0], devices[0][1]


def open_uart(device_index, baud=115200):
    """Open FTDI device and configure as UART."""
    handle = ctypes.c_void_p(0)
    status = ftd2xx.FT_Open(device_index, ctypes.byref(handle))
    if status != FT_OK:
        return None, f"FT_Open failed: {status}"
    ftd2xx.FT_ResetDevice(handle)
    # Reset bitmode to UART (clear any FIFO/bitbang mode)
    ftd2xx.FT_SetBitMode(handle, 0, 0)
    ftd2xx.FT_SetBaudRate(handle, baud)
    ftd2xx.FT_SetDataCharacteristics(handle, FT_BITS_8, FT_STOP_BITS_1, FT_PARITY_NONE)
    ftd2xx.FT_SetFlowControl(handle, FT_FLOW_NONE, 0, 0)
    ftd2xx.FT_SetTimeouts(handle, 100, 100)  # 100ms read/write timeout
    ftd2xx.FT_SetLatencyTimer(handle, 2)  # low latency for responsive reads
    ftd2xx.FT_Purge(handle, FT_PURGE_RX | FT_PURGE_TX)
    return handle, "OK"


def read_uart(handle, max_bytes=4096):
    """Read available bytes from UART."""
    buf = (ctypes.c_ubyte * max_bytes)()
    written = wintypes.DWORD(0)
    status = ftd2xx.FT_Read(handle, buf, max_bytes, ctypes.byref(written))
    if status != FT_OK:
        return None, f"FT_Read failed: {status}"
    return bytes(buf[:written.value]), "OK"


def write_uart(handle, data):
    """Write bytes to UART."""
    buf = (ctypes.c_ubyte * len(data))(*data)
    written = wintypes.DWORD(0)
    status = ftd2xx.FT_Write(handle, buf, len(data), ctypes.byref(written))
    if status != FT_OK:
        return False, f"FT_Write failed: {status}"
    return True, "OK"


def close_uart(handle):
    ftd2xx.FT_Close(handle)


# ===================== Tkinter GUI =====================
try:
    import tkinter as tk
    from tkinter import ttk, scrolledtext
    HAS_TK = True
except ImportError:
    HAS_TK = False


class UARTMonitorGUI:
    def __init__(self, root, baud=115200):
        self.root = root
        self.baud = baud
        self.handle = None
        self.running = False
        self.rx_total = 0
        self.tx_total = 0

        root.title("xv6 UART Monitor (FT2232H D2XX)")
        root.geometry("900x650")

        # Top control bar
        top = ttk.Frame(root)
        top.pack(fill=tk.X, padx=5, pady=5)

        ttk.Label(top, text="Baud:").pack(side=tk.LEFT)
        self.baud_var = tk.StringVar(value=str(baud))
        baud_combo = ttk.Combobox(top, textvariable=self.baud_var, width=8,
                                   values=["9600", "38400", "57600", "115200", "230400", "460800"])
        baud_combo.pack(side=tk.LEFT, padx=5)

        self.connect_btn = ttk.Button(top, text="Connect", command=self.toggle_connect)
        self.connect_btn.pack(side=tk.LEFT, padx=5)

        self.clear_btn = ttk.Button(top, text="Clear", command=self.clear_output)
        self.clear_btn.pack(side=tk.LEFT, padx=5)

        self.status_var = tk.StringVar(value="Disconnected")
        ttk.Label(top, textvariable=self.status_var).pack(side=tk.LEFT, padx=10)

        # RX hex toggle
        self.hex_var = tk.BooleanVar(value=False)
        ttk.Checkbutton(top, text="Hex", variable=self.hex_var).pack(side=tk.LEFT, padx=5)

        # RX text area
        ttk.Label(root, text="UART RX Output:").pack(anchor=tk.W, padx=5)
        self.rx_text = scrolledtext.ScrolledText(root, height=25, font=("Consolas", 10))
        self.rx_text.pack(fill=tk.BOTH, expand=True, padx=5, pady=2)

        # TX input
        ttk.Label(root, text="TX Input (Enter to send, \\n for newline):").pack(anchor=tk.W, padx=5)
        tx_frame = ttk.Frame(root)
        tx_frame.pack(fill=tk.X, padx=5, pady=2)
        self.tx_entry = ttk.Entry(tx_frame)
        self.tx_entry.pack(side=tk.LEFT, fill=tk.X, expand=True)
        self.tx_entry.bind('<Return>', lambda e: self.send_input())
        ttk.Button(tx_frame, text="Send", command=self.send_input).pack(side=tk.LEFT, padx=5)

        # Stats
        self.stats_var = tk.StringVar(value="RX: 0 bytes | TX: 0 bytes")
        ttk.Label(root, textvariable=self.stats_var).pack(anchor=tk.W, padx=5, pady=2)

    def toggle_connect(self):
        if self.running:
            self.disconnect()
        else:
            self.connect()

    def connect(self):
        baud = int(self.baud_var.get())
        idx, desc = find_basys3_uart()
        if idx is None:
            self.status_var.set(f"ERROR: {desc}")
            return
        handle, msg = open_uart(idx, baud)
        if handle is None:
            self.status_var.set(f"ERROR: {msg}")
            return
        self.handle = handle
        self.running = True
        self.connect_btn.config(text="Disconnect")
        self.status_var.set(f"Connected: idx={idx} ({desc}) @ {baud} baud")
        threading.Thread(target=self.rx_loop, daemon=True).start()

    def disconnect(self):
        self.running = False
        if self.handle:
            close_uart(self.handle)
            self.handle = None
        self.connect_btn.config(text="Connect")
        self.status_var.set("Disconnected")

    def rx_loop(self):
        while self.running and self.handle:
            data, msg = read_uart(self.handle, 4096)
            if data is None:
                self.status_var.set(f"Read error: {msg}")
                break
            if data:
                self.rx_total += len(data)
                self.root.after(0, self.append_rx, data)
                self.root.after(0, self.update_stats)

    def append_rx(self, data):
        if self.hex_var.get():
            text = ' '.join(f'{b:02x}' for b in data)
        else:
            text = data.decode('utf-8', errors='replace')
        self.rx_text.insert(tk.END, text)
        self.rx_text.see(tk.END)
        # Limit buffer to avoid memory issues
        if float(self.rx_text.index('end-1c')) > 100000:
            self.rx_text.delete('1.0', '50000.0')

    def update_stats(self):
        self.stats_var.set(f"RX: {self.rx_total} bytes | TX: {self.tx_total} bytes")

    def clear_output(self):
        self.rx_text.delete('1.0', tk.END)

    def send_input(self):
        if not self.handle:
            return
        text = self.tx_entry.get()
        self.tx_entry.delete(0, tk.END)
        # Replace literal \n with newline
        text = text.replace('\\n', '\n')
        data = (text + '\n').encode('utf-8')
        ok, msg = write_uart(self.handle, data)
        if ok:
            self.tx_total += len(data)
            self.update_stats()


def main():
    baud = 115200
    if len(sys.argv) > 1:
        baud = int(sys.argv[1])

    if not HAS_TK:
        # CLI mode
        print(f"=== CLI Mode (baud={baud}) ===")
        devices = list_devices()
        for idx, desc in devices:
            print(f"  [{idx}] {desc}")
        idx, desc = find_basys3_uart()
        if idx is None:
            print(f"ERROR: {desc}")
            return
        print(f"Opening [{idx}] {desc} @ {baud} baud...")
        handle, msg = open_uart(idx, baud)
        if handle is None:
            print(f"ERROR: {msg}")
            return
        print("Connected. Press Ctrl+C to exit.")
        try:
            while True:
                data, _ = read_uart(handle, 4096)
                if data:
                    sys.stdout.write(data.decode('utf-8', errors='replace'))
                    sys.stdout.flush()
        except KeyboardInterrupt:
            print("\nDisconnecting...")
        finally:
            close_uart(handle)
        return

    root = tk.Tk()
    app = UARTMonitorGUI(root, baud)
    root.mainloop()


if __name__ == '__main__':
    main()
