# ================================================================
# SPI Flash programming - Step by step
# First test: program bitstream-only MCS to SPI Flash
# ================================================================

set repo_root {G:/GitHub/26-Arch}
set bitstream_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.bit]
set mcs_file_path [file join $repo_root vivado test-cpu project project_3 bitstream_only.mcs]

# Delete old MCS file
if {[file exists $mcs_file_path]} {
    file delete $mcs_file_path
}

# Step 1: Create MCS file from bitstream using Vivado's write_cfgmem
puts "Step 1: Creating MCS file from bitstream..."
write_cfgmem -format mcs -interface spix4 -size 32 \
    -loadbit "up 0x0 $bitstream_path" \
    -force $mcs_file_path

if {![file exists $mcs_file_path]} {
    puts "ERROR: Failed to create MCS file!"
    exit 1
}
puts "MCS file created: $mcs_file_path ([file size $mcs_file_path] bytes)"

# Step 2: Connect to hardware and program
puts "Step 2: Connecting to hardware..."
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

# Program SPI Flash
puts "Setting up SPI Flash programming..."
set cfgmem [create_hw_cfgmem -hw_device $device n25q32-3.3v-spi-x1_x2_x4]

# Debug: print cfgmem properties
puts "cfgmem: $cfgmem"
puts "Setting PROGRAM properties..."

set_property PROGRAM.ADDRESS_RANGE {use_file} $cfgmem
set_property PROGRAM.FILES [list $mcs_file_path] $cfgmem
set_property PROGRAM.UNUSED_PIN_TERMINATION {pull-none} $cfgmem

# Verify properties
set files [get_property PROGRAM.FILES $cfgmem]
puts "PROGRAM.FILES = $files"

puts "Programming SPI Flash..."
program_hw_cfgmem $cfgmem
puts "SPI Flash programmed!"

close_hw_target
disconnect_hw_server
close_hw

puts "DONE!"
