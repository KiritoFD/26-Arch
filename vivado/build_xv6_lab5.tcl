# Build xv6 on lab5_project with proper package handling
# The key issue: Vivado needs to compile packages before modules that import them

set repo_root {G:/GitHub/26-Arch}
set project_path [file join $repo_root vivado lab5_project lab5_project.xpr]
set ip_dir [file join $repo_root vivado test-cpu project project_3 project_3.srcs sources_1 ip]

open_project $project_path

# Update compile order
update_compile_order -fileset sources_1

# Generate IP outputs (bram_0 was already updated with xv6 COE)
generate_target all [get_ips]

# Set verilog defines - we need VERILATOR to NOT be defined (default)
# But we need to ensure packages are compiled first

# Force compile order: packages first
# Vivado should auto-detect this from `import` statements
# But if it doesn't, we can set the compile order manually

# Check current sources
puts "Current sources:"
puts [get_files -of_objects [get_filesets sources_1] *.sv]

# Run synthesis with explicit top
reset_run synth_1
launch_runs synth_1 -jobs 4
wait_on_run synth_1

set synth_status [get_property STATUS [get_runs synth_1]]
puts "Synthesis status: $synth_status"

if {$synth_status != "synth_design Complete!"} {
    puts "ERROR: Synthesis failed! Checking log..."
    set log_file [file join $repo_root vivado lab5_project lab5_project.runs synth_1 basys3_top.vds]
    if {[file exists $log_file]} {
        set fp [open $log_file r]
        set content [read $fp]
        close $fp
        # Print last 50 lines
        set lines [split $content "\n"]
        set start [expr {max(0, [llength $lines] - 50)}]
        for {set i $start} {$i < [llength $lines]} {incr i} {
            puts [lindex $lines $i]
        }
    }
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
