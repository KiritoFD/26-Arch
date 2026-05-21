set repo_root [file normalize [file join [file dirname [info script]] ..]]
set project_path [file join $repo_root vivado lab5_project lab5_project.xpr]

open_project $project_path
update_compile_order -fileset sources_1
reset_run synth_1
launch_runs synth_1 -jobs 4
wait_on_run synth_1
close_project
