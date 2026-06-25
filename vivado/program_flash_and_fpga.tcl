# program_flash_and_fpga.tcl - Program SPI Flash with MCS, then load bitstream to FPGA
set repo_root {G:/GitHub/26-Arch}
set bitstream_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.bit]
set mcs_file_path [file join $repo_root vivado test-cpu project project_3 full_flash.mcs]

puts "=========================================="
puts "Programming SPI Flash + FPGA"
puts "  MCS: $mcs_file_path"
puts "  Bit: $bitstream_path"
puts "=========================================="

open_hw
connect_hw_server -url localhost:3121
open_hw_target

set device [get_hw_devices xc7a35t_0]
current_hw_device $device

# ================================================================
# Step 1: Program SPI Flash (N25Q032, 32Mbit=4MB) with MCS file
# ================================================================
puts "=========================================="
puts "Step 1: Programming SPI Flash..."
puts "=========================================="
set flash_part "n25q32-3.3v-spi-x1_x2_x4"
puts "Using flash part: $flash_part"
set cfgmem [create_hw_cfgmem -hw_device $device $flash_part]

set_property PROGRAM.ADDRESS_RANGE {use_file} $cfgmem
set_property PROGRAM.FILES [list $mcs_file_path] $cfgmem
set_property PROGRAM.ERASE 1 $cfgmem
set_property PROGRAM.VERIFY 1 $cfgmem

puts "Programming SPI Flash (erase + program + verify, ~5-10 minutes)..."
program_hw_cfgmem $cfgmem
puts "SPI Flash programming complete!"

# ================================================================
# Step 2: Program FPGA via JTAG with bitstream
# ================================================================
puts "=========================================="
puts "Step 2: Programming FPGA via JTAG..."
puts "=========================================="
set_property PROGRAM.FILE $bitstream_path $device
program_hw_devices $device
puts "FPGA programmed!"

close_hw_target
disconnect_hw_server
close_hw

puts "=========================================="
puts "ALL DONE! Press btnC to reset and start xv6."
puts "Then run: xsdb jtag_uart_console.tcl"
puts "=========================================="
