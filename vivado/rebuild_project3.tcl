# Rebuild project_3 with disk BRAM support
set repo_root {G:/GitHub/26-Arch}
set project_path [file join $repo_root vivado test-cpu project project_3 project_3.xpr]

open_project $project_path

# Update compile order
update_compile_order -fileset sources_1

# Generate IP outputs
generate_target all [get_ips]

# Run synthesis
reset_run synth_1
launch_runs synth_1 -jobs 4
wait_on_run synth_1

set synth_status [get_property STATUS [get_runs synth_1]]
puts "Synthesis status: $synth_status"

if {$synth_status != "synth_design Complete!"} {
    puts "ERROR: Synthesis failed!"
    exit 1
}

puts "Synthesis complete!"

# Run implementation + bitstream
launch_runs impl_1 -to_step write_bitstream -jobs 4
wait_on_run impl_1

set impl_status [get_property STATUS [get_runs impl_1]]
puts "Implementation status: $impl_status"

if {[string first "Complete" $impl_status] == -1} {
    puts "ERROR: Implementation failed!"
    exit 1
}

puts "Build complete! Bitstream at:"
puts [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.bit]

close_project
