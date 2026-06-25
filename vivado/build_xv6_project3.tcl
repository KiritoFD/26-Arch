# Build xv6 using project_3 with Vivado 2018.3
# Fix: Add all missing core sub-module files, ensure BRAM IP OOC synthesis

set repo_root {G:/GitHub/26-Arch}
set project_path [file join $repo_root vivado test-cpu project project_3 project_3.xpr]

open_project $project_path

# Add all missing core sub-module files
add_files -norecurse [file join $repo_root vsrc src core core_pkg.sv]
add_files -norecurse [file join $repo_root vsrc src core core_decode.sv]
add_files -norecurse [file join $repo_root vsrc src core core_execute.sv]
add_files -norecurse [file join $repo_root vsrc src core core_mdu.sv]
add_files -norecurse [file join $repo_root vsrc src core core_csr.sv]
add_files -norecurse [file join $repo_root vsrc src core core_commit.sv]

# Update compile order
update_compile_order -fileset sources_1

# Update BRAM IP with xv6 kernel COE
set coe_path [file join $repo_root ready-to-run lab5 xv6-kernel.coe]
set bram_ip [get_ips bram_0]
set_property -dict [list \
    CONFIG.Coe_File $coe_path \
    CONFIG.Load_Init_File {true} \
] $bram_ip

# Regenerate IP outputs
generate_target all [get_ips] -force

# Run OOC synthesis for bram_0 (must complete before top-level synth)
reset_run bram_0_synth_1
launch_runs bram_0_synth_1
wait_on_run bram_0_synth_1

if {[get_property STATUS [get_runs bram_0_synth_1]] != "synth_design Complete!"} {
    puts "ERROR: BRAM OOC synthesis failed!"
    exit 1
}
puts "BRAM OOC synthesis complete!"

# Run top-level synthesis
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

# Run implementation
reset_run impl_1
launch_runs impl_1 -jobs 4
wait_on_run impl_1

if {[get_property STATUS [get_runs impl_1]] != "route_design Complete!"} {
    puts "ERROR: Implementation failed!"
    exit 1
}
puts "Implementation complete!"

# Generate bitstream
launch_runs impl_1 -to_step write_bitstream
wait_on_run impl_1

puts "Build complete! Bitstream at:"
puts [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.bit]

close_project
