# Check JTAG connection
open_hw
connect_hw_server
puts "Available targets:"
foreach t [get_hw_targets] {
    puts "  $t"
    current_hw_target $t
    open_hw_target
    puts "  Devices:"
    foreach d [get_hw_devices] {
        puts "    $d"
    }
    close_hw_target
}
disconnect_hw_server
close_hw
