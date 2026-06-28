Write-Host "=== Win32_SerialPort ==="
Get-CimInstance Win32_SerialPort | Select-Object Name, DeviceID, Description | Format-Table -AutoSize

Write-Host "=== PnPEntity (Ports class) ==="
Get-CimInstance Win32_PnPEntity | Where-Object { $_.PNPClass -eq 'Ports' } | Select-Object Name, DeviceID | Format-Table -AutoSize

Write-Host "=== FTDI-related ==="
Get-CimInstance Win32_PnPEntity | Where-Object { $_.Name -match 'FTDI|FT2232|Digilent|Basys|Serial' } | Select-Object Name, DeviceID, ConfigManagerErrorCode | Format-Table -AutoSize
