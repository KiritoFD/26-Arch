# Full build + flash script for Basys3 xv6 with SPI Flash disk
# Usage: C:\Xilinx\Vivado\2019.2\bin\vivado.bat -mode batch -source build_and_flash_spi.tcl

set repo_root {G:/GitHub/26-Arch}
set project_path [file join $repo_root vivado test-cpu project project_3 project_3.xpr]
set bitstream_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.bit]
set fs_img_path [file join $repo_root third_party xv6-riscv fs.img]
set mcs_file_path [file join $repo_root vivado test-cpu project project_3 full_flash.mcs]

# ================================================================
# Step 1: Open project and upgrade IPs
# ================================================================
puts "=== Step 1: Open project ==="
open_project $project_path

set locked_ips [get_ips -filter {IS_LOCKED == true}]
if {[llength $locked_ips] > 0} {
    puts "Upgrading locked IPs: $locked_ips"
    upgrade_ip $locked_ips
}

# Update BRAM IP with new xv6 kernel COE
set coe_path [file join $repo_root vivado xv6_project xv6-kernel.coe]
set bram_ip [get_ips bram_0]
set_property -dict [list \
    CONFIG.Coe_File $coe_path \
    CONFIG.Load_Init_File {true} \
] $bram_ip

generate_target all [get_ips] -force

# ================================================================
# Step 2: OOC synthesis for IPs
# ================================================================
puts "=== Step 2: IP OOC synthesis ==="

# clk_wiz_0
set clk_runs [get_runs -filter {NAME =~ "*clk_wiz_0*"}]
if {[llength $clk_runs] == 0} {
    create_ip_run [get_ips clk_wiz_0]
}
set clk_runs [get_runs -filter {NAME =~ "*clk_wiz_0*"}]
if {[llength $clk_runs] > 0} {
    set clk_run [lindex $clk_runs 0]
    reset_run $clk_run
    launch_runs $clk_run
    wait_on_run $clk_run
    if {[get_property STATUS $clk_run] != "synth_design Complete!"} {
        puts "ERROR: clk_wiz_0 OOC synthesis failed!"
        exit 1
    }
}

# bram_0 - create OOC run if needed
set bram_runs [get_runs -filter {NAME =~ "*bram_0*"}]
if {[llength $bram_runs] == 0} {
    puts "No bram_0 OOC run found, will synthesize with top-level"
} else {
    set bram_run [lindex $bram_runs 0]
    reset_run $bram_run
    launch_runs $bram_run
    wait_on_run $bram_run
    if {[get_property STATUS $bram_run] != "synth_design Complete!"} {
        puts "WARNING: BRAM OOC synthesis issue, continuing..."
    }
}

# ================================================================
# Step 3: Top-level synthesis
# ================================================================
puts "=== Step 3: Synthesis ==="
reset_run synth_1
launch_runs synth_1 -jobs 4
wait_on_run synth_1
if {[get_property STATUS [get_runs synth_1]] != "synth_design Complete!"} {
    puts "ERROR: Synthesis failed!"
    exit 1
}

# ================================================================
# Step 4: Implementation + bitstream
# ================================================================
puts "=== Step 4: Implementation + bitstream ==="
reset_run impl_1
launch_runs impl_1 -jobs 4 -to_step write_bitstream
wait_on_run impl_1

# Check if bitstream was generated
if {![file exists $bitstream_path]} {
    puts "ERROR: Bitstream not generated!"
    exit 1
}

puts "Bitstream: $bitstream_path"
close_project

# ================================================================
# Step 5: Create MCS file (bitstream + fs.img)
# ================================================================
puts "=== Step 5: Create MCS file ==="
write_cfgmem -format mcs -interface SPIx1 -size 32 \
    -loadbit "up 0x00000000 $bitstream_path" \
    -loaddata "up 0x00300000 $fs_img_path" \
    -file $mcs_file_path \
    -force

puts "MCS file: $mcs_file_path"

# ================================================================
# Step 6: Program SPI Flash
# ================================================================
puts "=== Step 6: Program SPI Flash ==="
open_hw
connect_hw_server
open_hw_target

set device [get_hw_devices xc7a35t_0]
current_hw_device $device

# Find flash part
set parts [get_cfgmem_parts -of_objects $device]
puts "Available flash parts: $parts"

set flash_part ""
foreach p $parts {
    if {[string match "*n25q*" [string tolower $p]] || [string match "*mt25q*" [string tolower $p]]} {
        set flash_part $p
        break
    }
}
if {$flash_part eq ""} {
    set flash_part "n25q032-3.0v-qspi"
}
puts "Using flash part: $flash_part"

set cfgmem [create_hw_cfgmem -hw_device $device $flash_part]
set_property PROGRAM.ADDRESS_RANGE {use_file} $cfgmem
set_property PROGRAM.FILE $mcs_file_path $cfgmem

# Program flash
program_hw_cfgmem $cfgmem

puts "=== SPI Flash programming complete! ==="
puts "Press FPGA reset button (btnC) to start xv6."

close_hw_target
disconnect_hw_server
close_hw
