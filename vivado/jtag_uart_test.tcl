# jtag_uart_test.tcl - Read xv6 UART output via BSCANE2 USER1
# Uses xsdb's jtag sequence API with -capture option

# Connect and select FPGA target
connect -url TCP:localhost:3121
jtag targets 2
puts "=== Selected target 2 (xc7a35t) ==="

# BSCANE2 USER1 instruction: JTAG_CHAIN=1, IR code=0x02
# Artix-7 IR length = 6 bits
# DR = 9 bits [valid, data[7:0]]

puts "=== Reading 2000 JTAG UART samples ==="
set valid_count 0
set total 2000

for {set i 0} {$i < $total} {incr i} {
    # Create JTAG sequence: RESET -> IR(USER1) -> DR(capture 9 bits)
    set seq [jtag sequence]
    $seq state RESET
    $seq irshift -integer 6 0x02
    $seq drshift -capture -tdi 0 9
    set rx_raw [$seq run -integer -single]
    $seq delete

    # rx_raw is now an integer (9 bits captured)
    set valid [expr {($rx_raw >> 8) & 0x1}]
    set data [expr {$rx_raw & 0xFF}]

    if {$valid} {
        incr valid_count
        if {$data >= 0x20 && $data <= 0x7E} {
            puts -nonewline [format "%c" $data]
        } else {
            puts -nonewline [format "\\x%02x" $data]
        }
        flush stdout
    }
}
puts ""
puts "=== Test complete: $valid_count valid bytes out of $total reads ==="
disconnect
