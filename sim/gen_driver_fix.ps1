# Find the FTDI device with VID_1443 and switch its driver to ftdibus
# This allows D2XX to access the device and rewrite the EEPROM

Write-Host "=== Current FTDI devices with VID_1443 ===" -ForegroundColor Cyan
$devices = Get-WmiObject Win32_PnPEntity | Where-Object { $_.DeviceID -match 'VID_1443&PID_6010' }
foreach ($d in $devices) {
    Write-Host "Device: $($d.Name)"
    Write-Host "  DeviceID: $($d.DeviceID)"
    Write-Host "  Status: $($d.Status)"
    Write-Host "  ConfigManagerErrorCode: $($d.ConfigManagerErrorCode)"
    Write-Host ""
}

Write-Host "=== Available FTDI bus driver INFs ===" -ForegroundColor Cyan
# List FTDI ftdibus.inf packages
$result = & pnputil /enum-drivers
$entries = $result -split "`n`n"
foreach ($entry in $entries) {
    if ($entry -match 'ftdibus' -and $entry -match 'FTDI') {
        Write-Host $entry
        Write-Host "---"
    }
}

Write-Host ""
Write-Host "=== Steps to switch driver ===" -ForegroundColor Yellow
Write-Host "1. Find the device instance ID above (USB\VID_1443&PID_6010&MI_00\...)"
Write-Host "2. Use pnputil to bind ftdibus.inf to it"
Write-Host ""
Write-Host "Run this command (admin):"
Write-Host '  pnputil /add-driver "C:\Windows\INF\oem172.inf" /install'
Write-Host ""
Write-Host "Or use Device Manager:"
Write-Host "  - Right-click the VID_1443 device -> Update driver"
Write-Host "  - Browse -> Let me pick -> USB Serial Converter (FTDI)"

Write-Host ""
Write-Host "=== Alternative: Find device instance IDs ===" -ForegroundColor Cyan
# Get the full instance IDs
Get-WmiObject Win32_PnPEntity | Where-Object { $_.DeviceID -match 'VID_1443&PID_6010' } | ForEach-Object {
    Write-Host "Instance ID: $($_.DeviceID)"
}
