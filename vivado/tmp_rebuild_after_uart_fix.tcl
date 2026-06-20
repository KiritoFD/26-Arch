open_project G:/Github/26-Arch/vivado/test-cpu/project/project_3/project_3.xpr
update_compile_order -fileset sources_1
reset_run synth_1
reset_run impl_1
launch_runs impl_1 -to_step write_bitstream -jobs 4
wait_on_run impl_1
open_run impl_1
report_timing_summary -file G:/Github/26-Arch/vivado/test-cpu/project/project_3/project_3.runs/impl_1/post_fix_timing_summary.rpt
close_project
exit
