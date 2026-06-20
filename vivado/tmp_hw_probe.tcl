open_hw
connect_hw_server
open_hw_target
current_hw_device [lindex [get_hw_devices] 0]
current_hw_device [lindex [get_hw_devices] 0]
refresh_hw_device [current_hw_device]
puts [get_property PART [current_hw_device]]
puts [get_property PROGRAM.FILE [current_hw_device]]
close_hw_target
disconnect_hw_server
exit
