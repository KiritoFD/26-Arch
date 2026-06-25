# Build xv6 on lab5_project - use XCI instead of DCP
# Step 1: Replace DCP references with XCI in project
# Step 2: Run synthesis + implementation + bitstream

set repo_root {G:/GitHub/26-Arch}
set project_path [file join $repo_root vivado lab5_project lab5_project.xpr]
set ip_dir [file join $repo_root vivado test-cpu project project_3 project_3.srcs sources_1 ip]

open_project $project_path

# Remove old DCP references and add XCI instead
# First, remove the old bram_0.dcp file reference
remove_files [get_files */bram_0.dcp]
remove_files [get_files */bram_0_stub.v]

# Add the new XCI file
add_files -norecurse [file join $ip_dir bram_0 bram_0.xci]

# Also remove old clk_wiz DCP and add XCI
remove_files [get_files */clk_wiz_0.dcp]
remove_files [get_files */clk_wiz_0_stub.v]
add_files -norecurse [file join $ip_dir clk_wiz_0 clk_wiz_0.xci]

# Update compile order
update_compile_order -fileset sources_1

# Generate all IP outputs
generate_target all [get_ips]

# Run synthesis
reset_run synth_1
launch_runs synth_1 -jobs 4
wait_on_run synth_1

if {[get_property STATUS [get_runs synth_1]] != "synth_design Complete!"} {
    puts "ERROR: Synthesis failed!"
    exit 1
}
puts "Synthesis complete!"

# Run implementation
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
puts [file join $repo_root vivado lab5_project lab5_project.runs impl_1 basys3_top.bit]

close_project
