open_hw
connect_hw_server
open_hw_target
current_hw_device [lindex [get_hw_devices] 0]
set_property PROGRAM.FILE {G:/Github/26-Arch/vivado/test-cpu/project/project_3/project_3.runs/impl_1/basys3_top.bit} [current_hw_device]
program_hw_devices [current_hw_device]
close_hw_target
disconnect_hw_server
exit
