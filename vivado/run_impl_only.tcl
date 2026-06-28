open_project g:/GitHub/26-Arch/vivado/xv6_project/xv6_project.xpr
reset_run impl_1
launch_runs impl_1 -jobs 4
wait_on_run impl_1
set impl_status [get_property STATUS [get_runs impl_1]]
puts "IMPL_STATUS=$impl_status"
exit
