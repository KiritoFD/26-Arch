# 仅生成 MCS（bitstream 已生成，fs.img 已裁剪）
open_project g:/GitHub/26-Arch/vivado/xv6_project/xv6_project.xpr

set bit_file "g:/GitHub/26-Arch/vivado/xv6_project/xv6_project.runs/impl_1/basys3_top.bit"
set fs_img  "g:/GitHub/26-Arch/third_party/xv6-riscv/fs_trim.img"
set mcs_file "g:/GitHub/26-Arch/vivado/basys3_xv6.mcs"

if {![file exists $bit_file]} {
    puts "ERROR: bitstream not found: $bit_file"
    exit 1
}
if {![file exists $fs_img]} {
    puts "ERROR: fs_trim.img not found: $fs_img"
    exit 1
}

puts "BIT_SIZE=[file size $bit_file]"
puts "FS_SIZE=[file size $fs_img]"

# SPI Flash: s25fl032p, 4MB, SPI x1
# bitstream @0x000000 (2.09MB)
# fs.img   @0x300000 (976KB, trimmed from 2MB)
# 总占用: 2.09MB + 976KB = 3.04MB < 4MB
write_cfgmem -format mcs -interface spix1 -size 4 \
    -loadbit "up 0x000000 $bit_file" \
    -loaddata "up 0x300000 $fs_img" \
    -file $mcs_file -force

puts "MCS_FILE_OK=$mcs_file"
puts "MCS_SIZE=[file size $mcs_file]"
puts "ALL_DONE"
exit
