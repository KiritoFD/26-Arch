# program_flash_v3.tcl - Minimal SPI Flash programming (no ERASE/VERIFY flags)
set repo_root {G:/GitHub/26-Arch}
set mcs_file_path [file join $repo_root vivado test-cpu project project_3 full_flash.mcs]
set bitstream_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.bit]

open_hw
connect_hw_server -url localhost:3121
open_hw_target

set device [get_hw_devices xc7a35t_0]
current_hw_device $device

# Step 1: Program FPGA first (provides bridge to SPI Flash)
puts "Step 1: Programming FPGA..."
set_property PROGRAM.FILE $bitstream_path $device
program_hw_devices $device
puts "FPGA programmed!"

# Step 2: Create cfgmem with minimal settings
puts "Step 2: Creating cfgmem..."
set cfgmem [create_hw_cfgmem -hw_device $device "n25q32-3.3v-spi-x1_x2_x4"]

# List all available properties and their defaults
puts "=== cfgmem properties ==="
foreach p [list_property $cfgmem] {
    catch {set val [get_property $p $cfgmem]}
    if {[info exists val]} {
        puts "  $p = $val"
    }
}

# Set minimal properties - only FILES and ADDRESS_RANGE
set_property PROGRAM.ADDRESS_RANGE {use_file} $cfgmem
set_property PROGRAM.FILES [list $mcs_file_path] $cfgmem

# Do NOT set ERASE/VERIFY/CFG_PROGRAM - let program_hw_cfgmem handle defaults
puts "Step 3: Programming SPI Flash (minimal settings)..."
program_hw_cfgmem $cfgmem
puts "SPI Flash programming complete!"

close_hw_target
disconnect_hw_server
close_hw

puts "=========================================="
puts "ALL DONE! Press btnC to reset."
puts "=========================================="
