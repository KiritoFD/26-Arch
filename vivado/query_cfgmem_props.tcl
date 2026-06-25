# Query cfgmem properties
open_hw
connect_hw_server -url localhost:3121
open_hw_target
set device [get_hw_devices xc7a35t_0]
current_hw_device $device
set cfgmem [create_hw_cfgmem -hw_device $device "n25q32-3.3v-spi-x1_x2_x4"]
puts "=== Configurable properties on hw_cfgmem ==="
set props [list_property $cfgmem]
foreach p $props {
    puts "  $p"
}
puts "=== Current property values ==="
foreach p $props {
    if {[catch {set val [get_property $p $cfgmem]} err]} {
        puts "  $p = (error: $err)"
    } else {
        puts "  $p = $val"
    }
}
close_hw_target
disconnect_hw_server
close_hw
