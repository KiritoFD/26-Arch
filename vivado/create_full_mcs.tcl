# Convert fs.img to MCS file at offset 0x00300000 (3MB, matches device.sv FLASH_DISK_OFFSET)
# Usage: vivado -mode batch -source create_full_mcs.tcl

set repo_root {G:/GitHub/26-Arch}
set bitstream_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.bit]
set fs_img_path [file join $repo_root third_party xv6-riscv fs.img]
set mcs_file_path [file join $repo_root vivado test-cpu project project_3 full_flash.mcs]

puts "Creating MCS file with bitstream + fs.img..."
puts "  Bitstream: $bitstream_path"
puts "  fs.img:    $fs_img_path"
puts "  MCS output: $mcs_file_path"
puts "  fs.img offset: 0x00300000 (3MB, matches device.sv FLASH_DISK_OFFSET)"

# write_cfgmem with multiple data files:
#   - bitstream at offset 0x00000000
#   - fs.img at offset 0x00300000 (3MB, matches device.sv)
write_cfgmem -format mcs -interface SPIx1 -size 32 \
    -loadbit "up 0x00000000 $bitstream_path" \
    -loaddata "up 0x00300000 $fs_img_path" \
    -file $mcs_file_path \
    -force

puts "MCS file created: $mcs_file_path"
