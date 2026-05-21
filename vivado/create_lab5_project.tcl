proc write_bram_mif {coe_path mif_path} {
    set fin [open $coe_path r]
    set fout [open $mif_path w]
    set saw_vector 0
    while {[gets $fin line] >= 0} {
        set s [string trim $line]
        if {$s eq ""} {
            continue
        }
        if {[string match "memory_initialization_vector*" $s]} {
            set saw_vector 1
            set parts [split $s "="]
            if {[llength $parts] > 1} {
                set s [string trim [lindex $parts 1]]
            } else {
                continue
            }
        }
        if {!$saw_vector} {
            continue
        }
        set s [string trimright $s ";"]
        set s [string trimright $s ","]
        set s [string trim $s]
        if {$s eq ""} {
            continue
        }
        if {[regexp {^[0-9a-fA-F]+$} $s]} {
            set bin ""
            foreach ch [split [string toupper $s] ""] {
                append bin [dict get {
                    0 0000 1 0001 2 0010 3 0011
                    4 0100 5 0101 6 0110 7 0111
                    8 1000 9 1001 A 1010 B 1011
                    C 1100 D 1101 E 1110 F 1111
                } $ch]
            }
            puts $fout $bin
        }
    }
    close $fin
    close $fout
}

set repo_root [file normalize [file join [file dirname [info script]] ..]]
set project_dir [file join $repo_root vivado lab5_project]
set project_name lab5_project
set ip_root [file join $repo_root vivado test-cpu project project_3 project_3.srcs sources_1 ip]

file mkdir $project_dir

create_project $project_name $project_dir -force -part xc7a35tcpg236-1
set_property target_language Verilog [current_project]
set_property default_lib xil_defaultlib [current_project]

add_files -norecurse [file join $repo_root vsrc include config.sv]
add_files -norecurse [file join $repo_root vsrc include common.sv]
add_files -norecurse [file join $repo_root vsrc util IBusToCBus.sv]
add_files -norecurse [file join $repo_root vsrc util DBusToCBus.sv]
add_files -norecurse [file join $repo_root vsrc util CBusArbiter.sv]
add_files -norecurse [file join $repo_root vsrc util mmu.sv]
add_files -norecurse [file join $repo_root vsrc src core.sv]
add_files -norecurse [file join $repo_root vsrc VTop.sv]
add_files -norecurse [file join $repo_root vsrc mycpu_top.sv]
add_files -norecurse [file join $repo_root vivado src with_delay bram_wrapper.sv]
add_files -norecurse [file join $repo_root vivado src with_delay cbus_crossbar.sv]
add_files -norecurse [file join $repo_root vivado src with_delay soc_top.sv]
add_files -norecurse [file join $repo_root vivado src with_delay basys3_top.sv]
add_files -norecurse [file join $repo_root vivado src device.sv]
add_files -norecurse [file join $repo_root vivado src device.svh]
add_files -fileset constrs_1 -norecurse [file join $repo_root vivado src Basys-3-Master.xdc]
add_files -norecurse [file join $ip_root clk_wiz_0 clk_wiz_0_stub.v]
add_files -norecurse [file join $ip_root bram_0 bram_0_stub.v]
add_files -norecurse [file join $ip_root clk_wiz_0 clk_wiz_0.dcp]
add_files -norecurse [file join $ip_root bram_0 bram_0.dcp]
add_files -fileset sim_1 -norecurse [file join $repo_root vivado src with_delay simtop.sv]

set_property include_dirs [list [file join $repo_root vsrc] [file join $ip_root clk_wiz_0]] [get_filesets sources_1]
set_property include_dirs [list [file join $repo_root vsrc] [file join $ip_root clk_wiz_0]] [get_filesets sim_1]
set_property SCOPED_TO_REF clk_wiz_0 [get_files [file join $ip_root clk_wiz_0 clk_wiz_0.dcp]]
set_property SCOPED_TO_REF bram_0 [get_files [file join $ip_root bram_0 bram_0.dcp]]
set_property top basys3_top [get_filesets sources_1]
set_property top simtop [get_filesets sim_1]

update_compile_order -fileset sources_1
update_compile_order -fileset sim_1

close_project
