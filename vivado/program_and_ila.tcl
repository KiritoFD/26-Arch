# Program FPGA + immediately capture ILA (reset CPU via JTAG programming)
set repo_root {G:/GitHub/26-Arch}
set bitstream_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.bit]
set ltx_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.ltx]
set ila_csv [file join $repo_root vivado ila_after_fix.csv]

open_hw_manager
connect_hw_server -url localhost:3121 -allow_non_jtag

set targets [get_hw_targets -quiet]
if {[llength $targets] == 0} { puts "ERROR: No targets"; exit 1 }

current_hw_target [lindex $targets 0]
open_hw_target

set dev [lindex [get_hw_devices] 0]
current_hw_device $dev
set_property PROGRAM.FILE $bitstream_path $dev
set_property PROBES.FILE $ltx_path $dev

# Reprogram FPGA (this resets CPU)
puts "Reprogramming FPGA (resets CPU)..."
program_hw_devices $dev
puts "Programmed!"

# Wait a moment for CPU to start executing
after 1000
refresh_hw_device $dev

set ilas [get_hw_ilas -quiet]
set ila_core [lindex $ilas 0]

# Run ILA capture
puts "Running ILA capture..."
run_hw_ila $ila_core

# Wait longer for trigger and data
after 5000
refresh_hw_device $dev

puts "Uploading..."
set hw_ila_data [upload_hw_ila $ila_core]
puts "Data: $hw_ila_data"
wait_on_hw_ila $ila_core

# Write to CSV using current_hw_ila_data approach
current_hw_ila_data $hw_ila_data
catch {write_hw_ila_data -quiet -force -csv -file $ila_csv $hw_ila_data} werr
puts "write err: $werr"

# Display (creates backup .ila file)
display_hw_ila_data $hw_ila_data

close_hw_target
disconnect_hw_server
close_hw_manager
