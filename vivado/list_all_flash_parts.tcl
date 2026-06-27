# List ALL available flash parts to find alternatives
open_hw
connect_hw_server
open_hw_target
set device [get_hw_devices xc7a35t_0]
current_hw_device $device

puts "=== ALL available flash parts ==="
set parts [get_cfgmem_parts -of_objects $device]
puts "Total: [llength $parts] parts"
foreach p $parts {
    puts "  $p"
}

# Also list just the SPI parts (n25q, mt25q, etc.)
puts "=== N25Q/MT25Q parts ==="
foreach p $parts {
    set pl [string tolower $p]
    if {[string match "*25q*" $pl] || [string match "*25p*" $pl]} {
        puts "  $p"
    }
}

close_hw_target
disconnect_hw_server
close_hw
