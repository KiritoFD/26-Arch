# ============================================================
# 删除 ILA debug core + 重新综合 + 实现 + 生成 bitstream
# ============================================================
open_project g:/GitHub/26-Arch/vivado/xv6_project/xv6_project.xpr

# ------------------------------------------------------------
# 1. 打开综合结果，清除所有 debug core
# ------------------------------------------------------------
open_run synth_1

set cores [get_debug_cores -quiet]
puts "==== Found [llength $cores] debug cores before cleanup ===="
foreach c $cores {
    puts "  deleting: $c"
    delete_debug_core $c
}

# 确认清空
set cores_after [get_debug_cores -quiet]
puts "==== Found [llength $cores_after] debug cores after cleanup ===="

# 保存约束（把 debug core 删除持久化）
save_constraints

close_design

# ------------------------------------------------------------
# 2. 重新综合（不带 ILA）
# ------------------------------------------------------------
puts "==== Resetting synth_1 ===="
reset_run synth_1
puts "==== Launching synth_1 ===="
launch_runs synth_1 -jobs 4
wait_on_run synth_1
set synth_status [get_property STATUS [get_runs synth_1]]
puts "SYNTH_STATUS=$synth_status"

# ------------------------------------------------------------
# 3. 实现 + 生成 bitstream
# ------------------------------------------------------------
puts "==== Resetting impl_1 ===="
reset_run impl_1
puts "==== Launching impl_1 (to write_bitstream) ===="
launch_runs impl_1 -to_step write_bitstream -jobs 4
wait_on_run impl_1
set impl_status [get_property STATUS [get_runs impl_1]]
puts "IMPL_STATUS=$impl_status"

# ------------------------------------------------------------
# 4. 验证 bitstream
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
