# JTAG UART read - more reads to drain FIFO
connect -url TCP:localhost:3121
jtag targets 2
puts "=== Target selected ==="

set valid_count 0
set total 5000
set chars ""

for {set i 0} {$i < $total} {incr i} {
    set seq [jtag sequence]
    $seq state RESET
    $seq irshift -integer 6 0x02
    $seq drshift -capture -tdi 0 9
    set rx_raw [$seq run -integer -single]
    $seq delete

    set valid [expr {($rx_raw >> 8) & 0x1}]
    set data [expr {$rx_raw & 0xFF}]

    if {$valid} {
        incr valid_count
        if {$data >= 0x20 && $data <= 0x7E} {
            append chars [format "%c" $data]
        } else {
            append chars [format "\\x%02x" $data]
        }
    }
}
puts ""
puts "=== Result: $valid_count valid bytes out of $total reads ==="
puts "=== Chars: $chars ==="
disconnect
