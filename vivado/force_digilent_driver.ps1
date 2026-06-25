# Run as Administrator
#requires -RunAsAdministrator
$ErrorActionPreference = "Continue"

Write-Host "=== Step 1: Stop processes ===" -ForegroundColor Cyan
Get-Process hw_server,cs_server,vivado -ErrorAction SilentlyContinue | Stop-Process -Force
Start-Sleep -Seconds 2

Write-Host "`n=== Step 2: List Digilent driver packages ===" -ForegroundColor Cyan
pnputil /enum-drivers | Select-String -Pattern "digiftdibus|digiftdiport|ftdibus|ftdiport" -Context 1,0 | ForEach-Object {
    Write-Host "  $_"
}

Write-Host "`n=== Step 3: Force remove FTDI driver packages (keep Digilent) ===" -ForegroundColor Cyan
# Remove FTDI official drivers (oem46.inf is ftdibus.inf, oem69.inf is ftdiport.inf)
$driverList = pnputil /enum-drivers
$oemList = @()
$oemList += $driverList | Select-String -Pattern "Original Name:\s*ftdibus\.inf|Original Name:\s*ftdiport\.inf" -Context 1,0
foreach ($match in $oemList) {
    # Get the published name from the pre-context (line above)
    $prev = $match.Context.PreContext[0]
    if ($prev -match "Published Name:\s*(oem\d+\.inf)") {
        $inf = $matches[1]
        Write-Host "  Deleting FTDI driver: $inf"
        pnputil /delete-driver $inf /uninstall /force 2>&1 | ForEach-Object { Write-Host "    $_" }
    }
}

Write-Host "`n=== Step 4: Re-list driver packages ===" -ForegroundColor Cyan
pnputil /enum-drivers | Select-String -Pattern "digiftdibus|digiftdiport|ftdibus|ftdiport" -Context 1,0 | ForEach-Object {
    Write-Host "  $_"
}

Write-Host "`n=== Step 5: Remove all FTDI device instances ===" -ForegroundColor Cyan
$devs = Get-PnpDevice | Where-Object { $_.InstanceId -match "VID_0403" } | Sort-Object InstanceId -Descending
foreach ($d in $devs) {
    Write-Host "  Removing: $($d.FriendlyName) [$($d.InstanceId)]"
    & pnputil /remove-device "$($d.InstanceId)" 2>&1 | Out-Null
}

Start-Sleep -Seconds 2

Write-Host "`n=== Step 6: Scan for hardware changes ===" -ForegroundColor Cyan
pnputil /scan-devices 2>&1 | ForEach-Object { Write-Host "  $_" }
Start-Sleep -Seconds 3

Write-Host "`n=== Step 7: Device state after re-scan ===" -ForegroundColor Cyan
Get-PnpDevice | Where-Object { $_.InstanceId -match "VID_0403" } | Format-Table FriendlyName, Status, Class, InstanceId -AutoSize

Write-Host "`n=== Step 8: Check what driver is now bound ===" -ForegroundColor Cyan
$devs = Get-PnpDevice | Where-Object { $_.InstanceId -match "VID_0403&PID_6010&MI_0[01]" }
foreach ($d in $devs) {
    Write-Host "`n--- $($d.InstanceId) ---"
    Write-Host "  FriendlyName: $($d.FriendlyName)"
    $props = Get-PnpDeviceProperty -InputObject $d -ErrorAction SilentlyContinue
    $props | Where-Object { $_.KeyName -match "DriverInfPath|DriverProvider|DriverDesc|BusReportedDeviceDesc" } | ForEach-Object {
        Write-Host "  $($_.KeyName): $($_.Data)"
    }
}

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
