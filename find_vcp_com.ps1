# Find COM ports (VCP-managed FTDI channels don't show in D2XX but show as COM)
Write-Host "=== All COM ports ==="
$coms = Get-CimInstance Win32_PnPEntity | Where-Object { $_.Name -match 'COM\d' -or $_.DeviceID -match 'FTDI' -or $_.DeviceID -match 'VID_0403' }
$coms | ForEach-Object {
    Write-Host ("Name: {0}" -f $_.Name)
    Write-Host ("  DeviceID: {0}" -f $_.DeviceID)
    Write-Host ("  Class: {0}" -f $_.PNPClass)
    Write-Host ("  Status: {0}" -f $_.Status)
    Write-Host ""
}

Write-Host "=== Registry: HKLM\SYSTEM\CurrentControlSet\Enum\FTDIBUS ==="
reg query "HKLM\SYSTEM\CurrentControlSet\Enum\FTDIBUS" 2>$null | Select-Object -First 20

Write-Host "=== FTDI VCP COM mapping ==="
$keys = Get-ChildItem "HKLM:\SYSTEM\CurrentControlSet\Enum\FTDIBUS" -ErrorAction SilentlyContinue
foreach ($k in $keys) {
    $sub = Get-ChildItem $k.PSPath -ErrorAction SilentlyContinue
    foreach ($s in $sub) {
        $props = Get-ItemProperty $s.PSPath -ErrorAction SilentlyContinue
        if ($props.DeviceDesc -match 'Serial' -or $props.DeviceDesc -match 'COM') {
            Write-Host ("  {0} -> {1}" -f $s.PSChildName, $props.DeviceDesc)
        }
    }
}
