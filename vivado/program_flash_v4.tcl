# ================================================================
# SPI Flash programming with spix1 interface
# ================================================================

set repo_root {G:/GitHub/26-Arch}
set bitstream_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.bit]
set fs_img_path [file join $repo_root third_party xv6-riscv fs.img]
set mcs_file_path [file join $repo_root vivado test-cpu project project_3 full_flash.mcs]

# Delete old MCS file
if {[file exists $mcs_file_path]} {
    file delete $mcs_file_path
}

# Step 1: Create MCS file from bitstream using Vivado's write_cfgmem
puts "Step 1: Creating MCS file from bitstream..."
write_cfgmem -format mcs -interface spix1 -size 32 \
    -loadbit "up 0x0 $bitstream_path" \
    -force $mcs_file_path

if {![file exists $mcs_file_path]} {
    puts "ERROR: Failed to create MCS file!"
    exit 1
}
puts "MCS file created: $mcs_file_path ([file size $mcs_file_path] bytes)"

# Step 2: Append fs.img data to MCS file at offset 0x400000
puts "Step 2: Appending fs.img to MCS file at offset 0x400000..."

# Read fs.img
set fs_fd [open $fs_img_path rb]
fconfigure $fs_fd -translation binary
set fs_data [read $fs_fd]
close $fs_fd
puts "fs.img size: [string length $fs_data] bytes"

# Append to MCS file
set mcs_fd [open $mcs_file_path a]
fconfigure $mcs_fd -translation auto

set fs_offset 0x00400000
set pos 0
set current_ext_addr -1

while {$pos < [string length $fs_data]} {
    set abs_addr [expr {$fs_offset + $pos}]
    set ext_addr [expr {($abs_addr >> 16) & 0xFFFF}]
    set addr_lo [expr {$abs_addr & 0xFFFF}]

    # Write extended linear address record if needed
    if {$ext_addr != $current_ext_addr} {
        set checksum [expr {(2 + 0 + 0 + 4 + ($ext_addr >> 8) + ($ext_addr & 0xFF)) & 0xFF}]
        set checksum [expr {(~$checksum + 1) & 0xFF}]
        puts $mcs_fd [format ":02000004%04X%02X" $ext_addr $checksum]
        set current_ext_addr $ext_addr
    }

    # Write 16-byte data record
    set chunk_len 16
    set bytes_left [expr {[string length $fs_data] - $pos}]
    if {$chunk_len > $bytes_left} {
        set chunk_len $bytes_left
    }
    # Also limit to end of 64KB block
    set bytes_to_eob [expr {0x10000 - $addr_lo}]
    if {$chunk_len > $bytes_to_eob} {
        set chunk_len $bytes_to_eob
    }

    set chunk [string range $fs_data $pos [expr {$pos + $chunk_len - 1}]]
    # Pad to 16 bytes if needed
    if {[string length $chunk] < 16} {
        append chunk [string repeat "\xFF" [expr {16 - [string length $chunk]}]]
        set chunk_len 16
    }

    set checksum [expr {($chunk_len + ($addr_lo >> 8) + ($addr_lo & 0xFF) + 0) & 0xFF}]
    set hex_data ""
    for {set i 0} {$i < $chunk_len} {incr i} {
        set byte [scan [string range $chunk $i $i] %c]
        set checksum [expr {($checksum + $byte) & 0xFF}]
        append hex_data [format "%02X" $byte]
    }
    set checksum [expr {(~$checksum + 1) & 0xFF}]
    puts $mcs_fd [format ":%02X%04X00%s%02X" $chunk_len $addr_lo $hex_data $checksum]

    incr pos $chunk_len
}

# Re-write end-of-file record
puts $mcs_fd ":00000001FF"
close $mcs_fd

puts "MCS file updated with fs.img: [file size $mcs_file_path] bytes"

# Step 3: Connect to hardware and program
puts "Step 3: Connecting to hardware..."
open_hw
connect_hw_server
open_hw_target

set device [get_hw_devices xc7a35t_0]
current_hw_device $device

# Program FPGA first
puts "Programming FPGA..."
set_property PROGRAM.FILE $bitstream_path $device
program_hw_devices $device
puts "FPGA programmed!"

# Program SPI Flash
puts "Setting up SPI Flash programming..."
set cfgmem [create_hw_cfgmem -hw_device $device n25q32-3.3v-spi-x1_x2_x4]

set_property PROGRAM.ADDRESS_RANGE {use_file} $cfgmem
set_property PROGRAM.FILES [list $mcs_file_path] $cfgmem
set_property PROGRAM.UNUSED_PIN_TERMINATION {pull-none} $cfgmem

# Verify
set files [get_property PROGRAM.FILES $cfgmem]
puts "PROGRAM.FILES = $files"

puts "Programming SPI Flash (this may take several minutes)..."
program_hw_cfgmem $cfgmem
puts "SPI Flash programmed!"

close_hw_target
disconnect_hw_server
close_hw

puts "=========================================="
puts "DONE! Check serial output on COM4 (115200 baud)"
puts "=========================================="
