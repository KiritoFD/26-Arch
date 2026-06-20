open_project G:/Github/26-Arch/vivado/test-cpu/project/project_3/project_3.xpr
set ip [get_ips bram_0]
set_property -dict [list CONFIG.Write_Depth_A {32768} CONFIG.Load_Init_File {true} CONFIG.Coe_File {../../../../../ready-to-run/lab5/kernel.coe}] $ip
report_property $ip
generate_target all [get_files G:/Github/26-Arch/vivado/test-cpu/project/project_3/project_3.srcs/sources_1/ip/bram_0/bram_0.xci]
export_ip_user_files -of_objects [get_files G:/Github/26-Arch/vivado/test-cpu/project/project_3/project_3.srcs/sources_1/ip/bram_0/bram_0.xci] -no_script -sync -force -quiet
close_project
exit
