# ================================================================
# Simple SPI Flash programming for Basys3 (N25Q32)
# Strategy: Program FPGA first (provides SPI_BUSWIDTH from bitstream),
#           then program SPI Flash.
#
# Usage: vivado.bat -mode batch -source vivado\program_spi_flash_simple.tcl
# ================================================================

set repo_root {G:/GitHub/26-Arch}
set bitstream_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.bit]
set mcs_file_path [file join $repo_root vivado test-cpu project project_3 full_flash.mcs]

puts "=========================================="
puts "SPI Flash Programming (Simple)"
puts "=========================================="
puts "Bitstream: $bitstream_path"
puts "MCS:       $mcs_file_path"

# Verify files exist
if {![file exists $bitstream_path]} {
    puts "ERROR: Bitstream not found!"
    exit 1
}
if {![file exists $mcs_file_path]} {
    puts "ERROR: MCS file not found!"
    exit 1
}
puts "Both files exist. Proceeding..."

open_hw
connect_hw_server
open_hw_target

set device [get_hw_devices xc7a35t_0]
current_hw_device $device

# ================================================================
# Step 1: Program FPGA with bitstream
# (This tells Vivado the SPI bus width from BITSTREAM.CONFIG.SPI_BUSWIDTH)
# ================================================================
puts "=========================================="
puts "Step 1: Programming FPGA..."
puts "=========================================="
set_property PROGRAM.FILE $bitstream_path $device
set_property PROBES.FILE "" $device
program_hw_devices $device
puts "FPGA programmed successfully!"

# ================================================================
# Step 2: Program SPI Flash
# ================================================================
puts "=========================================="
puts "Step 2: Programming SPI Flash..."
puts "=========================================="

# Find N25Q32 flash part
set parts [get_cfgmem_parts -of_objects $device]
set flash_part ""
foreach p $parts {
    set pl [string tolower $p]
    if {[string match "*n25q32*3.3v*" $pl]} {
        set flash_part $p
        puts "Selected flash part: $flash_part"
        break
    }
}
if {$flash_part eq ""} {
    foreach p $parts {
        set pl [string tolower $p]
        if {[string match "*n25q*" $pl]} {
            set flash_part $p
            puts "Selected flash part (fallback): $flash_part"
            break
        }
    }
}
if {$flash_part eq ""} {
    puts "ERROR: No N25Q flash part found!"
    close_hw_target
    disconnect_hw_server
    close_hw
    exit 1
}

# Create config memory
set cfgmem [create_hw_cfgmem -hw_device $device $flash_part]

# Configure flash programming parameters
set_property PROGRAM.ADDRESS_RANGE {use_file} $cfgmem
set_property PROGRAM.FILES [list $mcs_file_path] $cfgmem
set_property PROGRAM.BLANK_CHECK 0 $cfgmem
set_property PROGRAM.ERASE        1 $cfgmem
set_property PROGRAM.CFG_PROGRAM  1 $cfgmem
set_property PROGRAM.VERIFY       0 $cfgmem

# Print configuration
puts "Flash configuration:"
puts "  Part:        $flash_part"
puts "  MCS file:    $mcs_file_path"
puts "  ERASE:       [get_property PROGRAM.ERASE $cfgmem]"
puts "  CFG_PROGRAM: [get_property PROGRAM.CFG_PROGRAM $cfgmem]"

# Program the flash
puts "Programming SPI Flash (this may take a few minutes)..."
refresh_hw_device $device
program_hw_cfgmem $cfgmem
puts "SPI Flash programming complete!"

close_hw_target
disconnect_hw_server
close_hw

puts "=========================================="
puts "DONE! SPI Flash programmed successfully."
puts "=========================================="
puts "Next: Press btnC to reset FPGA and verify xv6 boot."
puts "=========================================="
