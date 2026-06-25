# ================================================================
# Full build + SPI Flash programming script for Basys3 xv6
# Steps:
#   1. Open project, upgrade IPs
#   2. Update BRAM COE file
#   3. Run synthesis + implementation + bitstream
#   4. Create MCS file with bitstream + fs.img
#   5. Program SPI Flash
#   6. Program FPGA via JTAG
# ================================================================

set repo_root {G:/GitHub/26-Arch}
set project_path [file join $repo_root vivado test-cpu project project_3 project_3.xpr]
set bitstream_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.bit]
set coe_path [file join $repo_root ready-to-run lab5 xv6-kernel.coe]
set fs_img_path [file join $repo_root third_party xv6-riscv fs.img]
set mcs_file_path [file join $repo_root vivado test-cpu project project_3 full_flash.mcs]

# ================================================================
# Step 1: Open project and upgrade IPs
# ================================================================
puts "=========================================="
puts "Step 1: Opening project..."
puts "=========================================="
open_project $project_path

# Upgrade locked IPs
set locked_ips [get_ips -filter {IS_LOCKED == true}]
if {[llength $locked_ips] > 0} {
    puts "Upgrading locked IPs: $locked_ips"
    upgrade_ip $locked_ips
}

# ================================================================
# Step 2: Update BRAM IP with new kernel COE
# ================================================================
puts "=========================================="
puts "Step 2: Updating BRAM COE file..."
puts "=========================================="
set bram_ip [get_ips bram_0]
set_property -dict [list \
    CONFIG.Coe_File $coe_path \
    CONFIG.Load_Init_File {true} \
] $bram_ip

# ================================================================
# Step 3: Generate IP outputs
# ================================================================
puts "=========================================="
puts "Step 3: Generating IP outputs..."
puts "=========================================="
generate_target all [get_ips] -force

# Create OOC runs if needed
set clk_runs [get_runs -filter {NAME =~ "*clk_wiz_0_synth*"}]
if {[llength $clk_runs] == 0} {
    puts "Creating OOC synthesis run for clk_wiz_0..."
    create_ip_run [get_ips clk_wiz_0]
}

# Run OOC synthesis for clk_wiz_0
set clk_runs [get_runs -filter {NAME =~ "*clk_wiz_0_synth*"}]
if {[llength $clk_runs] > 0} {
    set clk_run [lindex $clk_runs 0]
    puts "Running clk_wiz_0 OOC synthesis: $clk_run"
    reset_run $clk_run
    launch_runs $clk_run
    wait_on_run $clk_run
    if {[get_property STATUS $clk_run] != "synth_design Complete!"} {
        puts "ERROR: clk_wiz_0 OOC synthesis failed!"
        exit 1
    }
    puts "clk_wiz_0 OOC synthesis complete!"
}

# Run OOC synthesis for bram_0
reset_run bram_0_synth_1
launch_runs bram_0_synth_1
wait_on_run bram_0_synth_1
if {[get_property STATUS [get_runs bram_0_synth_1]] != "synth_design Complete!"} {
    puts "ERROR: BRAM OOC synthesis failed!"
    exit 1
}
puts "BRAM OOC synthesis complete!"

# ================================================================
# Step 4: Run synthesis
# ================================================================
puts "=========================================="
puts "Step 4: Running synthesis..."
puts "=========================================="
reset_run synth_1
launch_runs synth_1 -jobs 4
wait_on_run synth_1
if {[get_property STATUS [get_runs synth_1]] != "synth_design Complete!"} {
    puts "ERROR: Synthesis failed!"
    exit 1
}
puts "Synthesis complete!"

# ================================================================
# Step 5: Run implementation + bitstream
# ================================================================
puts "=========================================="
puts "Step 5: Running implementation + bitstream..."
puts "=========================================="
reset_run impl_1
launch_runs impl_1 -to_step write_bitstream -jobs 4
wait_on_run impl_1
if {[get_property STATUS [get_runs impl_1]] != "route_design Complete!"} {
    puts "ERROR: Implementation failed!"
    exit 1
}
puts "Bitstream generated: $bitstream_path"

close_project

# ================================================================
# Step 6: Create MCS file with bitstream + fs.img
# ================================================================
puts "=========================================="
puts "Step 6: Creating MCS file..."
puts "=========================================="

# Read bitstream
set bit_fd [open $bitstream_path rb]
fconfigure $bit_fd -translation binary
set bit_data [read $bit_fd]
close $bit_fd

# Read fs.img
set fs_fd [open $fs_img_path rb]
fconfigure $fs_fd -translation binary
set fs_data [read $fs_fd]
close $fs_fd

puts "Bitstream size: [string length $bit_data] bytes"
puts "fs.img size: [string length $fs_data] bytes"

# Create full flash image (32MB)
set flash_size [expr {32 * 1024 * 1024}]
set fs_offset [expr {0x00400000}]

# Write MCS file
set mcs_fd [open $mcs_file_path w]
puts $mcs_fd "// MCS file for Basys3 SPI Flash (N25Q032, 32MB)"
puts $mcs_fd "// Contains: bitstream at 0x0, fs.img at 0x400000"
puts $mcs_fd ""

