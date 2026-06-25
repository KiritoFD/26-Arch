# Run as Administrator
#requires -RunAsAdministrator
$ErrorActionPreference = "Continue"

Write-Host "=== Step 1: Stop processes ===" -ForegroundColor Cyan
Get-Process hw_server,cs_server,vivado -ErrorAction SilentlyContinue | Stop-Process -Force
Start-Sleep -Seconds 2

Write-Host "`n=== Step 2: Take ownership and delete old Adept DLLs in System32 ===" -ForegroundColor Cyan
$oldDlls = @(
    "C:\Windows\System32\dmgr.dll",
    "C:\Windows\System32\dpcomm.dll",
    "C:\Windows\System32\djtg.dll",
    "C:\Windows\System32\dabs.dll",
    "C:\Windows\System32\dspi.dll",
    "C:\Windows\System32\dpceif.dll",
    "C:\Windows\System32\ftd2xx.dll",
    "C:\Windows\SysWOW64\dmgr.dll",
    "C:\Windows\SysWOW64\dpcomm.dll",
    "C:\Windows\SysWOW64\djtg.dll",
    "C:\Windows\SysWOW64\dabs.dll",
    "C:\Windows\SysWOW64\ftd2xx.dll"
)
foreach ($dll in $oldDlls) {
    if (Test-Path $dll) {
        takeown /F $dll /A 2>&1 | Out-Null
        icacls $dll /grant administrators:F 2>&1 | Out-Null
        try {
            Remove-Item $dll -Force -ErrorAction Stop
            Write-Host "  Deleted: $dll"
        } catch {
            Write-Host "  Failed to delete: $dll - $_"
        }
    }
}

Write-Host "`n=== Step 3: Run Vivado's install_digilent.exe (full runtime installer) ===" -ForegroundColor Cyan
$installExe = "C:\Xilinx\Vivado\2019.2\data\xicom\cable_drivers\nt64\digilent\install_digilent.exe"
if (Test-Path $installExe) {
    Write-Host "  Running: $installExe /S"
    $p = Start-Process -FilePath $installExe -ArgumentList "/S" -Verb RunAs -Wait -PassThru
    Write-Host "  ExitCode: $($p.ExitCode)"
} else {
    Write-Host "  install_digilent.exe not found!"
}

Write-Host "`n=== Step 4: Copy ftd2xx.dll from Digilent to System32 ===" -ForegroundColor Cyan
$src = "C:\Program Files\Digilent\Runtime\UsbDriver2\amd64\ftd2xx64.dll"
$dst = "C:\Windows\System32\ftd2xx.dll"
if (Test-Path $src) {
    takeown /F $dst /A 2>&1 | Out-Null
    icacls $dst /grant administrators:F 2>&1 | Out-Null
    Copy-Item $src $dst -Force -ErrorAction SilentlyContinue
    if (Test-Path $dst) {
        Write-Host "  Copied: $src -> $dst" -ForegroundColor Green
        Write-Host "  Version: $((Get-Item $dst).VersionInfo.FileVersion)"
    } else {
        Write-Host "  Failed to copy"
    }
}

# Also 32-bit
$src32 = "C:\Program Files\Digilent\Runtime\UsbDriver2\i386\ftd2xx.dll"
$dst32 = "C:\Windows\SysWOW64\ftd2xx.dll"
if (Test-Path $src32) {
    Copy-Item $src32 $dst32 -Force -ErrorAction SilentlyContinue
    Write-Host "  Copied 32-bit: $src32 -> $dst32"
}

Write-Host "`n=== Step 5: Check Adept DLLs in System32 ===" -ForegroundColor Cyan
Get-ChildItem "C:\Windows\System32" -Filter "*.dll" -ErrorAction SilentlyContinue | Where-Object { $_.Name -match "^(dmgr|dpcomm|djtg|dabs|dspi|dpceif|ftd2xx)" } | ForEach-Object {
    Write-Host "  $($_.Name) v$($_.VersionInfo.FileVersion) ($($_.LastWriteTime))"
}

Write-Host "`n=== Step 6: Remove and re-scan FTDI devices ===" -ForegroundColor Cyan
$devs = Get-PnpDevice | Where-Object { $_.InstanceId -match "VID_0403&PID_6010" }
foreach ($d in $devs) {
    Write-Host "  Removing: $($d.InstanceId)"
    & pnputil /remove-device "$($d.InstanceId)" 2>&1 | Out-Null
}
Start-Sleep -Seconds 2
pnputil /scan-devices 2>&1 | ForEach-Object { Write-Host "  $_" }
Start-Sleep -Seconds 3

Write-Host "`n=== Step 7: Device state ===" -ForegroundColor Cyan
Get-PnpDevice | Where-Object { $_.InstanceId -match "VID_0403&PID_6010" } | Format-Table FriendlyName, Status, Class, InstanceId -AutoSize

Write-Host "`n=== Step 8: Test hw_server ===" -ForegroundColor Cyan
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
