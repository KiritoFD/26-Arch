# ================================================================
# Program FPGA + Immediate ILA Capture (Vivado 2019.2)
# Based on the working check_ila.tcl approach.
#
# Usage:
#   C:\Xilinx\Vivado\2019.2\bin\vivado.bat -mode batch -source vivado\program_and_capture.tcl
# ================================================================

set repo_root {G:/GitHub/26-Arch}
set bitstream_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.bit]
set ltx_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.ltx]
set ila_csv [file join $repo_root vivado ila_capture_v2.csv]

# ================================================================
# Step 1: Open Hardware Manager and connect
# ================================================================
puts "=========================================="
puts "Step 1: Opening Hardware Manager..."
puts "=========================================="
open_hw_manager
connect_hw_server -url localhost:3121 -allow_non_jtag

set targets [get_hw_targets -quiet]
if {[llength $targets] == 0} {
    puts "ERROR: No hardware targets found!"
    close_hw_manager
    exit 1
}

current_hw_target [lindex $targets 0]
open_hw_target
puts "Connected to: [lindex $targets 0]"

# ================================================================
# Step 2: Program FPGA
# ================================================================
puts "=========================================="
puts "Step 2: Programming FPGA..."
puts "=========================================="
set device [lindex [get_hw_devices] 0]
current_hw_device $device

set_property PROGRAM.FILE $bitstream_path $device
set_property PROBES.FILE $ltx_path $device

program_hw_devices $device
puts "FPGA programmed successfully!"

# Refresh device to discover ILA with probe definitions
refresh_hw_device $device
puts "Device refreshed."

# ================================================================
# Step 3: Wait for CPU boot
# ================================================================
puts "=========================================="
puts "Step 3: Waiting 3 seconds for CPU boot..."
puts "=========================================="
after 3000

# ================================================================
# Step 4: ILA capture
# ================================================================
puts "=========================================="
puts "Step 4: Triggering ILA (immediate capture)..."
puts "=========================================="

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

# Wait for capture to complete (no refresh to avoid corruption)
puts "Waiting for ILA capture..."
after 5000

# Upload ILA data
puts "=========================================="
puts "Uploading ILA data..."
puts "=========================================="
set hw_ila_data [upload_hw_ila $ila_core]
puts "Data object: $hw_ila_data"

# Wait for upload to complete
wait_on_hw_ila $ila_core

# Save to CSV — try multiple syntaxes
current_hw_ila_data $hw_ila_data

# Syntax from check_ila.tcl (data object first, no -quiet)
catch {write_hw_ila_data $hw_ila_data -force -csv -file $ila_csv} err1
puts "Write syntax 1: $err1"

if {![file exists $ila_csv]} {
    # Try with -quiet
    catch {write_hw_ila_data -quiet -force -csv -file $ila_csv $hw_ila_data} err2
    puts "Write syntax 2: $err2"
}

if {![file exists $ila_csv]} {
    # Try without -csv
    set ila_ila [file join $repo_root vivado ila_capture_v2.ila]
    catch {write_hw_ila_data $hw_ila_data -force -file $ila_ila} err3
    puts "Write syntax 3 (ILA format): $err3"
}

if {[file exists $ila_csv]} {
    puts "SUCCESS: CSV saved to $ila_csv ([file size $ila_csv] bytes)"
} else {
    puts "WARNING: CSV file not found at $ila_csv"
    # Check current directory
    set cwd [pwd]
    puts "Current working directory: $cwd"
    set local_csv "ila_capture_v2.csv"
    catch {write_hw_ila_data $hw_ila_data -force -csv -file $local_csv} err4
    puts "Write to local dir: $err4"
    if {[file exists $local_csv]} {
        puts "SUCCESS: CSV saved to local: $local_csv ([file size $local_csv] bytes)"
        file copy -force $local_csv $ila_csv
    }
}

# ================================================================
# Step 5: Cleanup
# ================================================================
close_hw_target
disconnect_hw_server
close_hw_manager
puts "=========================================="
puts "CAPTURE COMPLETE!"
puts "CSV: $ila_csv"
puts "=========================================="
