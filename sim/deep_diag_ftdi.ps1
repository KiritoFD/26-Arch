# Deep diagnosis of FTDI channel A child device tree
Write-Host "=== 1. All FTDI/Basys3 related devices (including phantom) ===" -ForegroundColor Cyan
Get-PnpDevice | Where-Object { $_.InstanceId -match 'VID_0403&PID_6010|FTDIBUS.*PID_6010' } | Sort-Object Status, InstanceId | Format-List Status, Class, FriendlyName, InstanceId

Write-Host ""
Write-Host "=== 2. Child device tree of Channel A (USB\VID_0403&PID_6010&MI_00) ===" -ForegroundColor Cyan
$chanA = Get-PnpDevice -PresentOnly | Where-Object { $_.InstanceId -match 'PID_6010&MI_00\\8&1CFED31F' }
if ($chanA) {
    Write-Host ("Parent: " + $chanA.FriendlyName + " [" + $chanA.InstanceId + "]")
    $children = Get-PnpDevice | Where-Object { $_.Parent -eq $chanA.InstanceId }
    if ($children) {
        $children | Format-List Status, Class, FriendlyName, InstanceId
    } else {
        Write-Host "  -> NO child devices! ftdibus did not create COMPORT sub-device" -ForegroundColor Red
    }
} else {
    Write-Host "  Channel A not found" -ForegroundColor Red
}

Write-Host ""
Write-Host "=== 3. All FTDIBUS\COMPORT entries ===" -ForegroundColor Cyan
Get-PnpDevice | Where-Object { $_.InstanceId -match 'FTDIBUS\\COMPORT' } | Format-List Status, Class, FriendlyName, InstanceId

Write-Host ""
Write-Host "=== 4. Driver service & registry for Channel A ===" -ForegroundColor Cyan
$reg = "HKLM:\SYSTEM\CurrentControlSet\Enum\USB\VID_0403&PID_6010&MI_00\8&1CFED31F&0&0000"
if (Test-Path $reg) {
    Get-ItemProperty $reg | Select-Object DeviceDesc, FriendlyName, Class, Service, ConfigFlags, HardwareId | Format-List
    $paramsReg = "$reg\Device Parameters"
    if (Test-Path $paramsReg) {
        Write-Host "Device Parameters:"
        Get-ItemProperty $paramsReg | Format-List
    }
    $logConf = "$reg\LogConf"
    if (Test-Path $logConf) {
        Write-Host "LogConf exists"
    }
} else {
    Write-Host "Registry path not found"
}

Write-Host ""
Write-Host "=== 5. ftdibus service state ===" -ForegroundColor Cyan
Get-Service ftdibus, ftser2k, FTDIBUS, FTSER2K -ErrorAction SilentlyContinue | Format-List Name, Status, StartType

Write-Host ""
Write-Host "=== 6. Driver files for Channel A (ftdibus.sys version) ===" -ForegroundColor Cyan
Get-Item "C:\Windows\System32\Drivers\ftdibus.sys","C:\Windows\System32\Drivers\ftser2k.sys","C:\Windows\System32\Drivers\ftcser2k.sys" -ErrorAction SilentlyContinue | Select-Object Name, @{N='Version';E={$_.VersionInfo.FileVersion}}, Length, LastWriteTime | Format-List
