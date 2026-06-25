# Build with xv6-kernel.coe - force BRAM resynthesis
set repo_root {G:/GitHub/26-Arch}
set project_path [file join $repo_root vivado test-cpu project project_3 project_3.xpr]

open_project $project_path

# Switch BRAM COE back to xv6-kernel.coe
set coe_path [file join $repo_root ready-to-run lab5 xv6-kernel.coe]
set bram_ip [get_ips bram_0]
set_property -dict [list \
    CONFIG.Coe_File $coe_path \
    CONFIG.Load_Init_File {true} \
] $bram_ip

# Force regenerate BRAM IP with new COE
generate_target all [get_ips bram_0] -force

# Run BRAM OOC synthesis
reset_run bram_0_synth_1
launch_runs bram_0_synth_1
wait_on_run bram_0_synth_1
puts "BRAM OOC synthesis complete!"

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
