# Program the FPGA with the new bitstream (Vivado 2018.3 syntax)
set repo_root {G:/GitHub/26-Arch}
set bitstream [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.bit]

# Open hardware manager (2018.3 syntax)
open_hw

# Connect to hardware server
connect_hw_server

# Open hardware target
open_hw_target

# Get the FPGA device
set device [lindex [get_hw_devices] 0]
current_hw_device $device

# Set the bitstream file
set_property PROGRAM.FILE $bitstream $device

# Program the device
program_hw_devices $device

puts "FPGA programmed successfully with: $bitstream"

# Close
close_hw_target
disconnect_hw_server
