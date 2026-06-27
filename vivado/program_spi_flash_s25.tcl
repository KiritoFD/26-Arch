# Program SPI Flash using correct part: s25fl032p
set repo_root {G:/GitHub/26-Arch}
set bitstream_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.bit]
set mcs_file_path [file join $repo_root vivado test-cpu project project_3 full_flash.mcs]

puts "=========================================="
puts "SPI Flash Programming with S25FL032P"
puts "=========================================="

if {![file exists $bitstream_path]} { puts "ERROR: bitstream missing"; exit 1 }
if {![file exists $mcs_file_path]} { puts "ERROR: mcs missing"; exit 1 }

open_hw_manager
connect_hw_server -allow_non_jtag
open_hw_target

set device [get_hw_devices xc7a35t_0]
current_hw_device $device

# Step 1: Program FPGA with bitstream first (must be loaded for flash bridge)
puts "Step 1: Programming FPGA..."
set_property PROGRAM.FILE $bitstream_path $device
set_property PROBES.FILE "" $device
program_hw_devices $device
puts "FPGA programmed OK."

# Step 2: Find S25FL032P parts
puts "=========================================="
puts "Searching for S25FL032P parts:"
set all_parts [get_cfgmem_parts -of_objects $device]
set s25_parts [list]
foreach p $all_parts {
    set pl [string tolower $p]
    if {[string match "*s25fl032*" $pl] || [string match "*s25fl032p*" $pl]} {
        puts "  - $p"
        lappend s25_parts $p
    }
}
puts "=========================================="

if {[llength $s25_parts] == 0} {
    puts "ERROR: No S25FL032P part found!"
    # List all Spansion parts as fallback
    puts "All Spansion parts available:"
    foreach p $all_parts {
        set pl [string tolower $p]
        if {[string match "*s25*" $pl] || [string match "*spansion*" $pl]} {
            puts "  - $p"
        }
    }
    close_hw_target
    disconnect_hw_server
    exit 1
}

set success 0
foreach flash_part $s25_parts {
    puts "=========================================="
    puts "Trying part: $flash_part"
    puts "=========================================="

    catch {
        set existing [get_hw_cfgmems -of $device]
        if {[llength $existing] > 0} {
            delete_hw_cfgmem $existing
        }
    }

    set rc [catch {
        set cfgmem [create_hw_cfgmem -hw_device $device $flash_part]
        set_property PROGRAM.ADDRESS_RANGE {use_file} $cfgmem
        set_property PROGRAM.FILES [list $mcs_file_path] $cfgmem
        set_property PROGRAM.BLANK_CHECK 0 $cfgmem
        set_property PROGRAM.ERASE        1 $cfgmem
        set_property PROGRAM.CFG_PROGRAM  1 $cfgmem
        set_property PROGRAM.VERIFY       0 $cfgmem

        puts "Properties: ERASE=[get_property PROGRAM.ERASE $cfgmem] CFG_PROGRAM=[get_property PROGRAM.CFG_PROGRAM $cfgmem]"
        refresh_hw_device $device
        program_hw_cfgmem $cfgmem
    } err]

    if {$rc == 0} {
        puts "SUCCESS with $flash_part!"
        set success 1
        break
    } else {
        puts "FAILED with $flash_part: $err"
    }
}

if {$success} {
    puts "=========================================="
    puts "SPI FLASH PROGRAMMING SUCCESSFUL!"
    puts "=========================================="
    close_hw_target
    disconnect_hw_server
    exit 0
} else {
    puts "=========================================="
    puts "ALL BATCH MODE ATTEMPTS FAILED"
    puts "GUI manual operation required with part: s25fl032p"
    puts "=========================================="
    close_hw_target
    disconnect_hw_server
    exit 1
}
