# ================================================================
# ILA Capture v4: Correct command order (Vivado 2019.2)
#
# Key fixes vs v3:
#   - wait_on_hw_ila BEFORE upload_hw_ila_data (not after)
#   - Use trigger condition (cpu_tx == 1, always true) instead of trigger_now
#     This ensures a proper trigger mark is set in the buffer
#   - Add after 500 for buffer stabilization before upload
#
# Usage:
#   C:\Xilinx\Vivado\2019.2\bin\vivado.bat -mode batch -source vivado\capture_v4.tcl
# ================================================================

set repo_root {G:/GitHub/26-Arch}
set bitstream_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.bit]
set ltx_path       [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.ltx]
set ila_file "G:/GitHub/26-Arch/vivado/ila_v4.ila"
set csv_file "G:/GitHub/26-Arch/vivado/ila_v4.csv"
set vcd_file "G:/GitHub/26-Arch/vivado/ila_v4.vcd"

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
# Step 2: Program FPGA (fresh CPU boot)
# ================================================================
puts "=========================================="
puts "Step 2: Programming FPGA..."
puts "=========================================="
set device [lindex [get_hw_devices] 0]
current_hw_device $device

set_property PROGRAM.FILE $bitstream_path $device
set_property PROBES.FILE  $ltx_path       $device

program_hw_devices $device
puts "FPGA programmed successfully!"

# Refresh device to discover ILA with probe definitions
refresh_hw_device $device
puts "Device refreshed."

# ================================================================
# Step 3: Wait for CPU boot attempt
# ================================================================
puts "=========================================="
puts "Step 3: Waiting 3 seconds for CPU boot..."
puts "=========================================="
after 3000

# ================================================================
# Step 4: Configure ILA trigger (always-true condition)
# ================================================================
puts "=========================================="
puts "Step 4: Configuring ILA trigger..."
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

# Set trigger: probe0 (cpu_tx) == 1 (always true since UART idle is high)
# This ensures the trigger fires immediately and sets a proper trigger mark
puts "Setting trigger: probe0 (cpu_tx) == 1..."
catch {set_property CONTROL.TRIGGER_POSITION 2048 $ila_core} err_pos
puts "  TRIGGER_POSITION: $err_pos"
# Trigger condition: probe0 == 1 (immediate trigger since cpu_tx is idle high)
catch {set_property TRIGGER_SETUP "{probe0 == 1} {} {} {} {} {} {} {}" $ila_core} err_trig
puts "  TRIGGER_SETUP: $err_trig"

# ================================================================
# Step 5: Arm ILA and wait for trigger
# ================================================================
puts "=========================================="
puts "Step 5: Arming ILA..."
puts "=========================================="
run_hw_ila $ila_core

# Wait for trigger (should fire immediately since cpu_tx == 1)
puts "Waiting for trigger (cpu_tx == 1, should fire immediately)..."
if {[catch {wait_on_hw_ila $ila_core -timeout 10000} err_wait]} {
    puts "wait_on_hw_ila returned: $err_wait"
    puts "Trigger may have timed out — uploading buffer anyway..."
} else {
    puts "Trigger completed."
}

# Buffer stabilization delay
puts "Buffer stabilization (500ms)..."
after 500

# ================================================================
# Step 6: Upload ILA data
# ================================================================
puts "=========================================="
puts "Step 6: Uploading ILA data..."
puts "=========================================="
# upload_hw_ila_data returns the data object (e.g. hw_ila_data_1)
if {[catch {set ila_data [upload_hw_ila_data $ila_core]} err_upload]} {
    puts "ERROR uploading: $err_upload"
    # Try refreshing device and retrying
    puts "Refreshing device and retrying..."
    refresh_hw_device $device
    after 1000
    if {[catch {set ila_data [upload_hw_ila_data $ila_core]} err_upload2]} {
        puts "ERROR retry upload: $err_upload2"
        close_hw_target
        disconnect_hw_server
        close_hw_manager
        exit 1
    }
}
puts "Upload returned: $ila_data"

# ================================================================
# Step 7: Save to files (CORRECT SYNTAX)
# ================================================================
puts "=========================================="
puts "Step 7: Writing ILA data to files..."
puts "=========================================="

# .ila binary format
puts "Writing .ila binary..."
if {[catch {write_hw_ila_data -force $ila_file $ila_data} err_ila]} {
    puts "  .ila ERROR: $err_ila"
} else {
    puts "  .ila written: $ila_file ([file size $ila_file] bytes)"
}

# CSV format — use -csv_file (single option, NOT -csv -file)
puts "Writing CSV..."
if {[catch {write_hw_ila_data -force -csv_file $csv_file $ila_data} err_csv]} {
    puts "  CSV ERROR: $err_csv"
} else {
    puts "  CSV written: $csv_file ([file size $csv_file] bytes)"
}

# VCD format (fallback)
puts "Writing VCD..."
if {[catch {write_hw_ila_data -force -vcd_file $vcd_file $ila_data} err_vcd]} {
    puts "  VCD ERROR: $err_vcd"
} else {
    puts "  VCD written: $vcd_file ([file size $vcd_file] bytes)"
}

# ================================================================
# Step 8: Print probe sample values directly to stdout
# (so we can see the values even if file save fails)
# ================================================================
puts "=========================================="
puts "Step 8: Probe sample values (direct stdout)"
puts "=========================================="
set probes [get_hw_probes -of_objects $ila_core]
foreach p $probes {
    set name [get_property NAME $p]
    set vals [get_property SAMPLE_VALUES $p]
    set nv [llength $vals]
    puts "Probe: $name ($nv samples)"
    if {$nv > 0} {
        set n [expr {$nv > 20 ? 20 : $nv}]
        puts "  first $n: [lrange $vals 0 [expr {$n-1}]]"
        if {$nv > 20} {
            set mid [expr {$nv / 2}]
            puts "  middle: [lrange $vals $mid [expr {$mid+9}]]"
            puts "  last 10: [lrange $vals [expr {$nv-10}] [expr {$nv-1}]]"
        }
    }
}

# ================================================================
# Step 9: Cleanup
# ================================================================
close_hw_target
disconnect_hw_server
close_hw_manager
puts "=========================================="
puts "CAPTURE COMPLETE!"
puts "  .ila: $ila_file"
puts "  .csv: $csv_file"
puts "  .vcd: $vcd_file"
puts "=========================================="
