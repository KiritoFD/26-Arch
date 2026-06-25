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

puts "Writing full flash image to QSPI flash..."
set flash [get_hw_flash_devices xcfup32_0]
if {[llength $flash] == 0} {
    puts "WARNING: No flash device found. Trying to get flash devices..."
    set flash [get_hw_flash_devices]
    puts "Available flash devices: $flash"
}

if {[llength $flash] > 0} {
    current_hw_flash_device $flash
    set_property PROGRAM.FILE $flash_bin_path $flash
    program_hw_flash $flash
    puts "SPI Flash programming complete!"
} else {
    puts "ERROR: No SPI flash device found!"
}

close_hw_target
disconnect_hw_server
close_hw