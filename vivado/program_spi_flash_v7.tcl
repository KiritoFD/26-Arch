# SPI Flash programming - v7 with PROGRAM.FILES fix
set repo_root {G:/GitHub/26-Arch}
set mcs_file_path [file join $repo_root vivado test-cpu project project_3 full_flash.mcs]

open_hw
connect_hw_server
open_hw_target

set device [get_hw_devices xc7a35t_0]
current_hw_device $device

# Get the flash part
set parts [get_cfgmem_parts -of_objects $device]
set flash_part "n25q32-3.3v-spi-x1_x2_x4"
foreach p $parts {
    if {[string match "*n25q32*3.3v*" [string tolower $p]]} {
        set flash_part $p
        break
    }
}
puts "Using flash part: $flash_part"

# Create config memory
set cfgmem [create_hw_cfgmem -hw_device $device $flash_part]

# Use PROGRAM.FILES (plural) instead of deprecated PROGRAM.FILE
set_property PROGRAM.ADDRESS_RANGE {use_file} $cfgmem
set_property PROGRAM.FILES [list $mcs_file_path] $cfgmem
set_property PROGRAM.BLANK_CHECK  0 $cfgmem
set_property PROGRAM.ERASE        1 $cfgmem
set_property PROGRAM.CFG_PROGRAM  1 $cfgmem
set_property PROGRAM.VERIFY      0 $cfgmem

# Print the FILES property to verify
puts "PROGRAM.FILES = [get_property PROGRAM.FILES $cfgmem]"
puts "PROGRAM.ERASE = [get_property PROGRAM.ERASE $cfgmem]"
puts "PROGRAM.CFG_PROGRAM = [get_property PROGRAM.CFG_PROGRAM $cfgmem]"

# Program the flash
puts "Programming SPI Flash..."
refresh_hw_device $device
program_hw_cfgmem $cfgmem
puts "SPI Flash programming complete!"

close_hw_target
disconnect_hw_server
close_hw
