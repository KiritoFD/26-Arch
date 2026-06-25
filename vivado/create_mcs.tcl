set repo_root {G:/GitHub/26-Arch}
set bitstream_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.bit]
set mcs_file_path [file join $repo_root vivado test-cpu project project_3 full_flash.mcs]

write_cfgmem -format mcs -interface qspi -size 32 \
    -loadbit "up 0x00000000 $bitstream_path" \
    -file $mcs_file_path \
    -force

puts "MCS file created: $mcs_file_path"