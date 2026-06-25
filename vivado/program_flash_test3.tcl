# ================================================================
# SPI Flash programming with all required properties
# ================================================================

set repo_root {G:/GitHub/26-Arch}
set bitstream_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.bit]
set mcs_file_path [file join $repo_root vivado test-cpu project project_3 bitstream_only.mcs]

# Create MCS file from bitstream
if {[file exists $mcs_file_path]} {
    file delete $mcs_file_path
}
write_cfgmem -format mcs -interface spix1 -size 32 \
    -loadbit "up 0x0 $bitstream_path" \
    -force $mcs_file_path
puts "MCS file: $mcs_file_path ([file size $mcs_file_path] bytes)"

# Connect to hardware
open_hw
connect_hw_server
open_hw_target

set device [get_hw_devices xc7a35t_0]
current_hw_device $device

# Program FPGA first
puts "Programming FPGA..."
set_property PROGRAM.FILE $bitstream_path $device
program_hw_devices $device
puts "FPGA programmed!"

# Create cfgmem and set ALL required properties
puts "Setting up SPI Flash..."
set cfgmem [create_hw_cfgmem -hw_device $device n25q32-3.3v-spi-x1_x2_x4]

set_property PROGRAM.ADDRESS_RANGE {use_file} $cfgmem
set_property PROGRAM.FILES [list $mcs_file_path] $cfgmem
set_property PROGRAM.UNUSED_PIN_TERMINATION {pull-none} $cfgmem

# Set operation type: erase + program + verify
set_property PROGRAM.ERASE {1} $cfgmem
set_property PROGRAM.BLANK_CHECK {0} $cfgmem
set_property PROGRAM.CFG_PROGRAM {1} $cfgmem
set_property PROGRAM.VERIFY {1} $cfgmem

# Debug
puts "PROGRAM.FILES = [get_property PROGRAM.FILES $cfgmem]"
puts "PROGRAM.ERASE = [get_property PROGRAM.ERASE $cfgmem]"
puts "PROGRAM.CFG_PROGRAM = [get_property PROGRAM.CFG_PROGRAM $cfgmem]"

puts "Programming SPI Flash (this may take several minutes)..."
program_hw_cfgmem $cfgmem
puts "SPI Flash programmed!"

close_hw_target
disconnect_hw_server
close_hw

puts "DONE!"
