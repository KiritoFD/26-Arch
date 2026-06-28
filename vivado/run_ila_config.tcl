open_project g:/GitHub/26-Arch/vivado/xv6_project/xv6_project.xpr
open_run synth_1

# ============================================================
# 从 mark_debug 信号中筛选 ILA 需要的 net
# 完全避免 get_nets -filter 的 eq/=~ 语法陷阱
# ============================================================
set dbg_nets [get_nets -hierarchical -filter {MARK_DEBUG == 1}]
puts "==== Found [llength $dbg_nets] debug nets ===="

set clk_net  ""
set we_net   ""
set byte_nets {}
set wptr_nets {}

foreach net $dbg_nets {
    # 把 net 对象转成字符串便于 glob 匹配
    set nm [get_property NAME $net]
    if {[string match "*dbg_cpu_clk" $nm]} {
        set clk_net $net
    } elseif {[string match "*dbg_uart_buf_we*" $nm]} {
        set we_net $net
    } elseif {[string match "*dbg_uart_buf_byte*" $nm]} {
        lappend byte_nets $net
    } elseif {[string match "*dbg_uart_buf_wptr*" $nm]} {
        lappend wptr_nets $net
    }
}

puts "clk_net=$clk_net"
puts "we_net=$we_net"
puts "byte_nets=([llength $byte_nets] nets)"
puts "wptr_nets=([llength $wptr_nets] nets)"

if {$clk_net eq ""} {
    puts "ERROR: cannot find dbg_cpu_clk net"
    close_design
    exit 1
}
if {$we_net eq ""} {
    puts "ERROR: cannot find dbg_uart_buf_we net"
    close_design
    exit 1
}
if {[llength $byte_nets] != 8} {
    puts "ERROR: expected 8 byte nets, got [llength $byte_nets]"
    close_design
    exit 1
}
if {[llength $wptr_nets] != 12} {
    puts "ERROR: expected 12 wptr nets, got [llength $wptr_nets]"
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

# 诊断：列出 debug_core 支持的所有 property 名
puts "=== debug_core properties ==="
foreach p [list_property [get_debug_cores u_ila]] {
    puts "  PROP: $p"
}
puts "=== end debug_core properties ==="

# 也列出 debug_port 支持的 property 名
create_debug_port u_ila probe
puts "=== debug_port probe0 properties ==="
foreach p [list_property [get_debug_ports u_ila/probe0]] {
    puts "  PORT_PROP: $p"
}
puts "=== end debug_port properties ==="

# 查 connect_debug_core 命令语法
puts "=== connect_debug_core help ==="
help connect_debug_core
puts "=== end help ==="

# 后续配置先注释掉，等诊断出正确属性名再恢复
# create_debug_port u_ila probe
# set_property PORT_W 1 [get_debug_ports u_ila/probe0]
# set_property C_SIGNAL_INFO $we_net [get_debug_ports u_ila/probe0]

# create_debug_port u_ila probe
# set_property PORT_W 8 [get_debug_ports u_ila/probe1]
# set_property C_SIGNAL_INFO $byte_nets [get_debug_ports u_ila/probe1]

# create_debug_port u_ila probe
# set_property PORT_W 12 [get_debug_ports u_ila/probe2]
# set_property C_SIGNAL_INFO $wptr_nets [get_debug_ports u_ila/probe2]

# save_constraints
# puts "ILA_CONFIG_SUCCESS"
close_design
exit
