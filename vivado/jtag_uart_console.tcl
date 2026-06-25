# jtag_uart_console.tcl - Read xv6 UART output via BSCANE2 USER1 and send input via USER2
# Usage: xsdb jtag_uart_console.tcl
# Run after FPGA is programmed with bitstream

# Connect to hw_server
connect -url localhost:3121

# List and select JTAG target
puts "=== Available JTAG targets ==="
jtag targets
jtag targets 1

# BSCANE2 USER1 instruction (JTAG_CHAIN=1): TX FIFO read
# BSCANE2 USER2 instruction (JTAG_CHAIN=2): RX FIFO write
# Artix-7 IR length = 6 bits
# USER1 IR code = 0x02, USER2 IR code = 0x03
# DR = 9 bits [valid, data[7:0]]

set USER1_IR 0x02
set USER2_IR 0x03
set IR_LEN 6
set DR_LEN 9

puts "=== Starting JTAG UART console ==="
puts "=== Reading xv6 output via BSCANE2 USER1 (Ctrl+C to exit) ==="
puts ""

set total_bytes 0
set idle_count 0
set max_iterations 100000

for {set i 0} {$i < $max_iterations} {incr i} {
    # Create JTAG sequence to read USER1
    set seq [jtag sequence]
    $seq state RESET
    $seq irshift -integer $IR_LEN $USER1_IR
    $seq drshift -integer $DR_LEN 0x000
    set rx_raw [$seq run]
    $seq delete

    # rx_raw is a list of captured TDO values
    # Parse the 9-bit result
    set rx_data 0
    if {[llength $rx_raw] > 0} {
        set rx_data [lindex $rx_raw 0]
    }

    set valid [expr {($rx_data >> 8) & 0x1}]
    set data [expr {$rx_data & 0xFF}]

    if {$valid} {
        if {$data >= 0x20 && $data <= 0x7E} {
            puts -nonewline [format "%c" $data]
        } elseif {$data == 0x0A} {
            puts -nonewline "\n"
        } elseif {$data == 0x0D} {
            # Skip CR
        } elseif {$data == 0x09} {
            puts -nonewline "\t"
        } else {
            puts -nonewline [format "\\x%02x" $data]
        }
        flush stdout
        incr total_bytes
        set idle_count 0
    } else {
        incr idle_count
        if {$idle_count % 200 == 0} {
            after 100
        }
        if {$idle_count % 5000 == 0 && $idle_count > 0} {
            puts "\n[INFO] Waiting... ($total_bytes bytes received so far)"
            flush stdout
        }
    }
}

puts "\n=== Done. Total bytes received: $total_bytes ==="
disconnect
