# Rebuild bitstream with updated xv6 kernel (160KB PHYSTOP)
set repo_root {G:/GitHub/26-Arch}
set project_path [file join $repo_root vivado test-cpu project project_3 project_3.xpr]

open_project $project_path

# Upgrade locked IPs (clk_wiz_0 was created with 2018.1, needs upgrade for 2018.3)
set locked_ips [get_ips -filter {IS_LOCKED == true}]
if {[llength $locked_ips] > 0} {
    puts "Upgrading locked IPs: $locked_ips"
    upgrade_ip $locked_ips
}

# Update BRAM IP with new xv6 kernel COE
set coe_path [file join $repo_root ready-to-run lab5 xv6-kernel.coe]
set bram_ip [get_ips bram_0]
set_property -dict [list \
    CONFIG.Coe_File $coe_path \
    CONFIG.Load_Init_File {true} \
] $bram_ip

# Regenerate IP
generate_target all [get_ips] -force

# Create OOC run for clk_wiz_0 if it doesn't exist
set clk_runs [get_runs -filter {NAME =~ "*clk_wiz_0*"}]
if {[llength $clk_runs] == 0} {
    puts "Creating OOC synthesis run for clk_wiz_0..."
    create_ip_run [get_ips clk_wiz_0]
}

# Run OOC synthesis for clk_wiz_0
set clk_runs [get_runs -filter {NAME =~ "*clk_wiz_0*"}]
if {[llength $clk_runs] > 0} {
    set clk_run [lindex $clk_runs 0]
    puts "Running clk_wiz_0 OOC synthesis: $clk_run"
    reset_run $clk_run
    launch_runs $clk_run
    wait_on_run $clk_run
    if {[get_property STATUS $clk_run] != "synth_design Complete!"} {
        puts "ERROR: clk_wiz_0 OOC synthesis failed!"
        exit 1
    }
    puts "clk_wiz_0 OOC synthesis complete!"
}

# Run OOC synthesis for bram_0
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

if {[get_property STATUS [get_runs synth_1]] != "synth_design Complete!"} {
    puts "ERROR: Synthesis failed!"
    exit 1
}
puts "Synthesis complete!"

# Run implementation + bitstream
reset_run impl_1
launch_runs impl_1 -jobs 4
wait_on_run impl_1

if {[get_property STATUS [get_runs impl_1]] != "route_design Complete!"} {
    puts "ERROR: Implementation failed!"
    exit 1
}

# Generate bitstream
launch_runs impl_1 -to_step write_bitstream
wait_on_run impl_1

puts "Build complete! Bitstream at:"
puts [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.bit]

close_project
