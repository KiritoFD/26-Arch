# JTAG 烧 xv6 bitstream (无 ILA, 含新 kernel)
open_hw
connect_hw_server -quiet
set targets [get_hw_targets -quiet]
puts "==== hw_targets: $targets ===="
if {[llength $targets] == 0} {
    puts "ERROR: no hw_target found"
    exit 1
}
open_hw_target [lindex $targets 0]

set devices [get_hw_devices -quiet]
puts "==== hw_devices: $devices ===="
if {[llength $devices] == 0} {
    puts "ERROR: no hw_device found"
    exit 1
}
set dev [lindex $devices 0]
current_hw_device $dev

set bit "g:/GitHub/26-Arch/vivado/xv6_project/xv6_project.runs/impl_1/basys3_top.bit"
set_property PROGRAM.FILE $bit $dev

puts "==== Programming $bit ===="
program_hw_devices $dev
puts "==== Program done ===="

close_hw_target
disconnect_hw_server
exit
