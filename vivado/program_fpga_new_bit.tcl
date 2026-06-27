# Program FPGA with new bitstream (no ILA, with SPI_BUSWIDTH=1)
set repo_root {G:/GitHub/26-Arch}
set bitstream_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.bit]

puts "=========================================="
puts "Programming FPGA with new bitstream..."
puts "=========================================="
puts "Bitstream: $bitstream_path"

if {![file exists $bitstream_path]} { puts "ERROR: bitstream missing"; exit 1 }

open_hw_manager
connect_hw_server -allow_non_jtag
open_hw_target

set device [get_hw_devices xc7a35t_0]
current_hw_device $device

set_property PROGRAM.FILE $bitstream_path $device
set_property PROBES.FILE "" $device
program_hw_devices $device

puts "=========================================="
puts "FPGA programmed OK! xv6 should be booting..."
puts "=========================================="

close_hw_target
disconnect_hw_server
