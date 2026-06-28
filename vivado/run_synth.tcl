open_project g:/GitHub/26-Arch/vivado/xv6_project/xv6_project.xpr
reset_run synth_1
launch_runs synth_1 -jobs 4
wait_on_run synth_1
set prop [get_property STATUS [get_runs synth_1]]
puts "SYNTH_STATUS=$prop"
exit
