set repo_root {G:/GitHub/26-Arch}
set bitstream_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.bit]
set flash_bin_path [file join $repo_root vivado test-cpu project project_3 full_flash.bin]

open_hw
connect_hw_server
open_hw_target

set device [get_hw_devices xc7a35t_0]
current_hw_device $device

puts "Programming FPGA with bitstream..."
set_property PROGRAM.FILE $bitstream_path $device
program_hw_devices $device
puts "FPGA programmed!"

puts "\nWriting SPI Flash using jtagspi..."

set_property PROGRAM.FILE $flash_bin_path $device
program_hw_devices $device

puts "SPI Flash programming complete!"

close_hw_target
disconnect_hw_server
close_hw