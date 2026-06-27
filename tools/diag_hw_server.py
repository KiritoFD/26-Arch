#!/usr/bin/env python3
"""Start hw_server and capture its output to diagnose cable detection."""
import subprocess
import time
import os

HW_SERVER = r"C:\Xilinx\Vivado\2019.2\bin\hw_server.exe"
LOG_FILE = r"g:\GitHub\26-Arch\hw_server_diag.log"

# Start hw_server with verbose logging
env = os.environ.copy()
env['XILINX_VIVADO'] = r'C:\Xilinx\Vivado\2019.2'

print("Starting hw_server with verbose logging...")
print(f"Log file: {LOG_FILE}")

# Kill any existing hw_server
subprocess.run(['taskkill', '/f', '/im', 'hw_server.exe'],
               capture_output=True, text=True)
time.sleep(1)

# Start hw_server
proc = subprocess.Popen(
    [HW_SERVER, '-L', '3121', '-d'],
    stdout=subprocess.PIPE,
    stderr=subprocess.STDOUT,
    text=True,
    env=env
)

print(f"hw_server PID: {proc.pid}")
print("Waiting 5 seconds for hw_server to detect devices...")
time.sleep(5)

# Read output
output = proc.stdout.read() if proc.stdout else ""

# Also try connecting via Vivado Tcl
print("\n--- Trying Vivado Tcl connection ---")
tcl_script = r"""
open_hw_manager
connect_hw_server -url localhost:3121 -allow_non_jtag
set targets [get_hw_targets -quiet]
puts "TARGETS: $targets"
if {[llength $targets] == 0} {
    puts "ERROR: No hardware targets found"
    puts "Listing hw_devices:"
    set devs [get_hw_devices -quiet]
    puts "Devices: $devs"
} else {
    puts "Found targets!"
}
disconnect_hw_server
close_hw_manager
"""

with open(r'g:\GitHub\26-Arch\vivado\diag_connect.tcl', 'w') as f:
    f.write(tcl_script)

result = subprocess.run(
    [r'C:\Xilinx\Vivado\2019.2\bin\vivado.bat', '-mode', 'batch',
     '-source', r'g:\GitHub\26-Arch\vivado\diag_connect.tcl'],
    capture_output=True, text=True, timeout=30
)

print("\n--- Vivado output ---")
print(result.stdout[-2000:] if result.stdout else "no stdout")
if result.stderr:
    print(f"\n--- stderr (last 1000) ---")
    print(result.stderr[-1000:])

# Kill hw_server
proc.terminate()
proc.wait()

# Write log
with open(LOG_FILE, 'w') as f:
    f.write("=== hw_server output ===\n")
    f.write(output)
    f.write("\n\n=== Vivado output ===\n")
    f.write(result.stdout if result.stdout else "")
    f.write("\n\n=== Vivado stderr ===\n")
    f.write(result.stderr if result.stderr else "")

print(f"\nLog written to: {LOG_FILE}")
