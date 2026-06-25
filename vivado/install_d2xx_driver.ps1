# Run as Administrator
#requires -RunAsAdministrator
$ErrorActionPreference = "Continue"

Write-Host "=== Step 1: Install ftdibus.inf (D2XX mode, NOT VCP) ===" -ForegroundColor Cyan
# Use the newer version from UsbDriver2
$infPath = "C:\Program Files (x86)\Digilent\Runtime\UsbDriver2\ftdibus.inf"
if (-not (Test-Path $infPath)) {
    $infPath = "C:\Program Files (x86)\Digilent\Runtime\UsbDriver\ftdibus.inf"
}
Write-Host "Installing: $infPath"
pnputil /add-driver $infPath /install 2>&1 | ForEach-Object { Write-Host $_ }

Write-Host "`n=== Step 2: Scan for hardware changes ===" -ForegroundColor Cyan
pnputil /scan-devices 2>&1 | ForEach-Object { Write-Host $_ }

Start-Sleep -Seconds 2

Write-Host "`n=== Step 3: Check device state ===" -ForegroundColor Cyan
Get-PnpDevice | Where-Object { $_.InstanceId -match "VID_0403&PID_6010" } | Format-Table -AutoSize FriendlyName, Status, Class, InstanceId

Write-Host "`n=== Step 4: Test FTD2XX device detection ===" -ForegroundColor Cyan
try {
    $sig = @"
[DllImport("ftd2xx.dll")]
public static extern uint FT_CreateDeviceInfoList(out uint numdevs);
"@
    Add-Type -MemberDefinition $sig -Name "FTD2XX2" -Namespace "Win32" -ErrorAction Stop
    $numdevs = 0
    $ret = [Win32.FTD2XX2]::FT_CreateDeviceInfoList([ref]$numdevs)
    Write-Host "FT_CreateDeviceInfoList returned: $ret"
    Write-Host "Number of FTDI devices detected by D2XX: $numdevs" -ForegroundColor $(if($numdevs -gt 0){"Green"}else{"Red"})
} catch {
    Write-Host "FTD2XX test failed: $_" -ForegroundColor Red
}

Write-Host "`n=== Step 5: Driver packages ===" -ForegroundColor Cyan
pnputil /enum-drivers | Select-String -Pattern "ftdibus|ftdiport|digilent" -Context 1,0

Write-Host "`n=== DONE ===" -ForegroundColor Green
Write-Host "If D2XX detected devices > 0, Vivado should now find the JTAG target."
Write-Host "Press Enter to close..." -ForegroundColor Cyan
Read-Host
