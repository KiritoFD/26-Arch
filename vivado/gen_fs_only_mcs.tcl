# ================================================================
# Generate MCS file containing ONLY fs.img (at offset 0x300000)
# and program SPI Flash (does NOT touch bitstream area at 0x0)
#
# This is used when FPGA already has a working bitstream loaded,
# and we only need to add fs.img to SPI Flash.
#
# Usage: vivado.bat -mode batch -source vivado\program_fs_only.tcl
# ================================================================

set repo_root {G:/GitHub/26-Arch}
set fs_img_path [file join $repo_root third_party xv6-riscv fs.img]
set mcs_file_path [file join $repo_root vivado test-cpu project project_3 fs_only.mcs]

puts "=========================================="
puts "Generate MCS (fs.img only) + Program SPI Flash"
puts "=========================================="
puts "fs.img:    $fs_img_path"
puts "MCS output: $mcs_file_path"
puts "fs.img offset: 0x00300000 (3MB, matches device.sv FLASH_DISK_OFFSET)"

# Verify fs.img exists
if {![file exists $fs_img_path]} {
    puts "ERROR: fs.img not found!"
    exit 1
}
puts "fs.img found. Proceeding..."

# ================================================================
# Step 1: Generate MCS file with ONLY fs.img (no bitstream)
# ================================================================
puts "=========================================="
puts "Step 1: Generating MCS file (fs.img only)..."
puts "=========================================="
write_cfgmem -format mcs -interface SPIx1 -size 32 \
    -loaddata "up 0x00300000 $fs_img_path" \
    -file $mcs_file_path \
    -force
puts "MCS file created: $mcs_file_path"

# ================================================================
# Step 2: Program SPI Flash (only fs.img region, NOT touching bitstream)
# ================================================================
puts "=========================================="
puts "Step 2: Programming SPI Flash..."
puts "=========================================="

open_hw
connect_hw_server
open_hw_target

set device [get_hw_devices xc7a35t_0]
current_hw_device $device

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
puts "DONE! fs.img programmed to SPI Flash."
puts "=========================================="
puts "Next: Press btnC to reset FPGA and verify xv6 boot."
puts "=========================================="
