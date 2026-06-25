open_hw
catch {connect_hw_server -url localhost:3121 -allow_non_jtag}
puts "=== Connected to hw_server ==="

# List hw_servers and targets
set hw_targets [get_hw_targets]
puts "Targets found: [llength $hw_targets]"
foreach t $hw_targets {
    puts "  Target: $t"
    catch {open_hw_target $t}
    set devices [get_hw_devices]
    puts "  Devices: $devices"
    catch {close_hw_target $t}
}

# Try opening without specific target
catch {
    open_hw_target
    set devices [get_hw_devices]
    puts "Default target devices: $devices"
    close_hw_target
}

disconnect_hw_server
close_hw
