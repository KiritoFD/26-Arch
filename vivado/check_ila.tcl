# Check FPGA debug signals via JTAG + ILA (Vivado 2019.2)
set repo_root {G:/GitHub/26-Arch}
set bitstream_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.bit]
set ltx_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.ltx]
set ila_csv [file join $repo_root vivado ila_capture.csv]
set ila_vcd [file join $repo_root vivado ila_capture.vcd]

open_hw_manager
connect_hw_server -url localhost:3121 -allow_non_jtag

set targets [get_hw_targets -quiet]
if {[llength $targets] == 0} { puts "ERROR: No targets"; exit 1 }

current_hw_target [lindex $targets 0]
open_hw_target

set dev [lindex [get_hw_devices] 0]
current_hw_device $dev
set_property PROGRAM.FILE $bitstream_path $dev
set_property PROBES.FILE $ltx_path $dev

refresh_hw_device $dev
set ilas [get_hw_ilas -quiet]
set ila_core [lindex $ilas 0]

# List probes
puts "=========================================="
puts "Probes:"
set probes [get_hw_probes -quiet -of_objects $ila_core]
foreach probe $probes {
    puts "  [get_property NAME $probe]"
}

# Run ILA capture
puts "=========================================="
puts "Running ILA capture..."
run_hw_ila $ila_core

# Wait for trigger
puts "Waiting for trigger..."
after 2000
refresh_hw_device $dev

# Upload ILA data (returns data object)
puts "=========================================="
puts "Uploading ILA data..."
set hw_ila_data [upload_hw_ila $ila_core]
puts "Data object: $hw_ila_data"

# Wait for upload to complete
wait_on_hw_ila $ila_core

# Write to CSV (Vivado 2019.2 syntax: data object first, then options)
puts "=========================================="
puts "Writing ILA data..."
write_hw_ila_data $hw_ila_data -force -csv -file $ila_csv
puts "CSV written: $ila_csv"

# Also write as VCD (try without -csv to avoid option conflict)
catch {write_hw_ila_data $hw_ila_data -force -file $ila_vcd}
puts "VCD attempt done"

close_hw_target
disconnect_hw_server
close_hw_manager
