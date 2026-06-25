# ================================================================
# Program FPGA via JTAG (Vivado 2018.3 compatible)
# ================================================================

set repo_root {G:/GitHub/26-Arch}
set bitstream_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.bit]

open_hw
connect_hw_server

# Give server time to discover targets
after 3000

set targets [get_hw_targets]
puts "Targets: $targets"

if {[llength $targets] == 0} {
    puts "Trying refresh..."
    refresh_hw_server
    after 3000
    set targets [get_hw_targets]
    puts "After refresh - Targets: $targets"
}

if {[llength $targets] == 0} {
    puts "ERROR: No JTAG targets found! Check USB and try replugging."
    close_hw
    exit 1
}

open_hw_target [lindex $targets 0]

set device [get_hw_devices xc7a35t_0]
current_hw_device $device

puts "Programming FPGA..."
set_property PROGRAM.FILE $bitstream_path $device
program_hw_devices $device
puts "FPGA programmed!"

close_hw_target
disconnect_hw_server
close_hw

puts "=========================================="
puts "FPGA programmed! Use jtag_uart_bridge.py to see output"
puts "=========================================="
