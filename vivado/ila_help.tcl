# Just check write_hw_ila_data syntax
puts "===== write_hw_ila_data help ====="
if {[catch {help write_hw_ila_data} err]} {
    puts "help failed: $err"
}
puts "===== direct -help ====="
if {[catch {write_hw_ila_data -help} err]} {
    puts "-help failed: $err"
}
puts "===== done ====="
