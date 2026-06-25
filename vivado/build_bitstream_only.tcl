# ================================================================
# Build bitstream for Basys3 xv6 (no flash programming)
# Steps:
#   1. Open project, upgrade IPs
#   2. Update BRAM COE file
#   3. Run synthesis + implementation + bitstream
#   4. Create MCS file with bitstream + fs.img
# ================================================================

set repo_root {G:/GitHub/26-Arch}
set project_path [file join $repo_root vivado test-cpu project project_3 project_3.xpr]
set bitstream_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.bit]
set coe_path [file join $repo_root ready-to-run lab5 xv6-kernel.coe]
set fs_img_path [file join $repo_root third_party xv6-riscv fs.img]
set mcs_file_path [file join $repo_root vivado test-cpu project project_3 full_flash.mcs]

# ================================================================
# Step 1: Open project and upgrade IPs
# ================================================================
puts "=========================================="
puts "Step 1: Opening project..."
puts "=========================================="
open_project $project_path

set locked_ips [get_ips -filter {IS_LOCKED == true}]
if {[llength $locked_ips] > 0} {
    puts "Upgrading locked IPs: $locked_ips"
    upgrade_ip $locked_ips
}

# ================================================================
# Step 2: Update BRAM IP with new kernel COE
# ================================================================
puts "=========================================="
puts "Step 2: Updating BRAM COE file..."
puts "=========================================="
set bram_ip [get_ips bram_0]
set_property -dict [list \
    CONFIG.Coe_File $coe_path \
    CONFIG.Load_Init_File {true} \
] $bram_ip

# ================================================================
# Step 3: Generate IP outputs
# ================================================================
puts "=========================================="
puts "Step 3: Generating IP outputs..."
puts "=========================================="
generate_target all [get_ips] -force

# Create OOC runs if needed
set clk_runs [get_runs -filter {NAME =~ "*clk_wiz_0_synth*"}]
if {[llength $clk_runs] == 0} {
    puts "Creating OOC synthesis run for clk_wiz_0..."
    create_ip_run [get_ips clk_wiz_0]
}

# Run OOC synthesis for clk_wiz_0
set clk_runs [get_runs -filter {NAME =~ "*clk_wiz_0_synth*"}]
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

# ================================================================
# Step 4: Run synthesis
# ================================================================
puts "=========================================="
puts "Step 4: Running synthesis..."
puts "=========================================="
reset_run synth_1
launch_runs synth_1 -jobs 32
wait_on_run synth_1
if {[get_property STATUS [get_runs synth_1]] != "synth_design Complete!"} {
    puts "ERROR: Synthesis failed!"
    exit 1
}
puts "Synthesis complete!"

# ================================================================
# Step 5: Run implementation + bitstream
# ================================================================
puts "=========================================="
puts "Step 5: Running implementation + bitstream..."
puts "=========================================="
reset_run impl_1
launch_runs impl_1 -to_step write_bitstream -jobs 32
wait_on_run impl_1
# write_bitstream 完成后状态可能为 "route_design Complete!" 或 "write_bitstream Complete!"
set impl_status [get_property STATUS [get_runs impl_1]]
puts "Implementation status: $impl_status"
if {$impl_status != "route_design Complete!" && $impl_status != "write_bitstream Complete!"} {
    puts "ERROR: Implementation failed!"
    exit 1
}
puts "Bitstream generated: $bitstream_path"

close_project

# ================================================================
# Step 6: Create MCS file with bitstream + fs.img
# ================================================================
puts "=========================================="
puts "Step 6: Creating MCS file..."
puts "=========================================="
puts "  Bitstream: $bitstream_path"
puts "  fs.img:    $fs_img_path"
puts "  MCS output: $mcs_file_path"
puts "  fs.img offset: 0x00300000 (3MB, matches device.sv)"

# MCS generation removed - SPI Flash already programmed via GUI
# write_cfgmem needs SPIx1 interface, not qspi
if {0} {
write_cfgmem -format mcs -interface qspi -size 32 \
    -loadbit "up 0x00000000 $bitstream_path" \
    -loaddata "up 0x00300000 $fs_img_path" \
    -file $mcs_file_path \
    -force
}

puts "MCS generation skipped (SPI Flash already programmed via GUI)"
puts "=========================================="
puts "BUILD COMPLETE! Ready for flashing."
puts "=========================================="
