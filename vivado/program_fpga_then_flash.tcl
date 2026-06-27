# ================================================================
# Combined: Program FPGA with new bitstream (SPI_BUSWIDTH=1),
# then program SPI Flash.
#
# Theory: Vivado reads BITSTREAM.CONFIG.SPI_BUSWIDTH from the
# currently loaded bitstream to determine the SPI mode for the
# JTAG-SPI bridge. If the bitstream doesn't have this property,
# Vivado defaults to x4 mode, which fails on Basys3 (only 1 data pin).
#
# Usage: vivado.bat -mode batch -source program_fpga_then_flash.tcl
# ================================================================

set repo_root {G:/GitHub/26-Arch}
set bitstream_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.bit]
set mcs_file_path [file join $repo_root vivado test-cpu project project_3 full_flash.mcs]

puts "=========================================="
puts "Step 1: Program FPGA with new bitstream"
puts "  Bitstream: $bitstream_path"
puts "=========================================="

open_hw
connect_hw_server
open_hw_target

set device [get_hw_devices xc7a35t_0]
current_hw_device $device

# Program FPGA with new bitstream (has SPI_BUSWIDTH=1)
set_property PROGRAM.FILE $bitstream_path $device
set_property PROBES.FILE "" $device

puts "Programming FPGA..."
program_hw_devices $device
puts "FPGA programmed successfully!"

# Give it a moment
after 2000

# Read back CONFIG_VOLTAGE and SPI_BUSWIDTH from the device
puts "=== Device properties after programming ==="
catch {puts "  CONFIG_VOLTAGE = [get_property CONFIG_VOLTAGE $device]"}
catch {puts "  CFGBVS = [get_property CFGBVS $device]"}
catch {puts "  PROGRAM.FILE = [get_property PROGRAM.FILE $device]"}

# ================================================================
# Step 2: Program SPI Flash
# ================================================================
puts "=========================================="
puts "Step 2: Program SPI Flash"
puts "  MCS: $mcs_file_path"
puts "=========================================="

# Get the flash part
set parts [get_cfgmem_parts -of_objects $device]
set flash_part "n25q32-3.3v-spi-x1_x2_x4"
foreach p $parts {
    if {[string match "*n25q32*3.3v*" [string tolower $p]]} {
        set flash_part $p
        break
    }
}
puts "Flash part: $flash_part"

# Create config memory
set cfgmem [create_hw_cfgmem -hw_device $device $flash_part]

# Set program parameters
set_property PROGRAM.ADDRESS_RANGE {use_file} $cfgmem
set_property PROGRAM.FILES [list $mcs_file_path] $cfgmem
set_property PROGRAM.BLANK_CHECK  0 $cfgmem
set_property PROGRAM.ERASE        1 $cfgmem
set_property PROGRAM.CFG_PROGRAM  1 $cfgmem
set_property PROGRAM.VERIFY       0 $cfgmem

puts "PROGRAM.FILES = [get_property PROGRAM.FILES $cfgmem]"
puts "PROGRAM.ERASE = [get_property PROGRAM.ERASE $cfgmem]"
puts "PROGRAM.CFG_PROGRAM = [get_property PROGRAM.CFG_PROGRAM $cfgmem]"

# Program the flash
puts "=========================================="
puts "Programming SPI Flash..."
puts "=========================================="
set prog_result [catch {program_hw_cfgmem $cfgmem} prog_err]
if {$prog_result} {
    puts "ERROR: Flash programming failed!"
    puts "Error: $prog_err"
} else {
    puts "SUCCESS: SPI Flash programming complete!"
}

close_hw_target
disconnect_hw_server
close_hw
puts "Done."
