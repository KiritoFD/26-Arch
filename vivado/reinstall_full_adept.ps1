# Run as Administrator
#requires -RunAsAdministrator
$ErrorActionPreference = "Continue"

Write-Host "=== Step 1: Stop processes ===" -ForegroundColor Cyan
Get-Process hw_server,cs_server,vivado,djtgcfg,dmgr -ErrorAction SilentlyContinue | Stop-Process -Force
Start-Sleep -Seconds 2

Write-Host "`n=== Step 2: Uninstall existing Adept 2.30.4 ===" -ForegroundColor Cyan
$uninst = "C:\Program Files\Digilent\uninstall.exe"
if (Test-Path $uninst) {
    Write-Host "  Running: $uninst /S"
    $p = Start-Process -FilePath $uninst -ArgumentList "/S" -Wait -PassThru
    Write-Host "  ExitCode: $($p.ExitCode)"
    Start-Sleep -Seconds 3
} else {
    Write-Host "  uninstall.exe not found, skipping"
}

Write-Host "`n=== Step 3: Verify Adept uninstalled ===" -ForegroundColor Cyan
$digilentDir = "C:\Program Files\Digilent"
if (Test-Path $digilentDir) {
    Write-Host "  Digilent dir still exists, removing..."
    Remove-Item $digilentDir -Recurse -Force -ErrorAction SilentlyContinue
}

# Clean any leftover DLLs in System32
$oldDlls = @(
    "C:\Windows\System32\dmgr.dll","C:\Windows\System32\dpcomm.dll",
    "C:\Windows\System32\djtg.dll","C:\Windows\System32\dabs.dll",
    "C:\Windows\System32\dspi.dll","C:\Windows\System32\dpceif.dll",
    "C:\Windows\System32\ftd2xx.dll",
    "C:\Windows\SysWOW64\dmgr.dll","C:\Windows\SysWOW64\dpcomm.dll",
    "C:\Windows\SysWOW64\djtg.dll","C:\Windows\SysWOW64\dabs.dll",
    "C:\Windows\SysWOW64\ftd2xx.dll"
)
foreach ($dll in $oldDlls) {
    if (Test-Path $dll) {
        takeown /F $dll /A 2>&1 | Out-Null
        icacls $dll /grant administrators:F 2>&1 | Out-Null
        Remove-Item $dll -Force -ErrorAction SilentlyContinue
        Write-Host "  Deleted: $dll"
    }
}

# Clean registry
foreach ($key in @("HKLM:\SOFTWARE\Digilent","HKLM:\SOFTWARE\WOW6432Node\Digilent")) {
    if (Test-Path $key) {
        Remove-Item $key -Recurse -Force -ErrorAction SilentlyContinue
        Write-Host "  Deleted reg: $key"
    }
}

Write-Host "`n=== Step 4: Run Vivado install_digilent.exe (FULL Adept Runtime) ===" -ForegroundColor Cyan
$installExe = "C:\Xilinx\Vivado\2019.2\data\xicom\cable_drivers\nt64\digilent\install_digilent.exe"
if (Test-Path $installExe) {
    Write-Host "  Running: $installExe (without /S, may show GUI)"
    Write-Host "  If GUI appears, click through to install everything"
    $p = Start-Process -FilePath $installExe -Wait -PassThru
    Write-Host "  ExitCode: $($p.ExitCode)"
} else {
    Write-Host "  install_digilent.exe not found!"
    exit 1
}

Write-Host "`n=== Step 5: Verify Adept Runtime DLLs installed ===" -ForegroundColor Cyan
Get-ChildItem "C:\Windows\System32" -Filter "*.dll" -ErrorAction SilentlyContinue | Where-Object {
    $_.Name -match "^(dmgr|dpcomm|djtg|dabs|dspi|dpceif|ftd2xx)"
} | ForEach-Object {
    Write-Host "  $($_.Name) v$($_.VersionInfo.FileVersion) ($($_.LastWriteTime))" -ForegroundColor Green
}

Write-Host "`n=== Step 6: Check Digilent install dir ===" -ForegroundColor Cyan
if (Test-Path "C:\Program Files\Digilent") {
    Get-ChildItem "C:\Program Files\Digilent" -Recurse -File -ErrorAction SilentlyContinue | Where-Object {
        $_.Name -match "^(dmgr|dpcomm|djtg|dabs|dspi|dpceif|ftd2xx)"
    } | ForEach-Object {
        Write-Host "  $($_.FullName) v$($_.VersionInfo.FileVersion)"
    }
}

Write-Host "`n=== Step 7: Remove and re-scan FTDI devices ===" -ForegroundColor Cyan
$devs = Get-PnpDevice | Where-Object { $_.InstanceId -match "VID_0403&PID_6010" }
foreach ($d in $devs) {
    Write-Host "  Removing: $($d.InstanceId)"
    & pnputil /remove-device "$($d.InstanceId)" 2>&1 | Out-Null
}
Start-Sleep -Seconds 2
pnputil /scan-devices 2>&1 | ForEach-Object { Write-Host "  $_" }
Start-Sleep -Seconds 3

Write-Host "`n=== Step 8: Device state ===" -ForegroundColor Cyan
Get-PnpDevice | Where-Object { $_.InstanceId -match "VID_0403&PID_6010" } | Format-Table FriendlyName, Status, Class, InstanceId -AutoSize

Write-Host "`n=== Step 9: Test hw_server ===" -ForegroundColor Cyan
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
