set repo_root {G:/GitHub/26-Arch}
set bitstream_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.bit]
set fs_img_path [file join $repo_root third_party xv6-riscv fs.img]
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

puts "Writing fs.img to SPI Flash at offset 0x00400000..."

set fs_offset 0x00400000

set_property PROGRAM.FILE $bitstream_path $device
program_hw_devices $device

puts "Creating flash configuration file..."
write_cfgmem -format mcs -interface qspi -size 32 \
    -loadbit "up 0x00000000 $bitstream_path" \
    -loadbin "up 0x00400000 $fs_img_path" \
    -file [file join $repo_root vivado test-cpu project project_3 full_flash.mcs]

puts "MCS file created successfully!"

close_hw_target
disconnect_hw_server
close_hw