# ================================================================
# Build bitstream for Basys3 xv6 (NO ILA, NO mark_debug)
# + Generate MCS file with bitstream + fs.img
#
# Usage: vivado.bat -mode batch -source vivado\build_full_no_ila.tcl
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

# ------------------------------------------------------------
# Step 1a: Sync source files from vivado/src to project imports
# Vivado project uses imported (copied) source files. We must
# overwrite them with the latest versions before synthesis.
# ------------------------------------------------------------
set src_dir [file join $repo_root vivado src]
set imports_dir [file join $repo_root vivado test-cpu project project_3 project_3.srcs sources_1 imports src]
puts "Syncing source files from $src_dir to $imports_dir..."
set synced 0
foreach {orig copy} [list \
    [file join $src_dir device.sv]          [file join $imports_dir device.sv] \
    [file join $src_dir spi_flash_disk.sv]  [file join $imports_dir spi_flash_disk.sv] \
    [file join $src_dir with_delay basys3_top.sv]   [file join $imports_dir with_delay basys3_top.sv] \
    [file join $src_dir with_delay soc_top.sv]       [file join $imports_dir with_delay soc_top.sv] \
    [file join $src_dir with_delay bram_wrapper.sv] [file join $imports_dir with_delay bram_wrapper.sv] \
    [file join $src_dir with_delay cbus_crossbar.sv] [file join $imports_dir with_delay cbus_crossbar.sv] \
] {
    if {[file exists $orig] && [file exists $copy]} {
        file copy -force $orig $copy
        puts "  Synced: [file tail $orig]"
        incr synced
    }
}
puts "Synced $synced source files."

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

# Create OOC run for clk_wiz_0 if missing
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
launch_runs synth_1 -jobs 32
wait_on_run synth_1
if {[get_property STATUS [get_runs synth_1]] != "synth_design Complete!"} {
    puts "ERROR: Synthesis failed!"
    exit 1
}
puts "Synthesis complete!"

# ================================================================
# Step 5: Run implementation (route_design only, NOT write_bitstream yet)
# We need to set BITSTREAM.CONFIG.SPI_BUSWIDTH=1 BEFORE write_bitstream
# so Vivado knows SPI bus width for flash programming.
# ================================================================
puts "=========================================="
puts "Step 5: Running implementation (route_design)..."
puts "=========================================="
reset_run impl_1
launch_runs impl_1 -to_step route_design -jobs 32
wait_on_run impl_1
set impl_status [get_property STATUS [get_runs impl_1]]
puts "Implementation status: $impl_status"
if {$impl_status != "route_design Complete!"} {
    puts "ERROR: Implementation (route_design) failed!"
    exit 1
}
puts "Route design complete!"

# ================================================================
# Step 5b: Open implemented design, set SPI flash config, write bitstream
# ================================================================
puts "=========================================="
puts "Step 5b: Setting BITSTREAM.CONFIG.SPI_BUSWIDTH=1..."
puts "=========================================="
open_run impl_1

# Set SPI flash configuration properties on the design
# SPI_BUSWIDTH=1 -> Use SPIx1 mode (matches Basys3 hardware, single data pin)
# CONFIGRATE=33  -> 33 MHz config rate (safe for Basys3)
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

# Write bitstream with SPI config properties
puts "Writing bitstream with SPI config..."
write_bitstream -force $bitstream_path
puts "Bitstream generated: $bitstream_path"

close_design
close_project

# ================================================================
# Step 6: Create MCS file (bitstream + fs.img)
# ================================================================
puts "=========================================="
puts "Step 6: Creating MCS file..."
puts "=========================================="
puts "  Bitstream: $bitstream_path"
puts "  fs.img:    $fs_img_path"
puts "  MCS output: $mcs_file_path"
puts "  fs.img offset: 0x00300000 (3MB, matches device.sv FLASH_DISK_OFFSET)"

write_cfgmem -format mcs -interface SPIx1 -size 32 \
    -loadbit "up 0x00000000 $bitstream_path" \
    -loaddata "up 0x00300000 $fs_img_path" \
    -file $mcs_file_path \
    -force

puts "MCS file created: $mcs_file_path"
puts "=========================================="
puts "BUILD COMPLETE! Ready for SPI Flash programming."
puts "=========================================="
puts "Next: Run program_spi_flash_simple.tcl to program flash."
puts "=========================================="
