# ================================================================
# Rebuild bitstream with SPI flash configuration properties
#
# The current bitstream was generated WITHOUT BITSTREAM.CONFIG.* properties,
# which means Vivado doesn't know the SPI bus width or config voltage.
# This causes "Failure to set flash parameters" (Labtools 27-3347) when
# trying to program SPI flash.
#
# This script:
#   1. Opens the project
#   2. Opens the implemented design (impl_1) - no re-synthesis needed
#   3. Sets BITSTREAM.CONFIG.* properties
#   4. Writes a new bitstream (fast, ~30 seconds)
#   5. Regenerates the MCS file with the new bitstream
#
# Usage: vivado.bat -mode batch -source rebuild_bitstream_spi_config.tcl
# ================================================================

set repo_root {G:/GitHub/26-Arch}
set project_path [file join $repo_root vivado test-cpu project project_3 project_3.xpr]
set bitstream_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.bit]
set mcs_path [file join $repo_root vivado test-cpu project project_3 full_flash.mcs]
set fs_img_path [file join $repo_root third_party xv6-riscv fs.img]

puts "=========================================="
puts "Rebuilding bitstream with SPI flash config"
puts "=========================================="

# Step 1: Open project
puts "Step 1: Opening project..."
open_project $project_path

# Step 2: Open implemented design
puts "Step 2: Opening implemented design (impl_1)..."
open_run impl_1

# Step 3: Set BITSTREAM.CONFIG properties
# These tell Vivado how to communicate with the SPI flash:
#   SPI_BUSWIDTH=1  -> Use SPIx1 mode (1 data pin, matches Basys3 hardware)
#   CONFIGRATE=33   -> 33 MHz config rate (safe for Basys3)
#   CONFIG_VOLTAGE  -> 3.3V (Basys3 uses 3.3V config bank)
#   CFGBVS          -> VCCAUX (config bank voltage select)
puts "Step 3: Setting BITSTREAM.CONFIG properties..."

set props_set {}
set props_failed {}

foreach {prop val} {
    BITSTREAM.CONFIG.SPI_BUSWIDTH 1
    BITSTREAM.CONFIG.CONFIGRATE 33
    BITSTREAM.CONFIG.CONFIG_VOLTAGE 3.3
    BITSTREAM.CONFIG.CFGBVS VCCAUX
} {
    set rc [catch {set_property $prop $val [current_design]} err]
    if {$rc} {
        puts "  FAILED: $prop = $val -> $err"
        lappend props_failed $prop
    } else {
        puts "  OK: $prop = $val"
        lappend props_set $prop
    }
}

# List all BITSTREAM properties for reference
puts "=== All BITSTREAM.CONFIG properties on current design ==="
foreach prop [list_property [current_design] -regexp {BITSTREAM.CONFIG.*}] {
    set val [catch {get_property $prop [current_design]} result]
    if {$val == 0} {
        puts "  $prop = $result"
    }
}

# Step 4: Write new bitstream
puts "Step 4: Writing new bitstream..."
write_bitstream -force $bitstream_path
puts "  Bitstream written: $bitstream_path"

# Step 5: Regenerate MCS
puts "Step 5: Regenerating MCS file..."
write_cfgmem -format mcs -interface SPIx1 -size 32 \
    -loadbit "up 0x00000000 $bitstream_path" \
    -loaddata "up 0x00300000 $fs_img_path" \
    -file $mcs_path \
    -force
puts "  MCS file: $mcs_path"

close_project
puts "=========================================="
puts "Done! Bitstream rebuilt with SPI config."
puts "Properties set: $props_set"
if {[llength $props_failed] > 0} {
    puts "Properties FAILED: $props_failed"
}
puts "Next: Run program_spi_flash_v10.tcl to program flash."
puts "=========================================="
