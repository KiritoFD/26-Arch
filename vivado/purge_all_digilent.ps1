# Run as Administrator
#requires -RunAsAdministrator
$ErrorActionPreference = "Continue"

Write-Host "=== Step 1: Stop all related processes ===" -ForegroundColor Cyan
Get-Process hw_server,cs_server,vivado,djtgcfg,dmgr,uninstall -ErrorAction SilentlyContinue | Stop-Process -Force
Start-Sleep -Seconds 3

Write-Host "`n=== Step 2: Uninstall Adept (if uninstall.exe exists) ===" -ForegroundColor Cyan
$uninst = "C:\Program Files\Digilent\uninstall.exe"
if (Test-Path $uninst) {
    Write-Host "  Running: $uninst /S"
    $p = Start-Process -FilePath $uninst -ArgumentList "/S" -Wait -PassThru
    Write-Host "  ExitCode: $($p.ExitCode)"
    Start-Sleep -Seconds 5
} else {
    Write-Host "  uninstall.exe not found, will delete dir manually"
}

Write-Host "`n=== Step 3: Delete all Digilent directories ===" -ForegroundColor Cyan
$dirsToDelete = @(
    "C:\Program Files\Digilent",
    "C:\Program Files (x86)\Digilent",
    "C:\Program Files\Common Files\Digilent",
    "C:\Program Files (x86)\Common Files\Digilent",
    "C:\ProgramData\Digilent",
    "$env:USERPROFILE\AppData\Local\Digilent",
    "$env:USERPROFILE\AppData\Roaming\Digilent"
)
foreach ($dir in $dirsToDelete) {
    if (Test-Path $dir) {
        try {
            Remove-Item $dir -Recurse -Force -ErrorAction Stop
        } catch {
            # Force take ownership and retry
            Get-ChildItem $dir -Recurse -Force -ErrorAction SilentlyContinue | ForEach-Object {
                takeown /F $_.FullName /A 2>&1 | Out-Null
                icacls $_.FullName /grant administrators:F 2>&1 | Out-Null
            }
            Remove-Item $dir -Recurse -Force -ErrorAction SilentlyContinue
        }
        if (Test-Path $dir) {
            Write-Host "  FAILED to delete: $dir" -ForegroundColor Red
        } else {
            Write-Host "  Deleted: $dir"
        }
    } else {
        Write-Host "  Not present: $dir"
    }
}

Write-Host "`n=== Step 4: Delete Digilent DLLs from System32/SysWOW64 ===" -ForegroundColor Cyan
$dllsToDelete = @(
    "C:\Windows\System32\dmgr.dll",
    "C:\Windows\System32\dpcomm.dll",
    "C:\Windows\System32\djtg.dll",
    "C:\Windows\System32\dabs.dll",
    "C:\Windows\System32\dspi.dll",
    "C:\Windows\System32\dpceif.dll",
    "C:\Windows\System32\ftd2xx.dll",
    "C:\Windows\System32\dabsusb.sys",
    "C:\Windows\System32\dmodusb.sys",
    "C:\Windows\System32\Drivers\ftdibus.sys",
    "C:\Windows\System32\Drivers\ftser2k.sys",
    "C:\Windows\SysWOW64\dmgr.dll",
    "C:\Windows\SysWOW64\dpcomm.dll",
    "C:\Windows\SysWOW64\djtg.dll",
    "C:\Windows\SysWOW64\dabs.dll",
    "C:\Windows\SysWOW64\dspi.dll",
    "C:\Windows\SysWOW64\dpceif.dll",
    "C:\Windows\SysWOW64\ftd2xx.dll"
)
foreach ($dll in $dllsToDelete) {
    if (Test-Path $dll) {
        takeown /F $dll /A 2>&1 | Out-Null
        icacls $dll /grant administrators:F 2>&1 | Out-Null
        try {
            Remove-Item $dll -Force -ErrorAction Stop
            Write-Host "  Deleted: $dll"
        } catch {
            Write-Host "  FAILED: $dll - $_"
        }
    }
}

Write-Host "`n=== Step 5: Remove all FTDI device instances ===" -ForegroundColor Cyan
$usbDevices = Get-PnpDevice | Where-Object { $_.InstanceId -match "VID_0403" } | Sort-Object InstanceId -Descending
foreach ($dev in $usbDevices) {
    Write-Host "  Removing: $($dev.FriendlyName) [$($dev.InstanceId)]"
    & pnputil /remove-device "$($dev.InstanceId)" 2>&1 | Out-Null
}

Write-Host "`n=== Step 6: Delete ALL FTDI/Digilent driver packages ===" -ForegroundColor Cyan
$driverList = pnputil /enum-drivers
$oemList = @()
$oemList += $driverList | Select-String -Pattern "ftdibus\.inf|ftdiport\.inf|digiftdibus\.inf|digiftdiport\.inf|dmodusb\.inf|xusbdrvr\.inf|dabsusb\.inf" -Context 1,0
foreach ($match in $oemList) {
    if ($match.Context.PreContext -match "Published Name:\s*(oem\d+\.inf)") {
        $inf = $matches[1]
        Write-Host "  Deleting: $inf"
        pnputil /delete-driver $inf /uninstall /force 2>&1 | Out-Null
    }
}

