# Open project and program FPGA
set repo_root {G:/GitHub/26-Arch}
set project_path [file join $repo_root vivado test-cpu project project_3 project_3.xpr]
open_project $project_path

# Launch runs if needed
# launch_runs impl_1 -to_step write_bitstream -jobs 4
# wait_on_run impl_1

# Program
set bitstream [get_property DIRECTORY [get_runs impl_1]]/basys3_top.bit
open_hw
connect_hw_server
after 5000
set targets [get_hw_targets]
puts "Targets: $targets"
if {[llength $targets] > 0} {
    open_hw_target [lindex $targets 0]
    set device [get_hw_devices xc7a35t_0]
    current_hw_device $device
    set_property PROGRAM.FILE $bitstream $device
    program_hw_devices $device
    puts "FPGA programmed!"
    close_hw_target
} else {
    puts "No targets found"
}
disconnect_hw_server
close_hw
