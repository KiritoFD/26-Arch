open_hw_manager
catch {connect_hw_server -url localhost:3121 -allow_non_jtag}
refresh_hw_server
set hw_targets [get_hw_targets]
puts "Targets: \"
foreach t \ {
    puts "Target: \"
}
# Also try open_hw_target without specifying
catch {
    open_hw_target -allow_non_jtag
    set devices [get_hw_devices]
    puts "Devices: \"
    close_hw_target
}
disconnect_hw_server
close_hw_manager
