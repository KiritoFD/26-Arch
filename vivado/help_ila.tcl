# Display ILA data directly via display_hw_ila_data
set repo_root {G:/GitHub/26-Arch}
set bitstream_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.bit]
set ltx_path [file join $repo_root vivado test-cpu project project_3 project_3.runs impl_1 basys3_top.ltx]

open_hw_manager
connect_hw_server -url localhost:3121 -allow_non_jtag
set targets [get_hw_targets -quiet]
if {[llength $targets] > 0} {
    current_hw_target [lindex $targets 0]
    open_hw_target
    set dev [lindex [get_hw_devices] 0]
    current_hw_device $dev
    set_property PROGRAM.FILE $bitstream_path $dev
    set_property PROBES.FILE $ltx_path $dev
    refresh_hw_device $dev
    set ilas [get_hw_ilas -quiet]
    if {[llength $ilas] > 0} {
        set ila_core [lindex $ilas 0]

        # Run ILA
        run_hw_ila $ila_core
        after 3000
        refresh_hw_device $dev

        # Upload data
        puts "Uploading..."
        set hw_ila_data [upload_hw_ila $ila_core]
        puts "Data: $hw_ila_data"
        wait_on_hw_ila $ila_core

        # Display data to stdout
        puts "=========================================="
        puts "=== display_hw_ila_data ==="
        puts "=========================================="
        catch {display_hw_ila_data $hw_ila_data} disp_err
        puts "Display err: $disp_err"

        # Try current_hw_ila_data approach
        puts "=========================================="
        puts "=== current_hw_ila_data ==="
        puts "=========================================="
        catch {current_hw_ila_data $hw_ila_data} chd_err
        puts "current_hw_ila_data err: $chd_err"

        # Try write_hw_ila_data with -quiet
        puts "=========================================="
        puts "=== write_hw_ila_data -quiet ==="
        puts "=========================================="
        catch {write_hw_ila_data -quiet -force -csv -file {G:/GitHub/26-Arch/vivado/ila_q.csv} $hw_ila_data} werr
        puts "write err: $werr"

        # Try -export_format
        puts "=========================================="
        puts "=== write_hw_ila_data -format csv ==="
        puts "=========================================="
        catch {write_hw_ila_data -force -format csv -file {G:/GitHub/26-Arch/vivado/ila_fmt.csv} $hw_ila_data} ferr
        puts "format err: $ferr"

        # Check what files exist
        puts "=========================================="
        puts "=== Files ==="
        foreach f [glob -nocomplain {G:/GitHub/26-Arch/vivado/ila_*.csv}] {
            puts "  $f size=[file size $f]"
        }

        # List properties of hw_ila_data
        puts "=========================================="
        puts "=== Properties of hw_ila_data ==="
        catch {set props [list_property $hw_ila_data]} perr
        puts "list_property err: $perr"
        catch {puts "props: $props"} perr2
    }
    close_hw_target
}
disconnect_hw_server
close_hw_manager
