open_project g:/GitHub/26-Arch/vivado/xv6_project/xv6_project.xpr

# ============================================================
# 重跑 impl_1（含 ILA core），到 write_bitstream 步骤
# ============================================================
reset_run impl_1
launch_runs impl_1 -to_step write_bitstream -jobs 4
wait_on_run impl_1

set impl_status [get_property STATUS [get_runs impl_1]]
puts "IMPL_STATUS=$impl_status"

# 检查 bit 文件是否存在
set bit_file "g:/GitHub/26-Arch/vivado/xv6_project/xv6_project.runs/impl_1/basys3_top.bit"
if {![file exists $bit_file]} {
    puts "ERROR: bitstream not generated: $bit_file"
    exit 1
}
puts "BIT_FILE_OK=$bit_file"

# ============================================================
# 生成 MCS 文件（bitstream @0x0 + fs.img @0x300000）
# SPI Flash: s25fl032p, 4MB, SPI x1
# ============================================================
set fs_img "g:/GitHub/26-Arch/third_party/xv6-riscv/fs.img"
if {![file exists $fs_img]} {
    puts "ERROR: fs.img not found: $fs_img"
    exit 1
}

set mcs_file "g:/GitHub/26-Arch/vivado/basys3_xv6.mcs"
write_cfgmem -format mcs -interface spix1 -size 4 \
    -loadbit "up 0x000000 $bit_file" \
    -loaddata "up 0x300000 $fs_img" \
    -file $mcs_file -force

puts "MCS_FILE_OK=$mcs_file"
puts "ALL_DONE"
exit
