# Program FPGA bitstream
open_hw
connect_hw_server
open_hw_target

set device [get_hw_devices xc7a35t_0]
current_hw_device $device
set_property PROGRAM.FILE {G:/GitHub/26-Arch/vivado/test-cpu/project/project_3/project_3.runs/impl_1/basys3_top.bit} $device
program_hw_devices $device

close_hw_target
disconnect_hw_server
close_hw
puts "FPGA programmed successfully!"
