# program_and_read_uart.tcl - Program FPGA and immediately read JTAG UART
set repo_root {G:/GitHub/26-Arch}
set bitstream_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.bit]

open_hw
connect_hw_server -url localhost:3121
open_hw_target

set device [get_hw_devices xc7a35t_0]
current_hw_device $device

# Step 1: Program FPGA with bitstream
puts "Step 1: Programming FPGA..."
set_property PROGRAM.FILE $bitstream_path $device
program_hw_devices $device
puts "FPGA programmed!"

close_hw_target
disconnect_hw_server
close_hw

puts "=========================================="
puts "FPGA programmed! Now run xsdb to read UART."
puts "=========================================="
