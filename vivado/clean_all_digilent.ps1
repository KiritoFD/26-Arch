# Run as Administrator
#requires -RunAsAdministrator
$ErrorActionPreference = "Continue"

Write-Host "=== Step 1: Stop all related processes ===" -ForegroundColor Cyan
Get-Process hw_server,cs_server,vivado,djtgcfg,dmgr,digilent* -ErrorAction SilentlyContinue | ForEach-Object {
    Write-Host "  Stopping: $($_.ProcessName) (PID $($_.Id))"
    Stop-Process -Id $_.Id -Force -ErrorAction SilentlyContinue
}
Start-Sleep -Seconds 2

Write-Host "`n=== Step 2: Uninstall FTDI device instances (VID_0403) ===" -ForegroundColor Cyan
# Use pnputil to remove devices
$usbDevices = Get-PnpDevice | Where-Object { $_.InstanceId -match "VID_0403" } | Sort-Object InstanceId -Descending
foreach ($dev in $usbDevices) {
    Write-Host "  Removing: $($dev.FriendlyName) [$($dev.InstanceId)]"
    try {
        $result = & pnputil /remove-device "$($dev.InstanceId)" 2>&1
        $result | ForEach-Object { Write-Host "    $_" }
    } catch {
        Write-Host "    Failed: $_"
    }
}

Write-Host "`n=== Step 3: Delete ALL FTDI/Digilent driver packages ===" -ForegroundColor Cyan
$driverList = pnputil /enum-drivers
$oemList = @()
$oemList += $driverList | Select-String -Pattern "ftdibus\.inf|ftdiport\.inf|digiftdibus\.inf|digiftdiport\.inf|dmodusb\.inf|xusbdrvr\.inf" -Context 1,0
foreach ($match in $oemList) {
    if ($match.Context.PreContext -match "Published Name:\s*(oem\d+\.inf)") {
        $inf = $matches[1]
        Write-Host "  Deleting driver: $inf"
        pnputil /delete-driver $inf /uninstall /force 2>&1 | ForEach-Object { Write-Host "    $_" }
    }
}

Write-Host "`n=== Step 4: Delete Digilent DLLs from System32 ===" -ForegroundColor Cyan
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
        try {
            Remove-Item $dll -Force -ErrorAction Stop
            Write-Host "  Deleted: $dll"
        } catch {
            Write-Host "  Failed (locked?): $dll - $_"
            # Try to take ownership
            try {
                takeown /F $dll /A 2>&1 | Out-Null
                icacls $dll /grant administrators:F 2>&1 | Out-Null
                Remove-Item $dll -Force -ErrorAction Stop
                Write-Host "  Deleted after takeown: $dll"
            } catch {
                Write-Host "  STILL FAILED: $dll"
            }
        }
    }
}

Write-Host "`n=== Step 5: Delete Digilent directories ===" -ForegroundColor Cyan
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
            Write-Host "  Deleted: $dir"
        } catch {
            Write-Host "  Failed: $dir - $_"
        }
    } else {
        Write-Host "  Not present: $dir"
    }
}

Write-Host "`n=== Step 6: Clean Digilent registry ===" -ForegroundColor Cyan
$regKeys = @(
    "HKLM:\SOFTWARE\Digilent",
    "HKLM:\SOFTWARE\WOW6432Node\Digilent",
    "HKCU:\SOFTWARE\Digilent"
)
foreach ($key in $regKeys) {
    if (Test-Path $key) {
        try {
            Remove-Item $key -Recurse -Force -ErrorAction Stop
            Write-Host "  Deleted registry: $key"
        } catch {
            Write-Host "  Failed: $key - $_"
        }
    }
}

Write-Host "`n=== Step 7: Clean Digilent services ===" -ForegroundColor Cyan
$services = @("dmodusb","windrvr6","DigilentAdept","dmgr","djtg","dabs")
foreach ($svc in $services) {
    $s = Get-Service -Name $svc -ErrorAction SilentlyContinue
    if ($s) {
        Write-Host "  Removing service: $svc"
        sc.exe delete $svc 2>&1 | ForEach-Object { Write-Host "    $_" }
    }
}

Write-Host "`n=== Step 8: Scan for hardware changes ===" -ForegroundColor Cyan
pnputil /scan-devices 2>&1 | ForEach-Object { Write-Host $_ }

Write-Host "`n=== Step 9: Verify cleanup ===" -ForegroundColor Cyan
Write-Host "Remaining Digilent folders:"
$remaining = @()
foreach ($dir in @("C:\Program Files\Digilent","C:\Program Files (x86)\Digilent","C:\Program Files (x86)\Common Files\Digilent","C:\ProgramData\Digilent")) {
    if (Test-Path $dir) {
        Write-Host "  STILL EXISTS: $dir" -ForegroundColor Red
        $remaining += $dir
    }
}
if ($remaining.Count -eq 0) {
    Write-Host "  All Digilent folders removed!" -ForegroundColor Green
}

Write-Host "`nRemaining Digilent DLLs in System32:"
$remainingDlls = Get-ChildItem "C:\Windows\System32","C:\Windows\SysWOW64" -ErrorAction SilentlyContinue | Where-Object { 
    $_.Name -match "^(dmgr|dpcomm|djtg|dabs|dspi|dpceif)\.dll$" 
}
if ($remainingDlls) {
    $remainingDlls | ForEach-Object { Write-Host "  STILL EXISTS: $($_.FullName)" -ForegroundColor Red }
} else {
    Write-Host "  All Digilent DLLs removed!" -ForegroundColor Green
}

Write-Host "`nRemaining FTDI devices:"
$remainingDevs = Get-PnpDevice | Where-Object { $_.InstanceId -match "VID_0403" }
if ($remainingDevs) {
    $remainingDevs | Format-Table FriendlyName, Status, InstanceId -AutoSize
} else {
    Write-Host "  No FTDI devices (board unplugged or fully removed)" -ForegroundColor Green
}

Write-Host "`n=== DONE ===" -ForegroundColor Green
Write-Host @"
NEXT STEPS:
1. UNPLUG Basys3 USB cable
2. Reboot Windows (recommended for clean state)
3. Install Adept Runtime 2.30.4 (run as Administrator)
4. After install completes, plug Basys3 USB cable
5. Wait for Windows to install drivers automatically
6. Open Device Manager - should see "Digilent USB Device" entries
7. Run verify_adept.ps1 to test Vivado hw_server
"@
Write-Host "`nPress Enter to close..." -ForegroundColor Cyan
Read-Host
