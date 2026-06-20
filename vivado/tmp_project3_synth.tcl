open_project G:/Github/26-Arch/vivado/test-cpu/project/project_3/project_3.xpr
add_files -norecurse G:/Github/26-Arch/vsrc/util/mmu.sv
set_property include_dirs [list G:/Github/26-Arch/vsrc] [get_filesets sources_1]
set_property include_dirs [list G:/Github/26-Arch/vsrc] [get_filesets sim_1]
update_compile_order -fileset sources_1
reset_run synth_1
launch_runs synth_1 -jobs 4
wait_on_run synth_1
close_project
