# Check USB composite device enumeration for Basys3
Write-Host "=== USB Composite Device children of Basys3 ===" -ForegroundColor Cyan
$composite = Get-PnpDevice -PresentOnly | Where-Object { $_.InstanceId -eq 'USB\VID_0403&PID_6010\210183A8A984' }
if ($composite) {
    Write-Host ("Composite: " + $composite.FriendlyName + " Status=" + $composite.Status)
    Write-Host "Children (interfaces):"
    $children = Get-PnpDevice -PresentOnly | Where-Object { $_.Parent -eq $composite.InstanceId }
    $children | ForEach-Object {
        $d = $_
        $p = $d | Get-PnpDeviceProperty -KeyName 'DEVPKEY_Device_DriverInfPath','DEVPKEY_Device_DriverDesc','DEVPKEY_Device_Address'
        Write-Host ("  - " + $d.FriendlyName + " Status=" + $d.Status + " Class=" + $d.Class)
        Write-Host ("    " + $d.InstanceId)
        Write-Host ("    InfPath=" + ($p | Where-Object KeyName -eq 'DEVPKEY_Device_DriverInfPath').Data)
        Write-Host ("    Address=" + ($p | Where-Object KeyName -eq 'DEVPKEY_Device_Address').Data)
    }
} else {
    Write-Host "Composite not found"
}

Write-Host ""
Write-Host "=== USB device tree under parent hub ===" -ForegroundColor Cyan
$comp2 = Get-PnpDevice -PresentOnly | Where-Object { $_.InstanceId -eq 'USB\VID_0403&PID_6010\210183A8A984' }
if ($comp2) {
    $parentHub = $comp2.Parent
    Write-Host ("Parent hub: " + $parentHub)
    Get-PnpDevice -PresentOnly | Where-Object { $_.Parent -eq $parentHub } | Format-List FriendlyName, Status, Class, InstanceId
}

Write-Host ""
Write-Host "=== Registry of USB Composite device ===" -ForegroundColor Cyan
$reg = "HKLM:\SYSTEM\CurrentControlSet\Enum\USB\VID_0403&PID_6010\210183A8A984"
if (Test-Path $reg) {
    $props = Get-ItemProperty $reg
    Write-Host ("Service: " + $props.Service)
    Write-Host ("Class: " + $props.Class)
    Write-Host ("ConfigFlags: 0x" + ("{0:X8}" -f $props.ConfigFlags))
    Write-Host ("HardwareId: " + ($props.HardwareId -join ', '))
    if ($props.RemoveableOrUnknown) { Write-Host ("RemoveableOrUnknown: " + $props.RemoveableOrUnknown) }
    $child = "$reg\Child0000"
    if (Test-Path $child) { Write-Host "Child0000 path exists" }
    # Try to enumerate child subkeys
    Get-ChildItem $reg | ForEach-Object {
        Write-Host ("Subkey: " + $_.Name)
        if (Test-Path $_.PSPath) {
            $subProps = Get-ItemProperty $_.PSPath
            if ($subProps.HardwareId) { Write-Host ("  HardwareId: " + ($subProps.HardwareId -join ',')) }
            if ($subProps.Service) { Write-Host ("  Service: " + $subProps.Service) }
            if ($subProps.Class) { Write-Host ("  Class: " + $subProps.Class) }
            if ($subProps.ConfigFlags -ne $null) { Write-Host ("  ConfigFlags: 0x" + ("{0:X8}" -f $subProps.ConfigFlags)) }
        }
    }
}
