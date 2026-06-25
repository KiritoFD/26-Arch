# Read FPGA IO pin state via JTAG to verify RsTx (A18) is toggling
open_hw
connect_hw_server
open_hw_target

set device [get_hw_devices xc7a35t_0]
current_hw_device $device

# Refresh device to read current state
refresh_hw_device $device

# We can't directly read IO pins via JTAG without adding debug probes,
# but we can check the device status
puts "Device: $device"
puts "Device properties:"
foreach prop [list_property $device] {
    puts "  $prop = [get_property $prop $device]"
}

close_hw_target
disconnect_hw_server
close_hw
