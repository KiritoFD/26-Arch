# JTAG UART read using low-level JTAG state control
# This ensures CAPTURE-DR state is entered properly
connect -url TCP:localhost:3121
jtag targets 2
puts "=== Target selected ==="

set valid_count 0
set total 5000
set chars ""

for {set i 0} {$i < $total} {incr i} {
    set seq [jtag sequence]
    $seq state RESET
    $seq state IDLE
    # Select USER1 instruction (IR=0x02, 6-bit)
    $seq irshift -integer 6 0x02
    $seq state IDLE
    # Go through CAPTURE-DR -> SHIFT-DR -> UPDATE-DR
    $seq state DRSELECT
    $seq state DRCAPTURE
    $seq state DRSHIFT
    $seq drshift -capture -tdi 0 9
    $seq state DREXIT1
    $seq state DRPAUSE
    $seq state DREXIT2
    $seq state DRSHIFT
    $seq state DREXIT1
    $seq state DRUPDATE
    $seq state IDLE
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
