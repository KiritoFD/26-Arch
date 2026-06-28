open_project g:/GitHub/26-Arch/vivado/xv6_project/xv6_project.xpr
open_run synth_1

# ============================================================
# 从 mark_debug 信号中筛选 ILA 需要的 net
# ============================================================
set dbg_nets [get_nets -hierarchical -filter {MARK_DEBUG == 1}]
puts "==== Found [llength $dbg_nets] debug nets ===="

set we_net ""
set byte_nets {}
set wptr_nets {}

foreach net $dbg_nets {
    if {[string match "*dbg_uart_buf_we" $net]} {
        set we_net $net
    } elseif {[string match "*dbg_uart_buf_byte*" $net]} {
        lappend byte_nets $net
    } elseif {[string match "*dbg_uart_buf_wptr*" $net]} {
        lappend wptr_nets $net
    }
}

# clock：用顶层 dbg_cpu_clk 端口
set clk_net [get_nets -filter {NAME eq "dbg_cpu_clk"}]

puts "we_net=$we_net"
puts "byte_nets=$byte_nets ([llength $byte_nets] nets)"
puts "wptr_nets=$wptr_nets ([llength $wptr_nets] nets)"
puts "clk_net=$clk_net"

if {$we_net eq "" || [llength $byte_nets] != 8 || [llength $wptr_nets] != 12 || $clk_net eq ""} {
    puts "ERROR: cannot find required debug nets"
    close_design
    exit 1
}

# ============================================================
# 创建 ILA debug core
# ============================================================
set existing_cores [get_debug_cores -quiet]
if {$existing_cores ne ""} {
    foreach core $existing_cores {
        delete_debug_core $core
    }
}

create_debug_core u_ila ila
set_property -dict [list \
    C_DATA_DEPTH {4096} \
    C_TRIGIN_EN {0} \
    C_TRIGOUT_EN {0} \
    C_INPUT_PIPE_STAGES {2} \
] [get_debug_cores u_ila]

set_property C_CLK.SIGNAL_INFO $clk_net [get_debug_cores u_ila]

# probe0: dbg_uart_buf_we (1 bit)
create_debug_port u_ila probe
set_property PORT_W 1 [get_debug_ports u_ila/probe0]
set_property C_SIGNAL_INFO $we_net [get_debug_ports u_ila/probe0]

# probe1: dbg_uart_buf_byte (8 bit)
create_debug_port u_ila probe
set_property PORT_W 8 [get_debug_ports u_ila/probe1]
set_property C_SIGNAL_INFO $byte_nets [get_debug_ports u_ila/probe1]

# probe2: dbg_uart_buf_wptr (12 bit)
create_debug_port u_ila probe
set_property PORT_W 12 [get_debug_ports u_ila/probe2]
set_property C_SIGNAL_INFO $wptr_nets [get_debug_ports u_ila/probe2]

save_constraints
puts "ILA configured successfully"
close_design

# ============================================================
# 运行实现 + bitstream
# ============================================================
reset_run impl_1
launch_runs impl_1 -jobs 4
wait_on_run impl_1
set impl_status [get_property STATUS [get_runs impl_1]]
puts "IMPL_STATUS=$impl_status"

exit
