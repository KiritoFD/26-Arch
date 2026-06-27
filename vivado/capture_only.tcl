# ================================================================
# Capture-only ILA script (FPGA must already be programmed)
# Connects to the board, triggers ILA immediately, saves CSV.
#
# Usage:
#   C:\Xilinx\Vivado\2019.2\bin\vivado.bat -mode batch -source vivado\capture_only.tcl
# ================================================================

set repo_root {G:/GitHub/26-Arch}
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

set device [lindex [get_hw_devices] 0]
current_hw_device $device

# Refresh to discover ILA
refresh_hw_device $device
puts "Device refreshed."

# ================================================================
# Step 2: Find ILA and trigger immediately
# ================================================================
puts "=========================================="
puts "Step 2: Triggering ILA..."
puts "=========================================="

set ila [get_hw_ilas -quiet]
if {[llength $ila] == 0} {
    puts "ERROR: No ILA core found!"
    close_hw_target
    disconnect_hw_server
    close_hw_manager
    exit 1
}

puts "Found ILA: $ila"
current_hw_ila [lindex $ila 0]

# Trigger immediately (capture current state)
run_hw_ila -trigger_now [lindex $ila 0]

# Wait for capture to complete
puts "Waiting for ILA capture..."
set timeout 30
set elapsed 0
while {$elapsed < $timeout} {
    set status [get_property STATUS [lindex $ila 0]]
    if {$status eq "IDLE"} {
        puts "ILA capture complete!"
        break
    }
    after 1000
    incr elapsed
    puts "  Status: $status (${elapsed}s / ${timeout}s)"
}

if {$elapsed >= $timeout} {
    puts "WARNING: ILA capture timed out!"
}

# ================================================================
# Step 3: Upload and save ILA data
# ================================================================
puts "=========================================="
puts "Step 3: Uploading ILA data..."
puts "=========================================="

set hw_ila_data [upload_hw_ila [lindex $ila 0]]
puts "ILA data uploaded: $hw_ila_data"

# Save to CSV (correct Vivado 2019.2 syntax)
current_hw_ila_data $hw_ila_data
write_hw_ila_data -quiet -force -csv -file $ila_csv $hw_ila_data
puts "ILA data saved to: $ila_csv"

# ================================================================
# Step 4: Cleanup
# ================================================================
close_hw_target
disconnect_hw_server
close_hw_manager
puts "=========================================="
puts "CAPTURE COMPLETE!"
puts "CSV: $ila_csv"
puts "=========================================="
