# Generate LTX from routed checkpoint, then program FPGA via JTAG
set repo_root {G:/GitHub/26-Arch}
set routed_dcp [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top_routed.dcp]
set ltx_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.ltx]
set bitstream_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.bit]

# Step 1: Generate LTX from routed checkpoint
puts "=========================================="
puts "Generating LTX from routed checkpoint..."
puts "=========================================="
open_checkpoint $routed_dcp
write_debug_probes -force $ltx_path
close_design

if {[file exists $ltx_path]} {
    puts "LTX generated: $ltx_path ([file size $ltx_path] bytes)"
} else {
    puts "ERROR: LTX not generated!"
    exit 1
}

# Step 2: Program FPGA via JTAG
puts "=========================================="
puts "Programming FPGA via JTAG..."
puts "=========================================="
open_hw_manager
connect_hw_server -url localhost:3121 -allow_non_jtag

set targets [get_hw_targets -quiet]
if {[llength $targets] == 0} {
    puts "ERROR: No hardware targets found."
    exit 1
}

current_hw_target [lindex $targets 0]
open_hw_target

set dev [lindex [get_hw_devices] 0]
current_hw_device $dev
set_property PROGRAM.FILE $bitstream_path $dev
set_property PROBES.FILE $ltx_path $dev

puts "Programming $dev..."
program_hw_devices $dev
puts "Programming complete!"

close_hw_target
disconnect_hw_server
close_hw_manager
puts "=========================================="
puts "DONE! FPGA programmed with SPI Flash address fix."
puts "=========================================="
