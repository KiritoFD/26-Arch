open_project G:/Github/26-Arch/vivado/test-cpu/project/project_3/project_3.xpr
set ip [get_ips bram_0]
upgrade_ip $ip
set_property -dict [list CONFIG.Load_Init_File {true} CONFIG.Coe_File {../../../../../ready-to-run/lab5/kernel.coe}] $ip
generate_target all [get_files G:/Github/26-Arch/vivado/test-cpu/project/project_3/project_3.srcs/sources_1/ip/bram_0/bram_0.xci]
export_ip_user_files -of_objects [get_files G:/Github/26-Arch/vivado/test-cpu/project/project_3/project_3.srcs/sources_1/ip/bram_0/bram_0.xci] -no_script -sync -force -quiet
reset_run bram_0_synth_1
launch_runs bram_0_synth_1 -jobs 8
wait_on_run bram_0_synth_1
close_project
exit
