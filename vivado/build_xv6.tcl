# Build xv6 FPGA project for Basys3
# Usage: vivado -mode batch -source build_xv6.tcl

set repo_root {G:/GitHub/26-Arch}
set project_dir [file join $repo_root vivado xv6_project]
set project_name xv6_project
set ip_root [file join $repo_root vivado test-cpu src ip]

file mkdir $project_dir

create_project $project_name $project_dir -force -part xc7a35tcpg236-1
set_property target_language Verilog [current_project]
set_property default_lib xil_defaultlib [current_project]

# Add source files
add_files -norecurse [file join $repo_root vsrc include config.sv]
add_files -norecurse [file join $repo_root vsrc include common.sv]
add_files -norecurse [file join $repo_root vsrc include csr.sv]
add_files -norecurse [file join $repo_root vsrc src core core_pkg.sv]
add_files -norecurse [file join $repo_root vsrc src core core_decode.sv]
add_files -norecurse [file join $repo_root vsrc src core core_execute.sv]
add_files -norecurse [file join $repo_root vsrc src core core_mdu.sv]
add_files -norecurse [file join $repo_root vsrc src core core_csr.sv]
add_files -norecurse [file join $repo_root vsrc src core core_commit.sv]
add_files -norecurse [file join $repo_root vsrc util IBusToCBus.sv]
add_files -norecurse [file join $repo_root vsrc util DBusToCBus.sv]
add_files -norecurse [file join $repo_root vsrc util CBusArbiter.sv]
add_files -norecurse [file join $repo_root vsrc util mmu.sv]
add_files -norecurse [file join $repo_root vsrc src core.sv]
add_files -norecurse [file join $repo_root vsrc VTop.sv]
add_files -norecurse [file join $repo_root vsrc mycpu_top.sv]
add_files -norecurse [file join $repo_root vivado src with_delay bram_wrapper.sv]
add_files -norecurse [file join $repo_root vivado src with_delay cbus_crossbar.sv]
add_files -norecurse [file join $repo_root vivado src with_delay soc_top.sv]
add_files -norecurse [file join $repo_root vivado src with_delay basys3_top.sv]
add_files -norecurse [file join $repo_root vivado src device.sv]
add_files -norecurse [file join $repo_root vivado src device.svh]
add_files -norecurse [file join $repo_root vivado src spi_flash_disk.sv]
add_files -fileset constrs_1 -norecurse [file join $repo_root vivado src Basys-3-Master.xdc]

# Add IP XCI files (Vivado will regenerate from these)
add_files -norecurse [file join $ip_root clk_wiz_0 clk_wiz_0.xci]
add_files -norecurse [file join $ip_root bram_0 bram_0.xci]

# Set include dirs
set_property include_dirs [list \
    [file join $repo_root vsrc] \
    [file join $repo_root vivado src] \
] [get_filesets sources_1]
set_property include_dirs [list \
    [file join $repo_root vsrc] \
    [file join $repo_root vivado src] \
] [get_filesets sim_1]

# Set top module
set_property top basys3_top [get_filesets sources_1]
update_compile_order -fileset sources_1

# Upgrade locked IPs (created with older Vivado version)
set locked_ips [get_ips -filter {IS_LOCKED == true}]
if {[llength $locked_ips] > 0} {
    puts "Upgrading locked IPs: $locked_ips"
    upgrade_ip $locked_ips
}

# Note: BRAM COE path is already configured in bram_0.xci as
# ../../../../../ready-to-run/lab5/xv6-kernel.coe
# Just ensure the COE file exists at that path (already done)

# Generate IP output products
generate_target all [get_ips] -force

# Run OOC synthesis for IPs
set clk_runs [get_runs -filter {NAME =~ "*clk_wiz_0_synth*"}]
if {[llength $clk_runs] == 0} {
    create_ip_run [get_ips clk_wiz_0]
    set clk_runs [get_runs -filter {NAME =~ "*clk_wiz_0_synth*"}]
}
if {[llength $clk_runs] > 0} {
    set clk_run [lindex $clk_runs 0]
    reset_run $clk_run
    launch_runs $clk_run
    wait_on_run $clk_run
}

set bram_runs [get_runs -filter {NAME =~ "*bram_0_synth*"}]
if {[llength $bram_runs] == 0} {
    create_ip_run [get_ips bram_0]
    set bram_runs [get_runs -filter {NAME =~ "*bram_0_synth*"}]
}
if {[llength $bram_runs] > 0} {
    set bram_run [lindex $bram_runs 0]
    reset_run $bram_run
    launch_runs $bram_run
    wait_on_run $bram_run
}

# Run synthesis
reset_run synth_1
launch_runs synth_1 -jobs 32
wait_on_run synth_1

if {[get_property STATUS [get_runs synth_1]] != "synth_design Complete!"} {
    puts "ERROR: Synthesis failed!"
    exit 1
}

# Run implementation (route_design only, then set SPI config before bitstream)
reset_run impl_1
launch_runs impl_1 -to_step route_design -jobs 32
wait_on_run impl_1

if {[get_property STATUS [get_runs impl_1]] != "route_design Complete!"} {
    puts "ERROR: Implementation failed!"
    exit 1
}

# Set SPI flash config (SPIx1 for Basys3)
open_run impl_1
set_property BITSTREAM.CONFIG.SPI_BUSWIDTH 1 [current_design]
set_property BITSTREAM.CONFIG.CONFIGRATE 33 [current_design]
write_bitstream -force [file join $project_dir ${project_name}.runs impl_1 basys3_top.bit]
close_design

puts "Build complete! Bitstream at:"
set bitstream_path [file join $project_dir ${project_name}.runs impl_1 basys3_top.bit]
puts $bitstream_path

# Generate MCS file (bitstream + fs.img)
set fs_img_path [file join $repo_root third_party xv6-riscv fs.img]
set mcs_file_path [file join $project_dir full_flash.mcs]
write_cfgmem -format mcs -interface SPIx1 -size 32 \
    -loadbit "up 0x00000000 $bitstream_path" \
    -loaddata "up 0x00300000 $fs_img_path" \
    -file $mcs_file_path -force
puts "MCS file created: $mcs_file_path"

close_project
