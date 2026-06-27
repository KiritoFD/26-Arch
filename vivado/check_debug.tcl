# Check FPGA debug signals via JTAG + ILA
# Usage: vivado -mode batch -source check_debug.tcl

set repo_root {G:/GitHub/26-Arch}
set bitstream_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.bit]
set ltx_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.ltx]

open_hw_manager
connect_hw_server -url localhost:3121 -allow_non_jtag

set targets [get_hw_targets -quiet]
if {[llength $targets] == 0} {
    puts "ERROR: No hardware targets found"
    exit 1
}

current_hw_target [lindex $targets 0]
open_hw_target

set dev [lindex [get_hw_devices] 0]
current_hw_device $dev

# Set the bitstream and probes file (for ILA debug core)
set_property PROGRAM.FILE $bitstream_path $dev
set_property PROBES.FILE $ltx_path $dev

# Refresh device to read current debug probe values
puts "Refreshing device to read debug probes..."
refresh_hw_device $dev

# List all debug cores
puts "=========================================="
puts "Debug Cores:"
puts "=========================================="
set dbg_cores [get_hw_debug_cores -quiet]
if {[llength $dbg_cores] > 0} {
    foreach core $dbg_cores {
        puts "  Core: $core"
    }
} else {
    puts "  No debug cores found"
}

# List all hw probes
puts "=========================================="
puts "HW Probes (current values):"
puts "=========================================="
set probes [get_hw_probes -quiet -of_objects [get_hw_debug_cores -quiet]]
if {[llength $probes] > 0} {
    foreach probe $probes {
        set val [get_property VALUE $probe]
        puts "  $probe = $val"
    }
} else {
    puts "  No probes found"
}

close_hw_target
disconnect_hw_server
close_hw_manager
