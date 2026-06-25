# ================================================================
# Build bitstream with Vivado ILA for cpu_tx UART debug
# Steps:
#   1. Open project, upgrade IPs
#   2. Update BRAM COE file
#   3. Run synthesis (mark_debug attributes preserved)
#   4. Setup debug: auto-create ILA core on dbg_cpu_clk domain
#      Probes: cpu_tx, jtag_cpu_rx, dbg_ever_thr_write
#      Depth: 4096 (enough for ~1.9 UART frames @ 25MHz)
#   5. Run implementation + write_bitstream (DEBUG_BITSTREAM)
#   6. Output .bit + .ltx (probe definitions)
#
# Usage:
#   vivado.bat -mode batch -source build_with_ila.tcl
# ================================================================

set repo_root {G:/GitHub/26-Arch}
set project_path [file join $repo_root vivado test-cpu project project_3 project_3.xpr]
set bitstream_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.bit]
set ltx_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.ltx]
set coe_path [file join $repo_root ready-to-run lab5 xv6-kernel.coe]

# ================================================================
# Step 1: Open project and upgrade IPs
# ================================================================
puts "=========================================="
puts "Step 1: Opening project..."
puts "=========================================="
open_project $project_path

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
# Step 3: Generate IP outputs + OOC synthesis
# ================================================================
puts "=========================================="
puts "Step 3: Generating IP outputs..."
puts "=========================================="
generate_target all [get_ips] -force

set clk_runs [get_runs -filter {NAME =~ "*clk_wiz_0_synth*"}]
if {[llength $clk_runs] == 0} {
    puts "Creating OOC synthesis run for clk_wiz_0..."
    create_ip_run [get_ips clk_wiz_0]
}
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

reset_run bram_0_synth_1
launch_runs bram_0_synth_1
wait_on_run bram_0_synth_1
if {[get_property STATUS [get_runs bram_0_synth_1]] != "synth_design Complete!"} {
    puts "ERROR: BRAM OOC synthesis failed!"
    exit 1
}
puts "BRAM OOC synthesis complete!"

# ================================================================
# Step 4: Run synthesis (mark_debug attributes preserved)
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
# Step 5: Setup debug - create ILA core for mark_debug signals
# ================================================================
puts "=========================================="
puts "Step 5: Setup debug (auto ILA core)..."
puts "=========================================="
open_run synth_1

# Verify mark_debug nets were recognized
puts "Marked debug nets after synthesis:"
set marked_nets [get_nets -hier -filter {MARK_DEBUG == 1}]
if {[llength $marked_nets] == 0} {
    puts "  WARNING: No mark_debug nets found! Forcing MARK_DEBUG on key signals..."
    # Force MARK_DEBUG on key signals (in case RTL attribute was optimized away)
    set cpu_tx_net [get_nets -hier -filter {NAME =~ "*cpu_tx*"}]
    set jtag_rx_net [get_nets -hier -filter {NAME =~ "*jtag_cpu_rx*"}]
    set thr_write_net [get_nets -hier -filter {NAME =~ "*dbg_ever_thr_write*"}]
    if {[llength $cpu_tx_net] > 0} {
        set_property MARK_DEBUG TRUE [lindex $cpu_tx_net 0]
    }
    if {[llength $jtag_rx_net] > 0} {
        set_property MARK_DEBUG TRUE [lindex $jtag_rx_net 0]
    }
    if {[llength $thr_write_net] > 0} {
        set_property MARK_DEBUG TRUE [lindex $thr_write_net 0]
    }
} else {
    foreach net $marked_nets {
        puts "  $net"
    }
}

# Find dbg_cpu_clk net for ILA clock domain
set cpu_clk_net [get_nets -hier -filter {NAME =~ "*dbg_cpu_clk*"}]
if {[llength $cpu_clk_net] == 0} {
    # Try alternative names
    set cpu_clk_net [get_nets -hier -filter {NAME =~ "u_clk_wiz_0/clk_out1*"}]
}
if {[llength $cpu_clk_net] == 0} {
    puts "ERROR: dbg_cpu_clk net not found, cannot create ILA core"
    exit 1
}
set ila_clk [lindex $cpu_clk_net 0]
puts "ILA clock: $ila_clk"

# Find probe nets
set probe0_list [get_nets -hier -filter {NAME =~ "*cpu_tx*"}]
set probe1_list [get_nets -hier -filter {NAME =~ "*jtag_cpu_rx*"}]
set probe2_list [get_nets -hier -filter {NAME =~ "*dbg_ever_thr_write*"}]

if {[llength $probe0_list] == 0} {
    puts "ERROR: cpu_tx net not found, cannot setup ILA"
    exit 1
}

# ================================================================
# Create ILA debug core manually (setup_debug is GUI-only in batch mode)
# ================================================================
puts "Creating ILA debug core manually..."

# Remove existing debug core if any
set existing_dc [get_debug_cores -quiet u_ila]
if {[llength $existing_dc] > 0} {
    delete_debug_core $existing_dc
}

