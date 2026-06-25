# List available flash parts for xc7a35t
open_hw
connect_hw_server -url localhost:3121
open_hw_target
set device [get_hw_devices xc7a35t_0]
current_hw_device $device
# Try to create config memory with various part names to find supported ones
set flash_parts [list \
    "n25q32-3.3v-spi-x1_x2_x4" \
    "n25q32-1.8v-spi-x1_x2_x4" \
    "n25q32-3.3v-spi-x1_x4" \
    "mt25ql256-spi-x1_x2_x4" \
    "mt25qu256-spi-x1_x2_x4" \
    "mt25ql256-spi-x1_x4" \
]
foreach p $flash_parts {
    if {[catch {create_hw_cfgmem -hw_device $device $p} err]} {
        puts "NOT_SUPPORTED: $p"
    } else {
        puts "SUPPORTED: $p"
        delete_hw_cfgmem $p
    }
}
close_hw_target
disconnect_hw_server
close_hw
