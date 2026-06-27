# Look at USB composite interface enumeration
Write-Host "=== 1. USB Composite Device instance and its interface children ===" -ForegroundColor Cyan
$compositeInst = 'USB\VID_0403&PID_6010\210183A8A984'
$composite = Get-PnpDevice -PresentOnly | Where-Object { $_.InstanceId -eq $compositeInst }
if ($composite) {
    Write-Host ("Composite: " + $composite.FriendlyName + " Service=" + $composite.Service)
    # Children of composite (interface 0 and 1)
    Get-PnpDevice -PresentOnly | Where-Object { $_.Parent -eq $compositeInst } | ForEach-Object {
        Write-Host ("  IFace: " + $_.FriendlyName + " Class=" + $_.Class + " Service=" + $_.Service)
        Write-Host ("    " + $_.InstanceId)
        # And their children (should be FTDIBUS\COMPORT if any)
        $subChildren = Get-PnpDevice -PresentOnly | Where-Object { $_.Parent -eq $_.InstanceId }
        if ($subChildren) {
            $subChildren | ForEach-Object {
                Write-Host ("    SubChild: " + $_.FriendlyName + " Class=" + $_.Class + " Service=" + $_.Service)
                Write-Host ("      " + $_.InstanceId)
            }
        } else {
            Write-Host "    (no sub-children)"
        }
    }
}

Write-Host ""
Write-Host "=== 2. Use devcon-like listing via CIM ===" -ForegroundColor Cyan
Get-CimInstance Win32_PnPEntity | Where-Object { $_.DeviceID -match 'VID_0403&PID_6010' } | Sort-Object DeviceID | ForEach-Object {
    Write-Host ("Name    : " + $_.Name)
    Write-Host ("DeviceID: " + $_.DeviceID)
    Write-Host ("Status  : " + $_.Status)
    Write-Host ("Class   : " + $_.ClassGuid)
    Write-Host ("Parent  : " + $_.Parent)
    Write-Host ""
}
