# ILA batch capture v5: correct write_hw_ila_data syntax
# Grammar: write_hw_ila_data [-force] <file> [<hw_ila_data>]
#   where hw_ila_data is returned by upload_hw_ila_data
set repo_root {G:/GitHub/26-Arch}
set bitstream_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.bit]
set ltx_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.ltx]
set ila_file "G:/GitHub/26-Arch/vivado/ila_capture_data.ila"
set csv_file "G:/GitHub/26-Arch/vivado/ila_capture_data.csv"

open_hw
connect_hw_server
open_hw_target

set device [get_hw_devices xc7a35t_0]
current_hw_device $device
set_property PROGRAM.FILE $bitstream_path $device
set_property PROBES.FILE $ltx_path $device

# Reprogram: CPU restarts from reset
puts "Reprogramming device..."
program_hw_devices $device
refresh_hw_device $device

set ila [lindex [get_hw_ilas -of_objects $device] 0]

# Configure trigger: cpu_tx falling edge (UART start bit)
puts "Configuring trigger: cpu_tx falling edge..."
set_property CONTROL.TRIGGER_POSITION 2048 $ila
# Set trigger condition: probe0 (cpu_tx) == 0, falling edge
set_property TRIGGER_SETUP "{probe0 == 0,FALLING} {} {} {}" $ila
puts "Trigger configured."

# Arm and wait
puts "Arming ILA..."
run_hw_ila $ila
puts "Waiting for trigger (cpu_tx falling edge)..."
# If CPU already finished UART output, this will timeout (no trigger)
wait_on_hw_ila $ila -timeout 20000
puts "wait_on_hw_ila done."

# Upload: returns hw_ila_data object
# Add delay to let ILA buffer stabilize before upload
puts "Waiting 500ms for buffer stabilize..."
after 500
puts "Uploading ILA data..."
set ila_data [upload_hw_ila_data $ila]
puts "Upload returned: $ila_data"

# Write binary .ila file
puts "Writing .ila file..."
write_hw_ila_data -force $ila_file $ila_data
puts "Wrote: $ila_file"

# Write CSV file
puts "Writing CSV file..."
catch {write_hw_ila_data -force -csv_file $csv_file $ila_data}
puts "Wrote: $csv_file"

# Write VCD file (different format, may avoid corruption issue)
set vcd_file "G:/GitHub/26-Arch/vivado/ila_capture_data.vcd"
puts "Writing VCD file..."
catch {write_hw_ila_data -force -vcd_file $vcd_file $ila_data}
puts "Wrote: $vcd_file"

# Print probe sample values from the uploaded data object
set probes [get_hw_probes -of_objects $ila]
puts "=========================================="
puts "Probe sample values:"
puts "=========================================="
foreach p $probes {
    set name [get_property NAME $p]
    set vals [get_property SAMPLE_VALUES $p]
    set nv [llength $vals]
    puts "Probe: $name ($nv samples)"
    if {$nv > 0} {
        set n [expr {$nv > 80 ? 80 : $nv}]
        puts "  first $n: [lrange $vals 0 [expr {$n-1}]]"
    }
}

close_hw_target
disconnect_hw_server
close_hw
