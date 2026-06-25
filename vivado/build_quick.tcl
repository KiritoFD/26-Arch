# Simplified build: skip IP upgrade, go straight to synth+impl+bitstream
set repo_root {G:/GitHub/26-Arch}
set project_path [file join $repo_root vivado test-cpu project project_3 project_3.xpr]

open_project $project_path

# Add jtag_uart.sv if not already in project
set jtag_uart_src [file join $repo_root vivado src jtag_uart.sv]
if {[llength [get_files -quiet jtag_uart.sv]] == 0} {
    add_files -norecurse $jtag_uart_src
    puts "Added jtag_uart.sv to project"
}

# Refresh all source files (pick up modifications)
update_compile_order -fileset sources_1

# Update BRAM COE
set coe_path [file join $repo_root ready-to-run lab5 xv6-kernel.coe]
set bram_ip [get_ips bram_0]
set_property -dict [list CONFIG.Coe_File $coe_path CONFIG.Load_Init_File {true}] $bram_ip

# Reset and run synth
reset_run synth_1
launch_runs synth_1 -jobs 4
wait_on_run synth_1

# Reset and run impl + bitstream
reset_run impl_1
launch_runs impl_1 -to_step write_bitstream -jobs 4
wait_on_run impl_1

puts "BUILD DONE"
close_project
