# SPI Flash programming - v8 with explicit SPI_BUSWIDTH
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

# Check which PROGRAM properties exist
puts "=== Available PROGRAM properties ==="
foreach prop [list_property $cfgmem] {
    if {[string match "PROGRAM.*" $prop]} {
        puts "  $prop"
    }
}

# Try to set SPI_BUSWIDTH explicitly
puts "=== Setting SPI_BUSWIDTH ==="
set r1 [catch {set_property PROGRAM.SPI_BUSWIDTH 1 $cfgmem} msg1]
puts "SPI_BUSWIDTH: catch=$r1, msg=$msg1"

# Also try PROGRAM.SPI_MODE
set r2 [catch {set_property PROGRAM.SPI_MODE "SPIx1" $cfgmem} msg2]
puts "SPI_MODE: catch=$r2, msg=$msg2"

# Also try PROGRAM.INTERFACE
set r3 [catch {set_property PROGRAM.INTERFACE "SPIx1" $cfgmem} msg3]
puts "INTERFACE: catch=$r3, msg=$msg3"

# Set the file and program parameters
set_property PROGRAM.ADDRESS_RANGE {use_file} $cfgmem
set_property PROGRAM.FILES [list $mcs_file_path] $cfgmem
set_property PROGRAM.BLANK_CHECK  0 $cfgmem
set_property PROGRAM.ERASE        1 $cfgmem
set_property PROGRAM.CFG_PROGRAM  1 $cfgmem
set_property PROGRAM.VERIFY      0 $cfgmem

# Print final state
puts "=== Final cfgmem state ==="
foreach prop [list_property $cfgmem] {
    if {[string match "PROGRAM.*" $prop]} {
        set val [catch {get_property $prop $cfgmem} result]
        if {$val == 0} {
            puts "  $prop = $result"
        }
    }
}

# Program the flash
puts "Programming SPI Flash..."
program_hw_cfgmem $cfgmem
puts "SPI Flash programming complete!"

close_hw_target
disconnect_hw_server
close_hw
