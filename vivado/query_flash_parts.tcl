# Query flash parts supported by the device and try programming
open_hw
connect_hw_server -url localhost:3121
open_hw_target
set device [get_hw_devices xc7a35t_0]
current_hw_device $device

# Get flash parts attached to device
puts "=== Flash parts on device ==="
set parts [get_cfgmem_parts -of_objects $device]
puts "Parts: $parts"

# Try the first n25q part
set flash_part ""
foreach p $parts {
    puts "  Examining: $p"
    if {[string match "*n25q*" [string tolower $p]]} {
        set flash_part $p
    }
}
if {$flash_part eq ""} {
    set flash_part [lindex $parts 0]
}
puts "Selected flash part: $flash_part"

close_hw_target
disconnect_hw_server
close_hw
