set repo_root {G:/GitHub/26-Arch}
set bitstream_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.bit]
set mcs_file_path [file join $repo_root vivado test-cpu project project_3 full_flash.mcs]

open_hw
connect_hw_server
open_hw_target

set device [get_hw_devices xc7a35t_0]
current_hw_device $device

# Step 1: Program FPGA with bitstream first
puts "Step 1: Programming FPGA..."
set_property PROGRAM.FILE $bitstream_path $device
program_hw_devices $device
puts "FPGA programmed!"

# Step 2: Create config memory for SPI Flash
puts "Step 2: Creating SPI Flash config memory..."
set hw_device [get_hw_devices xc7a35t_0]

# List available config memory parts
puts "Searching for N25Q flash parts..."
set parts [get_cfgmem_parts -of_objects $hw_device]
puts "Available parts: $parts"

# Try to find the correct part
set flash_part ""
foreach p $parts {
    if {[string match "*n25q*" [string tolower $p]] || [string match "*mt25q*" [string tolower $p]]} {
        set flash_part $p
        puts "Found flash part: $flash_part"
        break
    }
}

if {$flash_part eq ""} {
    # Try common part names
    set flash_part "n25q032-3.0v-qspi"
    puts "Using default flash part: $flash_part"
}

puts "Creating config memory with part: $flash_part"
set cfgmem [create_hw_cfgmem -hw_device $hw_device $flash_part]

# Step 3: Program SPI Flash
puts "Step 3: Programming SPI Flash..."
set_property PROGRAM.ADDRESS_RANGE {use_file} $cfgmem
set_property PROGRAM.FILE $mcs_file_path $cfgmem

program_hw_cfgmem $cfgmem

puts "SPI Flash programming complete!"

close_hw_target
disconnect_hw_server
close_hw