# Create debug core
create_debug_core u_ila ila
set_property C_DATA_DEPTH 4096 [get_debug_cores u_ila]
set_property C_TRIGOUT_EN false [get_debug_cores u_ila]
set_property C_INPUT_PIPE_STAGES 2 [get_debug_cores u_ila]
set_property ALL_PROBE_SAME_MU true [get_debug_cores u_ila]
set_property ALL_PROBE_SAME_MU_CNT 2 [get_debug_cores u_ila]

# Connect clock port (clk port is auto-created by create_debug_core)
connect_debug_port u_ila/clk [get_nets $ila_clk]

# Create and connect probe 0: cpu_tx (1-bit)
create_debug_port u_ila probe
set_property PORT_WIDTH 1 [get_debug_ports u_ila/probe0]
connect_debug_port u_ila/probe0 [get_nets [lindex $probe0_list 0]]

# Create and connect probe 1: jtag_cpu_rx (1-bit)
if {[llength $probe1_list] > 0} {
    create_debug_port u_ila probe
    set_property PORT_WIDTH 1 [get_debug_ports u_ila/probe1]
    connect_debug_port u_ila/probe1 [get_nets [lindex $probe1_list 0]]
}

# Create and connect probe 2: dbg_ever_thr_write (1-bit)
if {[llength $probe2_list] > 0} {
    create_debug_port u_ila probe
    set_property PORT_WIDTH 1 [get_debug_ports u_ila/probe2]
    connect_debug_port u_ila/probe2 [get_nets [lindex $probe2_list 0]]
}

# Create and connect probe 3: dbg_cpu_valid (1-bit, CPU valid signal)
# Required because ILA core defaults to 5 probes; probe3 must be connected
set probe3_list [get_nets -hier -filter {NAME =~ "*dbg_cpu_valid*"}]
if {[llength $probe3_list] > 0} {
    create_debug_port u_ila probe
    set_property PORT_WIDTH 1 [get_debug_ports u_ila/probe3]
    connect_debug_port u_ila/probe3 [get_nets [lindex $probe3_list 0]]
}

# Delete extra probes (probe4+) that ILA core creates by default but are unused
set extra_probe [get_debug_ports -quiet u_ila/probe4]
if {[llength $extra_probe] > 0} {
    delete_debug_port $extra_probe
    puts "Deleted unused probe4"
}

puts "ILA core created:"
puts "  Clock: $ila_clk"
puts "  Probe0: cpu_tx"
if {[llength $probe1_list] > 0} { puts "  Probe1: jtag_cpu_rx" }
if {[llength $probe2_list] > 0} { puts "  Probe2: dbg_ever_thr_write" }
if {[llength $probe3_list] > 0} { puts "  Probe3: dbg_cpu_valid" }
puts "  Depth: 4096"

# Save design before implementing debug core (required by Vivado)
save_constraints

# Implement debug core (writes .ltx probe definitions)
implement_debug_core [get_debug_cores u_ila]
puts "implement_debug_core completed."

# Save again after implement_debug_core to persist probe definitions
save_constraints

# Close the synthesized design to allow impl_1 to launch
close_design

# ================================================================
# Step 6: Implementation + bitstream with DEBUG_BITSTREAM
# ================================================================
puts "=========================================="
puts "Step 6: Running implementation + bitstream..."
puts "=========================================="
# Note: ILA core already implemented via implement_debug_core above.
# Vivado will auto-generate .ltx probe definitions during write_bitstream.
reset_run impl_1
launch_runs impl_1 -to_step write_bitstream -jobs 32
wait_on_run impl_1
set impl_status [get_property STATUS [get_runs impl_1]]
puts "Implementation status: $impl_status"
if {$impl_status != "route_design Complete!" && $impl_status != "write_bitstream Complete!"} {
    puts "ERROR: Implementation failed!"
    exit 1
}

# Verify .ltx file exists (probe definitions)
if {[file exists $ltx_path]} {
    puts "Probe definitions: $ltx_path"
} else {
    puts "WARNING: .ltx file not found at $ltx_path"
}

close_project

puts "=========================================="
puts "BUILD COMPLETE! Ready for ILA debug."
puts "=========================================="
puts "Next steps:"
puts "1. Open Vivado Hardware Manager"
puts "2. Open target -> Auto connect (Basys3)"
puts "3. Program device with: $bitstream_path"
puts "   (Vivado will auto-load .ltx probe definitions)"
puts "4. In ILA dashboard, set trigger:"
puts "   - probe0 (cpu_tx): falling edge (R 0, F 1)"
puts "   This triggers on UART start bit"
puts "5. Run trigger, observe cpu_tx waveform"
puts "   - Verify: start bit (0) + 8 data bits + stop bit (1)"
puts "   - Bit period: 216 * 40ns = 8.64us (115740 baud)"
puts "=========================================="
