# Minimal rebuild: skip BRAM COE reconfigure (kernel unchanged), only device.sv changed
set repo_root {G:/GitHub/26-Arch}
set project_path [file join $repo_root vivado test-cpu project project_3 project_3.xpr]

open_project $project_path

# Refresh source files (pick up device.sv modifications)
update_compile_order -fileset sources_1

# Reset and run synth
reset_run synth_1
launch_runs synth_1 -jobs 4
wait_on_run synth_1

# Reset and run impl + bitstream
reset_run impl_1
launch_runs impl_1 -to_step write_bitstream -jobs 4
wait_on_run impl_1

puts "BUILD DONE"
close_project
