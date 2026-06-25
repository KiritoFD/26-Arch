# Run as Administrator
#requires -RunAsAdministrator
$ErrorActionPreference = "Continue"

Write-Host "=== Step 1: Stop processes ===" -ForegroundColor Cyan
Get-Process hw_server,cs_server,vivado -ErrorAction SilentlyContinue | Stop-Process -Force
Start-Sleep -Seconds 2

Write-Host "`n=== Step 2: Copy ftd2xx.dll to System32 (64-bit) ===" -ForegroundColor Cyan
$src64 = "C:\Program Files\Digilent\Runtime\UsbDriver2\amd64\ftd2xx64.dll"
$dst64 = "C:\Windows\System32\ftd2xx.dll"
if (Test-Path $src64) {
    takeown /F $dst64 /A 2>&1 | Out-Null
    icacls $dst64 /grant administrators:F 2>&1 | Out-Null
    Copy-Item $src64 $dst64 -Force -ErrorAction Stop
    Write-Host "  Copied: $src64 -> $dst64" -ForegroundColor Green
    Write-Host "  Version: $((Get-Item $dst64).VersionInfo.FileVersion)"
} else {
    Write-Host "  Source not found: $src64" -ForegroundColor Red
}

Write-Host "`n=== Step 3: Copy ftd2xx.dll to SysWOW64 (32-bit) ===" -ForegroundColor Cyan
$src32 = "C:\Program Files\Digilent\Runtime\UsbDriver2\i386\ftd2xx.dll"
$dst32 = "C:\Windows\SysWOW64\ftd2xx.dll"
if (Test-Path $src32) {
    takeown /F $dst32 /A 2>&1 | Out-Null
    icacls $dst32 /grant administrators:F 2>&1 | Out-Null
    Copy-Item $src32 $dst32 -Force -ErrorAction Stop
    Write-Host "  Copied: $src32 -> $dst32" -ForegroundColor Green
} else {
    Write-Host "  Source not found: $src32" -ForegroundColor Red
}

Write-Host "`n=== Step 4: Verify DLLs in System32 ===" -ForegroundColor Cyan
Get-ChildItem "C:\Windows\System32" -Filter "*.dll" -ErrorAction SilentlyContinue | Where-Object {
    $_.Name -match "^(dmgr|dpcomm|djtg|dabs|dspi|dpceif|ftd2xx)"
} | ForEach-Object {
    Write-Host "  $($_.Name) v$($_.VersionInfo.FileVersion) ($($_.LastWriteTime))"
}

Write-Host "`n=== Step 5: Remove and re-scan FTDI devices ===" -ForegroundColor Cyan
$devs = Get-PnpDevice | Where-Object { $_.InstanceId -match "VID_0403&PID_6010" }
foreach ($d in $devs) {
    Write-Host "  Removing: $($d.InstanceId)"
    & pnputil /remove-device "$($d.InstanceId)" 2>&1 | Out-Null
}
Start-Sleep -Seconds 2
pnputil /scan-devices 2>&1 | ForEach-Object { Write-Host "  $_" }
Start-Sleep -Seconds 3

Write-Host "`n=== Step 6: Device state ===" -ForegroundColor Cyan
Get-PnpDevice | Where-Object { $_.InstanceId -match "VID_0403&PID_6010" } | Format-Table FriendlyName, Status, Class, InstanceId -AutoSize

Write-Host "`n=== Step 7: Test hw_server ===" -ForegroundColor Cyan
Get-Process hw_server,cs_server -ErrorAction SilentlyContinue | Stop-Process -Force
Start-Sleep -Seconds 1
$hw = Start-Process -FilePath "C:\Xilinx\Vivado\2019.2\bin\unwrapped\win64.o\hw_server.exe" -PassThru -NoNewWindow
Start-Sleep -Seconds 3
Write-Host "hw_server PID: $($hw.Id)"

& "C:\Xilinx\Vivado\2019.2\bin\vivado.bat" -mode batch -nojournal -nolog -notrace -source "g:/GitHub/26-Arch/vivado/list_hw2.tcl" 2>&1 | ForEach-Object { Write-Host $_ }

Stop-Process -Id $hw.Id -Force -ErrorAction SilentlyContinue

Write-Host "`n=== DONE ===" -ForegroundColor Green
Write-Host "Press Enter to close..." -ForegroundColor Cyan
Read-Host
