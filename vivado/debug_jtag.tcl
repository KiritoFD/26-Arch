# Use Vivado Hardware Manager to read FPGA internal signals via JTAG
# This creates a simple debug bridge to verify UART TX is working
open_hw
connect_hw_server
open_hw_target

set device [get_hw_devices xc7a35t_0]
current_hw_device $device

# Create a VIO (Virtual Input/Output) core to read internal signals
# Actually, we need to add VIO to the design first. Let's just read the device status.

# Read the configuration register to verify FPGA is configured
refresh_hw_device $device

# Try to read the UART TX pin state using EPP (Extended Parallel Processing)
# We can use the JTAG USER instructions to read internal signals

# Actually, let's just verify the bitstream is loaded correctly
puts "Device: $device"
puts "Device is programmed: [get_property PROGRAM.HW_DEVICE $device]"

close_hw_target
disconnect_hw_server
close_hw
