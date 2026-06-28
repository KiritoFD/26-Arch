# Program the FPGA with xv6_project bitstream (no ILA)
set repo_root {G:/GitHub/26-Arch}
set bitstream [file join $repo_root vivado xv6_project xv6_project.runs impl_1 basys3_top.bit]

if {![file exists $bitstream]} {
    puts "ERROR: bitstream not found: $bitstream"
    exit 1
}
puts "BITSTREAM=$bitstream"
puts "BIT_SIZE=[file size $bitstream]"

open_hw
connect_hw_server
open_hw_target

set device [lindex [get_hw_devices] 0]
current_hw_device $device
set_property PROGRAM.FILE $bitstream $device

program_hw_devices $device

puts "FPGA programmed successfully"

close_hw_target
disconnect_hw_server
close_hw

puts "ALL_DONE"
exit
