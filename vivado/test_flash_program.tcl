# Test: program a tiny MCS file to check if flash communication works
set repo_root {G:/GitHub/26-Arch}

# Step 1: Create a tiny test data file (256 bytes of 0xAA)
set test_bin [file join $repo_root vivado test_data.bin]
set fh [open $test_bin w]
fconfigure $fh -translation binary
for {set i 0} {$i < 256} {incr i} {
    puts -nonewline $fh [binary format c 0xAA]
}
close $fh

# Step 2: Create a tiny MCS file
set test_mcs [file join $repo_root vivado test_tiny.mcs]
write_cfgmem -format mcs -interface SPIx1 -size 32 \
    -loaddata "up 0x00000000 $test_bin" \
    -file $test_mcs -force
puts "Created test MCS: $test_mcs"

# Step 3: Program the flash with the tiny MCS
open_hw
connect_hw_server
open_hw_target

set device [get_hw_devices xc7a35t_0]
current_hw_device $device
set_property PROBES.FILE "" $device

set flash_part "n25q32-3.3v-spi-x1_x2_x4"
set cfgmem [create_hw_cfgmem -hw_device $device $flash_part]

set_property PROGRAM.ADDRESS_RANGE {use_file} $cfgmem
set_property PROGRAM.FILES [list $test_mcs] $cfgmem
set_property PROGRAM.BLANK_CHECK  0 $cfgmem
set_property PROGRAM.ERASE        1 $cfgmem
set_property PROGRAM.CFG_PROGRAM  1 $cfgmem
set_property PROGRAM.VERIFY      0 $cfgmem

puts "Programming tiny test MCS..."
catch {program_hw_cfgmem $cfgmem} result
puts "Result: $result"

close_hw_target
disconnect_hw_server
close_hw
puts "Done."
