# Diagnose FTDI driver binding for Basys3 (FT2232H) channels
Write-Host "=== A/B Channel Driver Binding ===" -ForegroundColor Cyan
$devs = Get-PnpDevice -PresentOnly | Where-Object { $_.InstanceId -match 'VID_0403&PID_6010' }
foreach ($d in $devs) {
    $p = $d | Get-PnpDeviceProperty -KeyName 'DEVPKEY_Device_DriverInfPath','DEVPKEY_Device_DriverDesc','DEVPKEY_Device_Manufacturer','DEVPKEY_Device_HardwareIds'
    $inf = ($p | Where-Object KeyName -eq 'DEVPKEY_Device_DriverInfPath').Data
    $desc = ($p | Where-Object KeyName -eq 'DEVPKEY_Device_DriverDesc').Data
    $mfr = ($p | Where-Object KeyName -eq 'DEVPKEY_Device_Manufacturer').Data
    $hw = ($p | Where-Object KeyName -eq 'DEVPKEY_Device_HardwareIds').Data
    Write-Host ""
    Write-Host ("Name       : " + $d.FriendlyName)
    Write-Host ("InstanceId : " + $d.InstanceId)
    Write-Host ("Status     : " + $d.Status)
    Write-Host ("Class      : " + $d.Class)
    Write-Host ("InfPath    : " + $inf)
    Write-Host ("DriverDesc : " + $desc)
    Write-Host ("Manufacturer: " + $mfr)
    Write-Host ("HardwareIds: " + ($hw -join ', '))
}

Write-Host ""
Write-Host "=== Currently installed FTDI/Digilent INFs ===" -ForegroundColor Cyan
pnputil /enum-drivers | Select-String -Pattern 'Original Name:\s*(ftdi|digift)' -Context 2,2

Write-Host ""
Write-Host "=== Ports class devices (COM ports) ===" -ForegroundColor Cyan
Get-PnpDevice -PresentOnly | Where-Object { $_.Class -eq 'Ports' -and $_.InstanceId -notmatch 'BTHENUM' } | Format-List FriendlyName, InstanceId, Status
