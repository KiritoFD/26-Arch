# ============================================================
# 重新综合 + 实现 + 生成 bitstream (xv6-kernel.coe 已更新)
# ============================================================
open_project g:/GitHub/26-Arch/vivado/xv6_project/xv6_project.xpr

# ------------------------------------------------------------
# 1. 重新综合 (COE 变化需要重新综合 BRAM IP)
# ------------------------------------------------------------
puts "==== Resetting synth_1 ===="
reset_run synth_1
puts "==== Launching synth_1 ===="
launch_runs synth_1 -jobs 4
wait_on_run synth_1
set synth_status [get_property STATUS [get_runs synth_1]]
puts "SYNTH_STATUS=$synth_status"

# ------------------------------------------------------------
# 2. 实现 + 生成 bitstream
# ------------------------------------------------------------
puts "==== Resetting impl_1 ===="
reset_run impl_1
puts "==== Launching impl_1 (to write_bitstream) ===="
launch_runs impl_1 -to_step write_bitstream -jobs 4
wait_on_run impl_1
set impl_status [get_property STATUS [get_runs impl_1]]
puts "IMPL_STATUS=$impl_status"

# ------------------------------------------------------------
# 3. 验证 bitstream
# ------------------------------------------------------------
set bit_file "g:/GitHub/26-Arch/vivado/xv6_project/xv6_project.runs/impl_1/basys3_top.bit"
if {![file exists $bit_file]} {
    puts "ERROR: bitstream not generated: $bit_file"
    exit 1
}
puts "BIT_FILE_OK=$bit_file"
puts "BIT_SIZE=[file size $bit_file]"
puts "ALL_DONE"
exit