# Helper: write MCS record
proc write_mcs_record {fd addr data} {
    set len [string length $data]
    set record_type 0
    # Calculate checksum
    set checksum [expr {($len + ($addr >> 8 & 0xFF) + ($addr & 0xFF) + $record_type) & 0xFF}]
    for {set i 0} {$i < $len} {incr i} {
        set byte [scan [string range $data $i $i] %c]
        set checksum [expr {($checksum + $byte) & 0xFF}]
    }
    set checksum [expr {(~$checksum) & 0xFF}]

    set hex_str [format ":02%04X00" $len $addr]
    for {set i 0} {$i < $len} {incr i} {
        set byte [scan [string range $data $i $i] %c]
        append hex_str [format "%02X" $byte]
    }
    append hex_str [format "%02X" $checksum]
    puts $fd $hex_str
}

# Write bitstream data at offset 0 (in 16-byte records)
puts "Writing bitstream to MCS..."
set addr 0
set bit_len [string length $bit_data]
for {set i 0} {$i < $bit_len} {incr i 16} {
    set end_idx [expr {min($i + 16, $bit_len)}]
    set chunk [string range $bit_data $i $end_idx]
    # Pad to 16 bytes if needed
    set chunk_len [string length $chunk]
    if {$chunk_len < 16} {
        append chunk [string repeat "\xFF" [expr {16 - $chunk_len}]]
    }
    # Extended address record if needed
    set cur_ext [expr {$addr >> 16}]
    set rec_addr [expr {$addr & 0xFFFF}]
    if {$rec_addr == 0 || $cur_ext != [expr {($addr - 16) >> 16}]} {
        # Write extended address record
        set ext_checksum [expr {(2 + 0 + 0 + 4 + ($cur_ext >> 8 & 0xFF) + ($cur_ext & 0xFF)) & 0xFF}]
        set ext_checksum [expr {(~$ext_checksum) & 0xFF}]
        puts $mcs_fd [format ":02000004%04X%02X" $cur_addr $ext_checksum]
    }
    # Write data record
    set checksum [expr {(16 + ($rec_addr >> 8 & 0xFF) + ($rec_addr & 0xFF) + 0) & 0xFF}]
    set hex_data ""
    for {set j 0} {$j < 16} {incr j} {
        set byte [scan [string range $chunk $j $j] %c]
        set checksum [expr {($checksum + $byte) & 0xFF}]
        append hex_data [format "%02X" $byte]
    }
    set checksum [expr {(~$checksum) & 0xFF}]
    puts $mcs_fd [format ":10%04X00%s%02X" $rec_addr $hex_data $checksum]
    incr addr 16
}

# Write fs.img data at offset 0x400000
puts "Writing fs.img to MCS..."
set addr $fs_offset
set fs_len [string length $fs_data]
for {set i 0} {$i < $fs_len} {incr i 16} {
    set end_idx [expr {min($i + 16, $fs_len)}]
    set chunk [string range $fs_data $i $end_idx]
    set chunk_len [string length $chunk]
    if {$chunk_len < 16} {
        append chunk [string repeat "\xFF" [expr {16 - $chunk_len}]]
    }
    set cur_ext [expr {$addr >> 16}]
    set rec_addr [expr {$addr & 0xFFFF}]
    if {$rec_addr == 0 || $cur_ext != [expr {($addr - 16) >> 16}]} {
        set ext_checksum [expr {(2 + 0 + 0 + 4 + ($cur_ext >> 8 & 0xFF) + ($cur_ext & 0xFF)) & 0xFF}]
        set ext_checksum [expr {(~$ext_checksum) & 0xFF}]
        puts $mcs_fd [format ":02000004%04X%02X" $cur_ext $ext_checksum]
    }
    set checksum [expr {(16 + ($rec_addr >> 8 & 0xFF) + ($rec_addr & 0xFF) + 0) & 0xFF}]
    set hex_data ""
    for {set j 0} {$j < 16} {incr j} {
        set byte [scan [string range $chunk $j $j] %c]
        set checksum [expr {($checksum + $byte) & 0xFF}]
        append hex_data [format "%02X" $byte]
    }
    set checksum [expr {(~$checksum) & 0xFF}]
    puts $mcs_fd [format ":10%04X00%s%02X" $rec_addr $hex_data $checksum]
    incr addr 16
}

# End-of-file record
puts $mcs_fd ":00000001FF"
close $mcs_fd

puts "MCS file created: $mcs_file_path"

# ================================================================
# Step 7: Program SPI Flash
# ================================================================
puts "=========================================="
puts "Step 7: Programming SPI Flash..."
puts "=========================================="

open_hw
connect_hw_server
open_hw_target

set device [get_hw_devices xc7a35t_0]
current_hw_device $device

# Create config memory for SPI Flash (N25Q032)
set flash_part "n25q32-3.3v-spi-x1_x2_x4"
puts "Creating config memory with part: $flash_part"
set cfgmem [create_hw_cfgmem -hw_device $device $flash_part]

# Set MCS file for programming
set_property PROGRAM.ADDRESS_RANGE {use_file} $cfgmem
set_property PROGRAM.FILES [list $mcs_file_path] $cfgmem

# Program SPI Flash
puts "Programming SPI Flash (this may take several minutes)..."
program_hw_cfgmem $cfgmem

puts "SPI Flash programming complete!"

# ================================================================
# Step 8: Program FPGA via JTAG
# ================================================================
puts "=========================================="
puts "Step 8: Programming FPGA via JTAG..."
puts "=========================================="

set_property PROGRAM.FILE $bitstream_path $device
program_hw_devices $device

puts "FPGA programmed!"

close_hw_target
disconnect_hw_server
close_hw

puts "=========================================="
puts "ALL DONE! Check serial output on COM4 (115200 baud)"
puts "=========================================="
