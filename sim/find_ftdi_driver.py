"""Try multiple methods to access the FTDI device with VID=0x1443.

Method 1: Find FTDI driver INF files and install them for the custom VID
Method 2: Use devcon/pnputil to bind FTDI driver to the device
Method 3: Use Windows SetupAPI to install driver
"""
import subprocess
import os
import ctypes

print("=== Method 1: Find FTDI driver INF files ===")
# Find FTDI driver INF files
ftdi_inf_locations = []
search_paths = [
    'C:\\Windows\\INF',
    'C:\\Windows\\System32\\DriverStore\\FileRepository',
]
for search_path in search_paths:
    if not os.path.isdir(search_path):
        continue
    for item in os.listdir(search_path):
        if 'ftdi' in item.lower() or 'ftdibus' in item.lower() or 'ftdiport' in item.lower():
            full_path = os.path.join(search_path, item)
            if os.path.isdir(full_path):
                # Look for .inf files
                for f in os.listdir(full_path):
                    if f.endswith('.inf'):
                        ftdi_inf_locations.append(os.path.join(full_path, f))
            elif item.endswith('.inf'):
                ftdi_inf_locations.append(full_path)

for inf in ftdi_inf_locations:
    print(f"  Found: {inf}")
    # Check if it supports custom VID
    try:
        with open(inf, 'r', errors='ignore') as f:
            content = f.read()
        if '1443' in content.lower() or '0403' in content.lower():
            # Show VID/PID sections
            lines = content.split('\n')
            for i, line in enumerate(lines):
                if '1443' in line or 'VID_0403' in line or 'VID_1443' in line:
                    print(f"    Line {i}: {line.strip()}")
    except:
        pass

print("\n=== Method 2: Check devcon/pnputil ===")
# Check for devcon
result = subprocess.run(['where', 'devcon'], capture_output=True, text=True)
print(f"  devcon: {result.stdout.strip() or 'not found'}")

# pnputil is always available on Windows
result = subprocess.run(['where', 'pnputil'], capture_output=True, text=True)
print(f"  pnputil: {result.stdout.strip()}")

print("\n=== Method 3: Try pnputil to list FTDI drivers ===")
result = subprocess.run(['pnputil', '/enum-drivers'], capture_output=True, text=True)
output = result.stdout
# Find FTDI-related entries
lines = output.split('\n')
for i, line in enumerate(lines):
    if 'ftdi' in line.lower():
        # Print context
        start = max(0, i-2)
        end = min(len(lines), i+5)
        print(f"  Context around line {i}:")
        for j in range(start, end):
            print(f"    {lines[j]}")
        print()

print("\n=== Method 4: Find FTDI COM port driver (ftdiport) INF ===")
# The ftdiport.inf might have configurable VID/PID
result = subprocess.run(['pnputil', '/enum-drivers'], capture_output=True, text=True)
output = result.stdout
# Parse entries
entries = output.split('\n\n')
for entry in entries:
    if 'ftdi' in entry.lower() or 'ftdibus' in entry.lower():
        print(entry)
        print("---")
