open_project G:/Github/26-Arch/vivado/test-cpu/project/project_3/project_3.xpr
set_property include_dirs [list G:/Github/26-Arch/vsrc] [get_filesets sources_1]
set_property include_dirs [list G:/Github/26-Arch/vsrc] [get_filesets sim_1]
update_compile_order -fileset sources_1
update_compile_order -fileset sim_1
launch_simulation -simset sim_1 -mode behavioral
restart
run 20 ms
close_sim
close_project
exit
