set repo_root {G:/GitHub/26-Arch}
set bitstream_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.bit]
set fs_img_path [file join $repo_root third_party xv6-riscv fs.img]
set mcs_file_path [file join $repo_root vivado test-cpu project project_3 full_flash.mcs]

open_project [file join $repo_root vivado test-cpu project project_3 project_3.xpr]

open_hw
connect_hw_server
open_hw_target

set device [get_hw_devices xc7a35t_0]
current_hw_device $device

puts "Programming FPGA with bitstream..."
set_property PROGRAM.FILE $bitstream_path $device
program_hw_devices $device
puts "FPGA programmed!"

puts "Creating MCS file..."
write_cfgmem -format mcs -interface qspi -size 32 \
    -loadbit "up 0x00000000 $bitstream_path" \
    -file $mcs_file_path \
    -force
puts "MCS file created: $mcs_file_path"

close_hw_target
disconnect_hw_server
close_hw
close_project

puts "Done! Now use Vivado Hardware Manager to program SPI Flash with the MCS file."