# Quick rebuild: just synth + impl + bitstream (top-level only changed)
set repo_root {G:/GitHub/26-Arch}
set project_path [file join $repo_root vivado test-cpu project project_3 project_3.xpr]

open_project $project_path

# Run top-level synthesis
reset_run synth_1
launch_runs synth_1 -jobs 4
wait_on_run synth_1

if {[get_property STATUS [get_runs synth_1]] != "synth_design Complete!"} {
    puts "ERROR: Synthesis failed!"
    exit 1
}
puts "Synthesis complete!"

# Run implementation + bitstream
reset_run impl_1
launch_runs impl_1 -to_step write_bitstream -jobs 4
wait_on_run impl_1

puts "Build complete! Bitstream at:"
puts [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.bit]

close_project
