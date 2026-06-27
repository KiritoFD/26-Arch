# Capture ILA from already-programmed FPGA (Vivado 2019.2)
# Uses the exact syntax from check_ila.tcl that worked before.

set repo_root {G:/GitHub/26-Arch}
set ltx_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.ltx]
set ila_csv [file join $repo_root vivado ila_capture_v2.csv]

open_hw_manager
connect_hw_server -url localhost:3121 -allow_non_jtag

set targets [get_hw_targets -quiet]
if {[llength $targets] == 0} { puts "ERROR: No targets"; exit 1 }

current_hw_target [lindex $targets 0]
open_hw_target

set dev [lindex [get_hw_devices] 0]
current_hw_device $dev

# Set LTX file and refresh to load probe definitions
set_property PROBES.FILE $ltx_path $dev
refresh_hw_device $dev

set ilas [get_hw_ilas -quiet]
if {[llength $ilas] == 0} {
    puts "ERROR: No ILA core found!"
    close_hw_target
    disconnect_hw_server
    close_hw_manager
    exit 1
}

set ila_core [lindex $ilas 0]
puts "Found ILA: $ila_core"

# List probes
puts "Probes:"
set probes [get_hw_probes -quiet -of_objects $ila_core]
foreach probe $probes {
    puts "  [get_property NAME $probe]"
}

# Trigger immediately
run_hw_ila -trigger_now $ila_core
puts "ILA triggered, waiting 5 seconds..."
after 5000

# Upload ILA data
puts "Uploading ILA data..."
set hw_ila_data [upload_hw_ila $ila_core]
puts "Data object: $hw_ila_data"
wait_on_hw_ila $ila_core

# Save to CSV — try the syntax from check_ila.tcl
puts "Writing CSV..."
catch {write_hw_ila_data $hw_ila_data -force -csv -file $ila_csv} err1
puts "Syntax 1 result: $err1"

# Also try with current_hw_ila_data first
current_hw_ila_data $hw_ila_data
catch {write_hw_ila_data -force -csv -file $ila_csv} err2
puts "Syntax 2 result: $err2"

# Check if file exists
if {[file exists $ila_csv]} {
    puts "SUCCESS: CSV saved to $ila_csv ([file size $ila_csv] bytes)"
} else {
    puts "WARNING: CSV file not found at $ila_csv"
    # Try saving to current directory
    set local_csv "ila_capture_v2.csv"
    catch {write_hw_ila_data $hw_ila_data -force -csv -file $local_csv} err3
    puts "Syntax 3 (local) result: $err3"
    if {[file exists $local_csv]} {
        puts "SUCCESS: CSV saved to local: $local_csv ([file size $local_csv] bytes)"
    }
}

close_hw_target
disconnect_hw_server
close_hw_manager
puts "DONE"
