# ================================================================
# SPI Flash programming - try WITHOUT programming FPGA first
# Vivado should handle the bridge design automatically
# ================================================================

set repo_root {G:/GitHub/26-Arch}
set bitstream_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.bit]
set mcs_file_path [file join $repo_root vivado test-cpu project project_3 bitstream_only.mcs]

# Create MCS file from bitstream
if {[file exists $mcs_file_path]} {
    file delete $mcs_file_path
}
write_cfgmem -format mcs -interface spix1 -size 4 \
    -loadbit "up 0x0 $bitstream_path" \
    -force $mcs_file_path
puts "MCS file: $mcs_file_path ([file size $mcs_file_path] bytes)"

# Connect to hardware
open_hw
connect_hw_server
open_hw_target

set device [get_hw_devices xc7a35t_0]
current_hw_device $device

# Do NOT program FPGA first - let Vivado handle the bridge design

# Program SPI Flash
puts "Setting up SPI Flash..."
set cfgmem [create_hw_cfgmem -hw_device $device n25q32-3.3v-spi-x1_x2_x4]

set_property PROGRAM.ADDRESS_RANGE {use_file} $cfgmem
set_property PROGRAM.FILES [list $mcs_file_path] $cfgmem
set_property PROGRAM.UNUSED_PIN_TERMINATION {pull-none} $cfgmem
set_property PROGRAM.ERASE {1} $cfgmem
set_property PROGRAM.BLANK_CHECK {0} $cfgmem
set_property PROGRAM.CFG_PROGRAM {1} $cfgmem
set_property PROGRAM.VERIFY {1} $cfgmem

puts "PROGRAM.FILES = [get_property PROGRAM.FILES $cfgmem]"

puts "Programming SPI Flash..."
program_hw_cfgmem $cfgmem
puts "SPI Flash programmed!"

# Now program FPGA
puts "Programming FPGA..."
set_property PROGRAM.FILE $bitstream_path $device
program_hw_devices $device
puts "FPGA programmed!"

close_hw_target
disconnect_hw_server
close_hw

puts "DONE!"
