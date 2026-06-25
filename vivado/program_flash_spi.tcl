# Create MCS and program SPI Flash (bitstream already built)
# Usage: C:\Xilinx\Vivado\2019.2\bin\vivado.bat -mode batch -source program_flash_spi.tcl

set repo_root {G:/GitHub/26-Arch}
set bitstream_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.bit]
set fs_img_path [file join $repo_root third_party xv6-riscv fs.img]
set mcs_file_path [file join $repo_root vivado test-cpu project project_3 full_flash.mcs]

# ================================================================
# Step 1: Create MCS file (bitstream + fs.img)
# ================================================================
puts "=== Step 1: Create MCS file ==="
puts "  Bitstream: $bitstream_path"
puts "  fs.img:    $fs_img_path"
puts "  MCS output: $mcs_file_path"

write_cfgmem -format mcs -interface SPIx1 -size 32 \
    -loadbit "up 0x00000000 $bitstream_path" \
    -loaddata "up 0x00300000 $fs_img_path" \
    -file $mcs_file_path \
    -force

puts "MCS file created: $mcs_file_path"

# ================================================================
# Step 2: Program SPI Flash
# ================================================================
puts "=== Step 2: Program SPI Flash ==="
open_hw
connect_hw_server

# List and select targets
set targets [get_hw_targets]
puts "Found targets: $targets"
if {[llength $targets] == 0} {
    puts "ERROR: No JTAG targets found. Check USB connection and drivers."
    exit 1
}
current_hw_target [lindex $targets 0]
open_hw_target

set devices [get_hw_devices]
puts "Found devices: $devices"
if {[llength $devices] == 0} {
    puts "ERROR: No devices found."
    exit 1
}
set device [lindex $devices 0]
current_hw_device $device
puts "Using device: $device"

# Find flash part
set parts [get_cfgmem_parts -of_objects $device]
puts "Available flash parts: $parts"

set flash_part ""
foreach p $parts {
    if {[string match "*n25q*" [string tolower $p]] || [string match "*mt25q*" [string tolower $p]]} {
        set flash_part $p
        break
    }
}
if {$flash_part eq ""} {
    set flash_part [lindex $parts 0]
}
puts "Using flash part: $flash_part"

set cfgmem [create_hw_cfgmem -hw_device $device $flash_part]
set_property PROGRAM.ADDRESS_RANGE {use_file} $cfgmem
set_property PROGRAM.FILE $mcs_file_path $cfgmem

# Program flash
program_hw_cfgmem $cfgmem

puts "=== SPI Flash programming complete! ==="
puts "Press FPGA reset button (btnC) to start xv6."

close_hw_target
disconnect_hw_server
close_hw
