set repo_root {G:/GitHub/26-Arch}
set project_path [file join $repo_root vivado test-cpu project project_3 project_3.xpr]

open_project $project_path

add_files -norecurse [file join $repo_root vivado src spi_flash_disk.sv]

update_compile_order -fileset sources_1

close_project

puts "Added spi_flash_disk.sv to project successfully!"