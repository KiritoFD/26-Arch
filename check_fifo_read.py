#!/usr/bin/env python3
"""
Read FT2232H Channel A in current 0x64 mode (FIFO interface mode, no UART).
In FIFO mode, RX FIFO accumulates bytes clocked from BDBUS by internal logic —
but Basys3 wires RsTx/RsRx to BDBUS0/BDBUS1 directly, so the FT2232 internal
UART state machine is DISABLED in FIFO mode. We must read raw BD bus via
FT_GetBitMode (gives current 8-bit BD bus state) and sample BDBUS0 (=RsTx)
using software polling to reconstruct UART frames.

Strategy:
  1. Poll FT_GetBitMode at high frequency
  2. Detect falling edge on BDBUS0 (start bit)
  3. Sample 8 data bits + 1 stop bit at baud-intervals
  4. Reconstruct bytes
"""
import sys, ctypes, time
from ctypes import wintypes
sys.path.insert(0, 'tools')
from uart_monitor import ftd2xx, FT_OK

handle = ctypes.c_void_p(0)
status = ftd2xx.FT_Open(0, ctypes.byref(handle))
if status != FT_OK:
    print(f"FT_Open failed: {status}")
    sys.exit(1)

# Keep current mode (0x64), just configure for low-latency polling
ftd2xx.FT_SetTimeouts(handle, 0, 0)        # non-blocking
ftd2xx.FT_SetLatencyTimer(handle, 1)        # 1ms latency
ftd2xx.FT_Purge(handle, 3)

# Verify current BD bus state
ftd2xx.FT_GetBitMode.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_ubyte)]
ftd2xx.FT_GetBitMode.restype = wintypes.DWORD
mode = ctypes.c_ubyte(0)
ftd2xx.FT_GetBitMode(handle, ctypes.byref(mode))
print(f"Current mode: 0x{mode.value:02x}")

# Sample BD bus 1000 times to see if RsTx (bit0) toggles
samples = []
for _ in range(1000):
    m = ctypes.c_ubyte(0)
    ftd2xx.FT_GetBitMode(handle, ctypes.byref(m))
    samples.append(m.value & 0x01)  # BDBUS0 = RsTx

idle_count = sum(samples)
print(f"BDBUS0 (RsTx) state over 1000 polls: idle(1)={idle_count}, low(0)={1000-idle_count}")

# Also try reading from RX FIFO (in FIFO mode, this reads data clocked in via RD#)
buf = (ctypes.c_ubyte * 4096)()
got = wintypes.DWORD(0)
ftd2xx.FT_Read(handle, buf, 4096, ctypes.byref(got))
print(f"FT_Read (FIFO mode): {got.value} bytes")
if got.value > 0:
    print(f"  Data: {bytes(buf[:min(got.value,64)]).hex(' ')}")

ftd2xx.FT_Close(handle)