Write-Host "`n=== Step 7: Delete Digilent services ===" -ForegroundColor Cyan
$services = @("dmodusb","windrvr6","DigilentAdept","dmgr","djtg","dabs","dabsusb")
foreach ($svc in $services) {
    $s = Get-Service -Name $svc -ErrorAction SilentlyContinue
    if ($s) {
        Write-Host "  Removing service: $svc"
        sc.exe delete $svc 2>&1 | Out-Null
    }
}

Write-Host "`n=== Step 8: Clean Digilent registry ===" -ForegroundColor Cyan
$regKeys = @(
    "HKLM:\SOFTWARE\Digilent",
    "HKLM:\SOFTWARE\WOW6432Node\Digilent",
    "HKCU:\SOFTWARE\Digilent"
)
foreach ($key in $regKeys) {
    if (Test-Path $key) {
        Remove-Item $key -Recurse -Force -ErrorAction SilentlyContinue
        Write-Host "  Deleted: $key"
    }
}

Write-Host "`n=== Step 9: Clean Digilent env vars ===" -ForegroundColor Cyan
$digEnv = [System.Environment]::GetEnvironmentVariable("DigilentPath","Machine")
if ($digEnv) {
    Write-Host "  Removing DigilentPath env var"
    [System.Environment]::SetEnvironmentVariable("DigilentPath",$null,"Machine")
}
$digEnv2 = [System.Environment]::GetEnvironmentVariable("DigilentPath","User")
if ($digEnv2) {
    Write-Host "  Removing DigilentPath user env var"
    [System.Environment]::SetEnvironmentVariable("DigilentPath",$null,"User")
}

Write-Host "`n=== Step 10: Scan for hardware changes ===" -ForegroundColor Cyan
pnputil /scan-devices 2>&1 | ForEach-Object { Write-Host "  $_" }

Write-Host "`n=== Step 11: Final verification ===" -ForegroundColor Cyan
Write-Host ""
Write-Host "--- Digilent directories ---" -ForegroundColor Yellow
$found = $false
foreach ($dir in @("C:\Program Files\Digilent","C:\Program Files (x86)\Digilent","C:\Program Files\Common Files\Digilent","C:\Program Files (x86)\Common Files\Digilent","C:\ProgramData\Digilent")) {
    if (Test-Path $dir) {
        Write-Host "  STILL EXISTS: $dir" -ForegroundColor Red
        $found = $true
    }
}
if (-not $found) { Write-Host "  All clean" -ForegroundColor Green }

Write-Host ""
Write-Host "--- Digilent DLLs in System32/SysWOW64 ---" -ForegroundColor Yellow
$remainingDlls = Get-ChildItem "C:\Windows\System32","C:\Windows\SysWOW64" -ErrorAction SilentlyContinue | Where-Object {
    $_.Name -match "^(dmgr|dpcomm|djtg|dabs|dspi|dpceif|ftd2xx)\.dll$"
}
if ($remainingDlls) {
    $remainingDlls | ForEach-Object { Write-Host "  STILL EXISTS: $($_.FullName)" -ForegroundColor Red }
} else {
    Write-Host "  All clean" -ForegroundColor Green
}

Write-Host ""
Write-Host "--- FTDI device instances ---" -ForegroundColor Yellow
$remainingDevs = Get-PnpDevice | Where-Object { $_.InstanceId -match "VID_0403" }
if ($remainingDevs) {
    $remainingDevs | Format-Table FriendlyName, Status, Class, InstanceId -AutoSize
} else {
    Write-Host "  No FTDI devices (board unplugged or fully removed)" -ForegroundColor Green
}

Write-Host ""
Write-Host "--- Digilent/FTDI driver packages ---" -ForegroundColor Yellow
$remainingDrivers = pnputil /enum-drivers | Select-String -Pattern "ftdibus|ftdiport|digiftdibus|digiftdiport|dmodusb|xusbdrvr|dabsusb" -Context 1,0
if ($remainingDrivers) {
    $remainingDrivers | ForEach-Object { Write-Host "  $_" -ForegroundColor Red }
} else {
    Write-Host "  All clean" -ForegroundColor Green
}

Write-Host ""
Write-Host "--- Digilent registry ---" -ForegroundColor Yellow
$regFound = $false
foreach ($key in @("HKLM:\SOFTWARE\Digilent","HKLM:\SOFTWARE\WOW6432Node\Digilent","HKCU:\SOFTWARE\Digilent")) {
    if (Test-Path $key) {
        Write-Host "  STILL EXISTS: $key" -ForegroundColor Red
        $regFound = $true
    }
}
if (-not $regFound) { Write-Host "  All clean" -ForegroundColor Green }

Write-Host "`n=== DONE - All Digilent/FTDI traces removed ===" -ForegroundColor Green
Write-Host @"
NEXT STEPS:
1. Unplug Basys3 USB cable
2. Reboot Windows (recommended for clean state)
3. Download Adept Runtime 2.30.4 from Digilent website
   - https://digilent.com/reference/software/adept/start
   - Download 'Runtime - X64' for Windows
4. Run Adept installer AS ADMINISTRATOR
5. After install, plug Basys3 USB cable
6. Wait for Windows to install drivers
7. Run: & 'g:\GitHub\26-Arch\vivado\verify_adept.ps1'
"@
Write-Host "`nPress Enter to close..." -ForegroundColor Cyan
Read-Host
