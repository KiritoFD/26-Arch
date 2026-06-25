# check_fpga_status.tcl - Check FPGA status and read device registers
open_hw
connect_hw_server -url localhost:3121
open_hw_target

set device [get_hw_devices xc7a35t_0]
current_hw_device $device

puts "=== Device Properties ==="
set props [list_property $device]
foreach p $props {
    catch {set val [get_property $p $device]}
    if {[info exists val] && $val ne ""} {
        puts "  $p = $val"
    }
}

# Try to read some status via JTAG
puts "=== Done ==="
close_hw_target
disconnect_hw_server
close_hw
