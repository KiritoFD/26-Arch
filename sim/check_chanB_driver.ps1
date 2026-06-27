# Check Channel B (MI_01) driver binding - is it Digilent or FTDI?
Write-Host "=== Channel B (MI_01) driver details ===" -ForegroundColor Cyan
$devs = Get-PnpDevice -PresentOnly | Where-Object { $_.InstanceId -match 'PID_6010&MI_01' }
foreach ($d in $devs) {
    $p = $d | Get-PnpDeviceProperty -KeyName 'DEVPKEY_Device_DriverInfPath','DEVPKEY_Device_DriverDesc','DEVPKEY_Device_Manufacturer'
    Write-Host ("FriendlyName: " + $d.FriendlyName)
    Write-Host ("InstanceId: " + $d.InstanceId)
    Write-Host ("Status: " + $d.Status)
    Write-Host ("Class: " + $d.Class)
    Write-Host ("InfPath: " + ($p | Where-Object KeyName -eq 'DEVPKEY_Device_DriverInfPath').Data)
    Write-Host ("DriverDesc: " + ($p | Where-Object KeyName -eq 'DEVPKEY_Device_DriverDesc').Data)
    Write-Host ("Manufacturer: " + ($p | Where-Object KeyName -eq 'DEVPKEY_Device_Manufacturer').Data)
}

Write-Host ""
Write-Host "=== Digilent Adept driver installed? ===" -ForegroundColor Cyan
pnputil /enum-drivers | Select-String -Pattern 'digilent|adept|djtgcfg' -Context 2,2

Write-Host ""
Write-Host "=== All FTDI/Digilent related INFs ===" -ForegroundColor Cyan
pnputil /enum-drivers | Select-String -Pattern 'ftdi|digilent' -Context 2,2
