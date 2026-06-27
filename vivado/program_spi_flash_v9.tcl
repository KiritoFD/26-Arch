# SPI Flash programming - v9 without refresh
# Theory: refresh_hw_device tries to read ILA data, which might interfere with flash setup
set repo_root {G:/GitHub/26-Arch}
set mcs_file_path [file join $repo_root vivado test-cpu project project_3 full_flash.mcs]

open_hw
connect_hw_server
open_hw_target

set device [get_hw_devices xc7a35t_0]
current_hw_device $device

# Clear PROBES.FILE to avoid ILA mismatch warnings
set_property PROBES.FILE "" $device

# Get the flash part
set flash_part "n25q32-3.3v-spi-x1_x2_x4"
set parts [get_cfgmem_parts -of_objects $device]
foreach p $parts {
    if {[string match "*n25q32*3.3v*" [string tolower $p]]} {
        set flash_part $p
        break
    }
}
puts "Using flash part: $flash_part"

# Create config memory
set cfgmem [create_hw_cfgmem -hw_device $device $flash_part]

# Set program parameters
set_property PROGRAM.ADDRESS_RANGE {use_file} $cfgmem
set_property PROGRAM.FILES [list $mcs_file_path] $cfgmem
set_property PROGRAM.BLANK_CHECK  0 $cfgmem
set_property PROGRAM.ERASE        1 $cfgmem
set_property PROGRAM.CFG_PROGRAM  1 $cfgmem
set_property PROGRAM.VERIFY      0 $cfgmem

# Program WITHOUT refresh_hw_device first
puts "Programming SPI Flash (no refresh)..."
catch {program_hw_cfgmem $cfgmem} result
puts "Result: $result"

if {[string match "*ERROR*" $result] || [string match "*failed*" $result]} {
    # Try with refresh
    puts "=== Retrying with refresh ==="
    refresh_hw_device $device
    catch {program_hw_cfgmem $cfgmem} result2
    puts "Result2: $result2"
}

close_hw_target
disconnect_hw_server
close_hw
puts "Done."
