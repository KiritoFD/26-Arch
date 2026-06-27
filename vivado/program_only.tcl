# Program FPGA only (no ILA capture) — for use with reprogram_and_read.py
set repo_root {G:/GitHub/26-Arch}
set bitstream_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.bit]
set ltx_path       [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.ltx]

open_hw_manager
connect_hw_server -url localhost:3121 -allow_non_jtag

set targets [get_hw_targets -quiet]
if {[llength $targets] == 0} {
    puts "ERROR: No hardware targets found!"
    close_hw_manager
    exit 1
}

current_hw_target [lindex $targets 0]
open_hw_target

set device [lindex [get_hw_devices] 0]
current_hw_device $device
set_property PROGRAM.FILE $bitstream_path $device
set_property PROBES.FILE  $ltx_path       $device

program_hw_devices $device
puts "FPGA programmed successfully!"

close_hw_target
disconnect_hw_server
close_hw_manager
