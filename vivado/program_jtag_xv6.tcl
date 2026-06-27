# Program FPGA via JTAG (bitstream only, temporary)
# Usage: vivado -mode batch -source program_jtag_xv6.tcl

set repo_root {G:/GitHub/26-Arch}
set bitstream_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.bit]

# Open hardware manager
open_hw_manager
connect_hw_server -url localhost:3121 -allow_non_jtag

# List targets
set targets [get_hw_targets -quiet]
if {[llength $targets] == 0} {
    puts "ERROR: No hardware targets found. Is the Basys3 connected?"
    exit 1
}

puts "Found hardware targets: $targets"
current_hw_target [lindex $targets 0]
open_hw_target

# List devices
set devices [get_hw_devices]
puts "Found devices: $devices"
if {[llength $devices] == 0} {
    puts "ERROR: No devices found."
    exit 1
}

# Program the first device
set dev [lindex $devices 0]
current_hw_device $dev

set_property PROGRAM.FILE $bitstream_path $dev

puts "Programming $dev with $bitstream_path..."
program_hw_devices $dev
puts "Programming complete!"

# Close
close_hw_target
disconnect_hw_server
close_hw_manager
