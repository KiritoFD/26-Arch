# ================================================================
# SPI Flash programming script for Basys3
# Programs MCS file containing bitstream + fs.img to N25Q032
# Then programs FPGA via JTAG
# ================================================================

set repo_root {G:/GitHub/26-Arch}
set mcs_file_path [file join $repo_root vivado test-cpu project project_3 full_flash.mcs]
set bitstream_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.bit]

# Verify files exist
if {![file exists $mcs_file_path]} {
    puts "ERROR: MCS file not found: $mcs_file_path"
    exit 1
}
if {![file exists $bitstream_path]} {
    puts "ERROR: Bitstream not found: $bitstream_path"
    exit 1
}
puts "MCS file: $mcs_file_path ([file size $mcs_file_path] bytes)"
puts "Bitstream: $bitstream_path ([file size $bitstream_path] bytes)"

# Connect to hardware
open_hw
connect_hw_server
open_hw_target

set device [get_hw_devices xc7a35t_0]
current_hw_device $device

# Step 1: Program FPGA with bitstream first
puts "Step 1: Programming FPGA with bitstream..."
set_property PROGRAM.FILE $bitstream_path $device
program_hw_devices $device
puts "FPGA programmed!"

# Step 2: Create config memory for SPI Flash (N25Q032)
puts "Step 2: Setting up SPI Flash programming..."
set flash_part "n25q32-3.3v-spi-x1_x2_x4"
puts "Using flash part: $flash_part"

set cfgmem [create_hw_cfgmem -hw_device $device $flash_part]

# Set MCS file for programming (use PROGRAM.FILES, NOT PROGRAM.FILE!)
set_property PROGRAM.ADDRESS_RANGE {use_file} $cfgmem
set_property PROGRAM.FILES [list $mcs_file_path] $cfgmem

# Step 3: Program SPI Flash
puts "Step 3: Programming SPI Flash (this may take several minutes)..."
program_hw_cfgmem $cfgmem

puts "SPI Flash programming complete!"

# Step 4: Re-program FPGA from JTAG (to ensure correct configuration)
puts "Step 4: Re-programming FPGA via JTAG..."
set_property PROGRAM.FILE $bitstream_path $device
program_hw_devices $device
puts "FPGA re-programmed!"

close_hw_target
disconnect_hw_server
close_hw

puts "=========================================="
puts "ALL DONE! Check serial output on COM4 (115200 baud)"
puts "Set SW0=OFF for CPU output mode"
puts "=========================================="
