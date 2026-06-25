# Check connected hardware targets
open_hw
connect_hw_server -url localhost:3121 -quiet
set targets [get_hw_targets]
if {[llength $targets] > 0} {
    puts "FOUND_TARGETS:"
    foreach t $targets {
        puts "  TARGET: $t"
        current_hw_target $t
        open_hw_target -quiet
        set devices [get_hw_devices]
        foreach d $devices {
            puts "    DEVICE: $d"
        }
        close_hw_target -quiet
    }
} else {
    puts "NO_TARGETS_FOUND"
    # Try refresh
    refresh_hw_server
    set targets2 [get_hw_targets]
    puts "AFTER_REFRESH: [llength $targets2] targets"
}
disconnect_hw_server -quiet
