# Rebuild bitstream with updated BRAM COE (kernel with debug printf)
# Only regenerates BRAM IP and rewrites bitstream - no full synthesis
set repo_root {G:/GitHub/26-Arch}
set project_path [file join $repo_root vivado test-cpu project project_3 project_3.xpr]
set bitstream_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.bit]
set coe_path [file join $repo_root ready-to-run lab5 xv6-kernel.coe]
set fs_img_path [file join $repo_root third_party xv6-riscv fs.img]
set mcs_file_path [file join $repo_root vivado test-cpu project project_3 full_flash.mcs]

puts "=========================================="
puts "Rebuilding BRAM + Bitstream (debug kernel)"
puts "=========================================="

open_project $project_path

# Step 1: Update BRAM IP with new COE
puts "Step 1: Updating BRAM COE..."
set bram_ip [get_ips bram_0]
set_property -dict [list \
    CONFIG.Coe_File $coe_path \
    CONFIG.Load_Init_File {true} \
] $bram_ip

# Step 2: Regenerate BRAM IP target
puts "Step 2: Regenerating BRAM IP..."
generate_target all [get_ips] -force

# Step 3: Run BRAM OOC synthesis
puts "Step 3: Running BRAM OOC synthesis..."
reset_run bram_0_synth_1
launch_runs bram_0_synth_1 -jobs 32
wait_on_run bram_0_synth_1
if {[get_property STATUS [get_runs bram_0_synth_1]] != "synth_design Complete!"} {
    puts "ERROR: BRAM OOC synthesis failed!"
    exit 1
}
puts "BRAM OOC synthesis complete!"

# Step 4: Open implemented design and rewrite bitstream
puts "Step 4: Opening implemented design..."
open_run impl_1

# Set SPI flash config
foreach {prop val} {
    BITSTREAM.CONFIG.SPI_BUSWIDTH 1
    BITSTREAM.CONFIG.CONFIGRATE 33
} {
    set rc [catch {set_property $prop $val [current_design]} err]
    if {$rc} {
        puts "  WARNING: Failed to set $prop = $val: $err"
    } else {
        puts "  OK: $prop = $val"
    }
}

# Step 5: Write bitstream
puts "Step 5: Writing bitstream..."
write_bitstream -force $bitstream_path
puts "Bitstream written: $bitstream_path"

close_project

# Step 6: Generate MCS
puts "Step 6: Generating MCS..."
write_cfgmem -format mcs -interface SPIx1 -size 32 \
    -loadbit "up 0x00000000 $bitstream_path" \
    -loaddata "up 0x00300000 $fs_img_path" \
    -file $mcs_file_path -force
puts "MCS written: $mcs_file_path"

puts "=========================================="
puts "BUILD COMPLETE! Ready for JTAG programming."
puts "=========================================="
