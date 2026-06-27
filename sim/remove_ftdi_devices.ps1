# Remove all FTDI device instances for the current board and force re-enumeration
# This clears stale driver state that prevents D2XX from reading the real SN/Desc

Write-Host "=== Removing all FTDI/FTDIBUS device instances ===" -ForegroundColor Cyan

# Get all FTDI related device instances
$devs = Get-PnpDevice | Where-Object {
    $_.InstanceId -match 'VID_0403&PID_6010|FTDIBUS.*PID_6010'
}

foreach ($d in $devs) {
    Write-Host ("Removing: " + $d.FriendlyName + " [" + $d.InstanceId + "]")
    try {
        $d | Remove-PnpDevice -Confirm:$false -ErrorAction Stop
        Write-Host "  OK" -ForegroundColor Green
    } catch {
        Write-Host ("  FAILED: " + $_.Exception.Message) -ForegroundColor Yellow
        # Try pnputil as fallback
        Write-Host "  Trying pnputil..."
        $result = pnputil /remove-device $d.InstanceId 2>&1
        Write-Host ("  pnputil: " + $result)
    }
}

Write-Host ""
Write-Host "=== Scanning for device changes ===" -ForegroundColor Cyan
pnputil /scan-devices

Write-Host ""
Write-Host "=== Devices after re-enumeration ===" -ForegroundColor Cyan
Start-Sleep -Seconds 3
Get-PnpDevice -PresentOnly | Where-Object { $_.InstanceId -match 'VID_0403|FTDIBUS' } | Format-List Status, Class, FriendlyName, InstanceId

Write-Host ""
Write-Host "=== COM ports ===" -ForegroundColor Cyan
[System.IO.Ports.SerialPort]::GetPortNames()
