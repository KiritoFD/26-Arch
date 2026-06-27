# SPI Flash programming - careful version
# Lists all available parts, finds N25Q32, and tries to program with SPIx1
set repo_root {G:/GitHub/26-Arch}
set mcs_file_path [file join $repo_root vivado test-cpu project project_3 full_flash.mcs]

puts "MCS file: $mcs_file_path"

open_hw
connect_hw_server
open_hw_target

set device [get_hw_devices xc7a35t_0]
current_hw_device $device

# Step 1: List all available flash parts
puts "=== Step 1: List available flash parts ==="
set parts [get_cfgmem_parts -of_objects $device]
puts "Total parts available: [llength $parts]"
set n25q_parts {}
foreach p $parts {
    set pl [string tolower $p]
    if {[string match "*n25q*" $pl]} {
        lappend n25q_parts $p
        puts "  N25Q part: $p"
    }
}

# Step 2: Find the correct part (prefer n25q32-3.3v-spi-x1_x2_x4)
puts "=== Step 2: Select flash part ==="
set flash_part ""
# First try: exact match for n25q32-3.3v-spi-x1_x2_x4
foreach p $n25q_parts {
    if {[string match "*n25q32*3.3v*" [string tolower $p]]} {
        set flash_part $p
        puts "Selected: $flash_part"
        break
    }
}
if {$flash_part eq ""} {
    foreach p $n25q_parts {
        set flash_part $p
        puts "Selected (fallback): $flash_part"
        break
    }
}
if {$flash_part eq ""} {
    puts "ERROR: No N25Q flash part found!"
    close_hw_target
    disconnect_hw_server
    close_hw
    exit 1
}

# Step 3: Create config memory
puts "=== Step 3: Create config memory ==="
set cfgmem [create_hw_cfgmem -hw_device $device $flash_part]
puts "Config memory created: $cfgmem"

# Print all properties of the cfgmem
puts "Config memory properties:"
foreach prop [list_property $cfgmem] {
    set val [catch {get_property $prop $cfgmem} result]
    if {$val == 0} {
        puts "  $prop = $result"
    }
}

# Step 4: Configure flash programming parameters
puts "=== Step 4: Configure flash parameters ==="
set_property PROGRAM.ADDRESS_RANGE {use_file} $cfgmem
set_property PROGRAM.FILE $mcs_file_path $cfgmem
set_property PROGRAM.BLANK_CHECK  0 $cfgmem
set_property PROGRAM.ERASE        1 $cfgmem
set_property PROGRAM.CFG_PROGRAM  1 $cfgmem
set_property PROGRAM.VERIFY      0 $cfgmem

# Try to set SPI mode to x1 if the property exists
catch {set_property PROGRAM.SPI_BUSWIDTH 1 $cfgmem}
catch {set_property PROGRAM.SPI_MODE {SPIx1} $cfgmem}

# Step 5: Program the flash
puts "=== Step 5: Program flash ==="
refresh_hw_device $device
catch {program_hw_cfgmem $cfgmem} result
puts "Program result: $result"

close_hw_target
disconnect_hw_server
close_hw
puts "Done."
