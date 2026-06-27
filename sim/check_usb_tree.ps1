# Check all FTDI-related USB devices in Windows
Write-Host "=== All USB PnP devices with FTDI VID (0x0403) ===" -ForegroundColor Cyan
Get-WmiObject Win32_PnPEntity | Where-Object { $_.DeviceID -match 'VID_0403' } | Select-Object Name, DeviceID, Status, ConfigManagerErrorCode | Format-List

Write-Host ""
Write-Host "=== USB Composite devices ===" -ForegroundColor Cyan
Get-WmiObject Win32_PnPEntity | Where-Object { $_.Name -match 'Composite' } | Select-Object Name, DeviceID, Status | Format-List

Write-Host ""
Write-Host "=== FTDI driver nodes ===" -ForegroundColor Cyan
Get-WmiObject Win32_PnPSignedDriver | Where-Object { $_.DeviceName -match 'FTDI|FT2232|Dual RS232|Digilent' } | Select-Object DeviceName, DeviceID, DriverVersion, DriverProviderName, InfName | Format-List

Write-Host ""
Write-Host "=== Devices with problems (code != 0) ===" -ForegroundColor Yellow
Get-WmiObject Win32_PnPEntity | Where-Object { $_.ConfigManagerErrorCode -ne 0 -and $_.DeviceID -match 'VID_0403|FTDI|Digilent' } | Select-Object Name, DeviceID, ConfigManagerErrorCode | Format-List
