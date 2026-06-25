# Recreate bram_1 IP with NO registered output (combinational read)
set repo_root {G:/GitHub/26-Arch}
set project_path [file join $repo_root vivado test-cpu project project_3 project_3.xpr]

open_project $project_path

# Delete old bram_1 if exists
catch { remove_ip [get_ips bram_1] }

# Create the IP
create_ip -name blk_mem_gen -vendor xilinx.com -library ip -module_name bram_1

# Configure: 32-bit wide, 16384 depth, NO registered output
set_property -dict [list \
    CONFIG.Memory_Type {Single_Port_RAM} \
    CONFIG.Use_Byte_Write_Enable {true} \
    CONFIG.Byte_Size {8} \
    CONFIG.Write_Width_A {32} \
    CONFIG.Read_Width_A {32} \
    CONFIG.Write_Depth_A {16384} \
    CONFIG.Enable_A {Always_Enabled} \
    CONFIG.Register_PortA_Output_of_Memory_Primitives {false} \
    CONFIG.Use_RSTA_Pin {false} \
    CONFIG.Load_Init_File {true} \
    CONFIG.Coe_File [file join $repo_root ready-to-run lab5 fs_mini.coe] \
    CONFIG.Fill_Remaining_Memory_Locations {true} \
    CONFIG.Remaining_Memory_Locations {00000000} \
] [get_ips bram_1]

# Generate the IP
generate_target all [get_ips bram_1]

puts "bram_1 IP created (no registered output)!"

close_project
