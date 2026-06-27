# Verify all conditions for Vivado to recognize Basys3
Write-Host "=== Vivado Basys3 Recognition Check ===" -ForegroundColor Cyan

# 1. Check Channel A (MI_00) - should be VCP for COM port
Write-Host "`n--- Channel A (MI_00) ---" -ForegroundColor Yellow
$chanA = Get-PnpDevice -PresentOnly | Where-Object { $_.InstanceId -match 'PID_6010&MI_00' }
if ($chanA) {
    $p = $chanA | Get-PnpDeviceProperty -KeyName 'DEVPKEY_Device_DriverInfPath','DEVPKEY_Device_DriverDesc'
    Write-Host ("FriendlyName: " + $chanA.FriendlyName)
    Write-Host ("InstanceId: " + $chanA.InstanceId)
    Write-Host ("Status: " + $chanA.Status)
    Write-Host ("InfPath: " + ($p | Where-Object KeyName -eq 'DEVPKEY_Device_DriverInfPath').Data)
    Write-Host ("DriverDesc: " + ($p | Where-Object KeyName -eq 'DEVPKEY_Device_DriverDesc').Data)
}

# 2. Check Channel B (MI_01) - should be D2XX/ftdibus for Vivado JTAG
Write-Host "`n--- Channel B (MI_01) ---" -ForegroundColor Yellow
$chanB = Get-PnpDevice -PresentOnly | Where-Object { $_.InstanceId -match 'PID_6010&MI_01' }
if ($chanB) {
    $p = $chanB | Get-PnpDeviceProperty -KeyName 'DEVPKEY_Device_DriverInfPath','DEVPKEY_Device_DriverDesc'
    Write-Host ("FriendlyName: " + $chanB.FriendlyName)
    Write-Host ("InstanceId: " + $chanB.InstanceId)
    Write-Host ("Status: " + $chanB.Status)
    Write-Host ("InfPath: " + ($p | Where-Object KeyName -eq 'DEVPKEY_Device_DriverInfPath').Data)
    Write-Host ("DriverDesc: " + ($p | Where-Object KeyName -eq 'DEVPKEY_Device_DriverDesc').Data)
}

# 3. Check COM port
Write-Host "`n--- COM Ports ---" -ForegroundColor Yellow
Get-PnpDevice -PresentOnly | Where-Object { $_.Class -eq 'Ports' -and $_.InstanceId -match 'FTDIBUS.*PID_6010' } | Format-List FriendlyName, InstanceId, Status

# 4. Check USB Composite device instance (should be SN, not parent ID)
Write-Host "`n--- USB Composite Device ---" -ForegroundColor Yellow
$comp = Get-PnpDevice -PresentOnly | Where-Object { $_.InstanceId -match 'USB\\VID_0403&PID_6010\\' }
$comp | Format-List FriendlyName, InstanceId, Status

# 5. Summary
Write-Host "`n=== Summary ===" -ForegroundColor Cyan
$sn_correct = $comp.InstanceId -match '210183A8AC3D$'
$com_exists = (Get-PnpDevice -PresentOnly | Where-Object { $_.Class -eq 'Ports' -and $_.InstanceId -match 'PID_6010' }).Count -gt 0
Write-Host ("SN correct (210183A8AC3D): " + $sn_correct)
Write-Host ("COM port exists: " + $com_exists)
Write-Host ""
Write-Host "Now open Vivado and try: Open Target -> Auto Connect" -ForegroundColor Green
