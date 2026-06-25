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

# Update BRAM IP with xv6 kernel COE
set coe_path [file join $repo_root ready-to-run lab5 xv6-kernel.coe]

# Update BRAM IP to use xv6 kernel
set bram_ip [get_ips bram_0]
set_property -dict [list \
    CONFIG.Coe_File $coe_path \
    CONFIG.Load_Init_File {true} \
] $bram_ip

# Generate IP output products
generate_target all [get_ips]

# Run synthesis
reset_run synth_1
launch_runs synth_1 -jobs 4
wait_on_run synth_1

if {[get_property STATUS [get_runs synth_1]] != "synth_design Complete!"} {
    puts "ERROR: Synthesis failed!"
    exit 1
}

# Run implementation
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
puts [file join $project_dir ${project_name}.runs impl_1 basys3_top.bit]

close_project
