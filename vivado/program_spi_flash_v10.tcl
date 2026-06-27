# ================================================================
# SPI Flash programming - v10
# KEY FIX: Set CONFIG_VOLTAGE and CFGBVS on hw_device
#   Basys3 uses 3.3V config voltage, but Vivado defaults to 1.8V
#   when not specified in the bitstream. This causes the JTAG-SPI
#   bridge to fail communicating with the N25Q032 flash chip,
#   producing "Failure to set flash parameters" (Labtools 27-3347).
#
# Also includes comprehensive diagnostics.
# ================================================================

set repo_root {G:/GitHub/26-Arch}
set mcs_file_path [file join $repo_root vivado test-cpu project project_3 full_flash.mcs]

puts "=========================================="
puts "SPI Flash Programming v10"
puts "  MCS file: $mcs_file_path"
puts "=========================================="

open_hw
connect_hw_server
open_hw_target

set device [get_hw_devices xc7a35t_0]
current_hw_device $device

# ================================================================
# DIAGNOSTIC: Print device properties BEFORE fix
# ================================================================
puts "=== Device properties (BEFORE fix) ==="
catch {puts "  CONFIG_VOLTAGE = [get_property CONFIG_VOLTAGE $device]"}
catch {puts "  CFGBVS = [get_property CFGBVS $device]"}
catch {puts "  PROGRAM.FILE = [get_property PROGRAM.FILE $device]"}
catch {puts "  PROBES.FILE = [get_property PROBES.FILE $device]"}

# ================================================================
# FIX 1: Set CONFIG_VOLTAGE and CFGBVS on the device
# ================================================================
puts "=== Setting CONFIG_VOLTAGE=3.3 and CFGBVS=VCCAUX ==="
set r1 [catch {set_property CONFIG_VOLTAGE 3.3 $device} err1]
set r2 [catch {set_property CFGBVS VCCAUX $device} err2]
if {$r1} { puts "  CONFIG_VOLTAGE set FAILED: $err1" } else { puts "  CONFIG_VOLTAGE set OK" }
if {$r2} { puts "  CFGBVS set FAILED: $err2" } else { puts "  CFGBVS set OK" }

# Clear probes file to avoid ILA interference
set_property PROBES.FILE "" $device
set_property PROGRAM.FILE "" $device

# Print device properties AFTER fix
puts "=== Device properties (AFTER fix) ==="
catch {puts "  CONFIG_VOLTAGE = [get_property CONFIG_VOLTAGE $device]"}
catch {puts "  CFGBVS = [get_property CFGBVS $device]"}

# ================================================================
# Get the flash part
# ================================================================
set parts [get_cfgmem_parts -of_objects $device]
puts "=== Available flash parts (N25Q only) ==="
set flash_part "n25q32-3.3v-spi-x1_x2_x4"
foreach p $parts {
    if {[string match "*n25q32*3.3v*" [string tolower $p]]} {
        set flash_part $p
        puts "  Selected: $p"
        break
    }
}
# Also list ALL n25q parts for reference
foreach p $parts {
    if {[string match "*n25q*" [string tolower $p]]} {
        puts "  Available: $p"
    }
}

# ================================================================
# Create config memory
# ================================================================
puts "=== Creating config memory: $flash_part ==="
set cfgmem [create_hw_cfgmem -hw_device $device $flash_part]

# ================================================================
# DIAGNOSTIC: Print ALL cfgmem properties
# ================================================================
puts "=== Config memory properties ==="
foreach prop [list_property $cfgmem] {
    set val [catch {get_property $prop $cfgmem} result]
    if {$val == 0 && $result ne ""} {
        puts "  $prop = $result"
    }
}

# ================================================================
# Set ALL program parameters
# ================================================================
set_property PROGRAM.ADDRESS_RANGE {use_file} $cfgmem
set_property PROGRAM.FILES [list $mcs_file_path] $cfgmem
set_property PROGRAM.BLANK_CHECK  0 $cfgmem
set_property PROGRAM.ERASE        1 $cfgmem
set_property PROGRAM.CFG_PROGRAM  1 $cfgmem
set_property PROGRAM.VERIFY       0 $cfgmem

# Print final configuration
puts "=== Final flash programming config ==="
puts "  PROGRAM.FILES = [get_property PROGRAM.FILES $cfgmem]"
puts "  PROGRAM.ERASE = [get_property PROGRAM.ERASE $cfgmem]"
puts "  PROGRAM.CFG_PROGRAM = [get_property PROGRAM.CFG_PROGRAM $cfgmem]"

# ================================================================
# Program the flash
# ================================================================
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
