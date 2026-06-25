# rebuild_bram_and_bitstream.tcl - Force BRAM IP resynthesis and rebuild bitstream
set repo_root {G:/GitHub/26-Arch}
set bitstream_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.bit]

open_project [file join $repo_root vivado test-cpu project project_3 project_3.xpr]

# Force BRAM IP to resynthesize (re-read COE file)
puts "Resetting bram_0 OOC synthesis..."
reset_run bram_0_synth_1
launch_runs bram_0_synth_1 -jobs 32
wait_on_run bram_0_synth_1

puts "bram_0 status: [get_property STATUS [get_runs bram_0_synth_1]]"

# Reset and run top synthesis
puts "Resetting top synthesis..."
reset_run synth_1
launch_runs synth_1 -jobs 32
wait_on_run synth_1

# Run implementation
puts "Running implementation..."
reset_run impl_1
launch_runs impl_1 -to_step write_bitstream -jobs 32
wait_on_run impl_1

set impl_status [get_property STATUS [get_runs impl_1]]
puts "Implementation status: $impl_status"
if {$impl_status != "route_design Complete!" && $impl_status != "write_bitstream Complete!"} {
    puts "ERROR: Implementation failed!"
    exit 1
}
puts "Bitstream generated: $bitstream_path"
