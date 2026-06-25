# Read BSCANE2 USER1 via Vivado Hardware Manager Tcl API
# This uses Vivado's hw_device API instead of xsdb
set repo_root {G:/GitHub/26-Arch}

open_hw
connect_hw_server -url localhost:3121
open_hw_target

set device [get_hw_devices xc7a35t_0]
current_hw_device $device

puts "=== Reading BSCANE2 USER1 ==="

# Refresh device to read USER1 data
# Vivado Hardware Manager doesn't directly support BSCANE2 USER1 reads
# But we can try reading device registers

# Try using get_hw_debug_core or similar
puts "Device: $device"
puts "Properties:"
foreach prop [list_property $device] {
    set val [get_property $prop $device]
    if {$val != ""} {
        puts "  $prop = $val"
    }
}

close_hw_target
disconnect_hw_server
close_hw

puts "=== Done ==="
