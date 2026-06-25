# Run after installing Adept Runtime 2.21+
#requires -RunAsAdministrator
$ErrorActionPreference = "Continue"

Write-Host "=== Step 1: Check Adept dmgr.dll version ===" -ForegroundColor Cyan
$dmgr = Get-Item "C:\Windows\System32\dmgr.dll" -ErrorAction SilentlyContinue
if ($dmgr) {
    Write-Host "Version: $($dmgr.VersionInfo.FileVersion)"
    Write-Host "LastWrite: $($dmgr.LastWriteTime)"
}

Write-Host "`n=== Step 2: Re-scan devices ===" -ForegroundColor Cyan
pnputil /scan-devices 2>&1 | ForEach-Object { Write-Host $_ }

Write-Host "`n=== Step 3: Device state ===" -ForegroundColor Cyan
Get-PnpDevice | Where-Object { $_.InstanceId -match "VID_0403&PID_6010" -and $_.Status -eq "OK" } | Format-Table -AutoSize FriendlyName, Status, Class, InstanceId

Write-Host "`n=== Step 4: Restart hw_server ===" -ForegroundColor Cyan
Get-Process hw_server -ErrorAction SilentlyContinue | Stop-Process -Force
Start-Sleep -Seconds 1
$hw = Start-Process -FilePath "C:\Xilinx\Vivado\2019.2\bin\unwrapped\win64.o\hw_server.exe" -PassThru -NoNewWindow
Start-Sleep -Seconds 2
Write-Host "hw_server PID: $($hw.Id)"

Write-Host "`n=== Step 5: Connect via Vivado ===" -ForegroundColor Cyan
& "C:\Xilinx\Vivado\2019.2\bin\vivado.bat" -mode batch -nojournal -nolog -notrace -source "g:/GitHub/26-Arch/vivado/list_hw2.tcl" 2>&1 | ForEach-Object { Write-Host $_ }

Stop-Process -Id $hw.Id -Force -ErrorAction SilentlyContinue

Write-Host "`n=== DONE ===" -ForegroundColor Green
Write-Host "If you see 'xc7a35t_0' device above, we can proceed to flash the MCS file."
Write-Host "Press Enter to close..." -ForegroundColor Cyan
Read-Host
