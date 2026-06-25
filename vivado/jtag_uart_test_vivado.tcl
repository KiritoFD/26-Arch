# jtag_uart_test_vivado.tcl - Quick test of BSCANE2 USER1 read via Vivado hw API
# Tests if JTAG UART bridge is working

open_hw
connect_hw_server -url localhost:3121
open_hw_target

set device [get_hw_devices xc7a35t_0]
current_hw_device $device

puts "=== Reading 200 JTAG UART samples via Vivado hw API ==="
set valid_count 0
set total 200

for {set i 0} {$i < $total} {incr i} {
    # Use Vivado's JTAG access via create_hw_jtag_seq
    # BSCANE2 USER1: IR=0x02 (6 bits), DR=9 bits [valid, data[7:0]]
    set seq [create_hw_jtag_seq -dr_length 9 -dr_value 0x000 -ir_length 6 -ir_value 0x02]
    # Run sequence
    # ... Vivado hw API is limited for raw JTAG access
    # Use device properties instead
    delete_hw_jtag_seq $seq
}

puts "Vivado hw API does not support direct JTAG sequence in batch mode."
puts "Need to use xsdb with proper connection."

close_hw_target
disconnect_hw_server
close_hw
