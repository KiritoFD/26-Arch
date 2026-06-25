set repo_root {G:/GitHub/26-Arch}
set bitstream_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.bit]
set fs_img_path [file join $repo_root third_party xv6-riscv fs.img]
set mcs_file_path [file join $repo_root vivado test-cpu project project_3 full_flash.mcs]

puts "Creating MCS file with bitstream..."

write_cfgmem -format mcs -interface qspi -size 32 \
    -loadbit "up 0x00000000 $bitstream_path" \
    -file $mcs_file_path \
    -force

puts "MCS file created: $mcs_file_path"

puts "\nNow you need to manually add fs.img to the MCS file."
puts "The fs.img should be placed at offset 0x00400000."