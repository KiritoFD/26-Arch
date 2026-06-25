# Run as Administrator: right-click this file -> Run with PowerShell (as Admin)
# Or: Start Menu -> PowerShell -> right-click -> Run as administrator -> & 'g:\GitHub\26-Arch\vivado\uninstall_ftdi_drivers.ps1'

#requires -RunAsAdministrator

$ErrorActionPreference = "Continue"

Write-Host "=== Step 1: Removing all FTDI device instances (VID_0403) ===" -ForegroundColor Cyan
$devs = Get-PnpDevice | Where-Object { $_.InstanceId -match "VID_0403" }
foreach ($d in $devs) {
    Write-Host "Removing: $($d.FriendlyName) [$($d.InstanceId)]"
    try {
        $d | Uninstall-PnpDevice -Confirm:$false -ErrorAction Stop
        Write-Host "  OK" -ForegroundColor Green
    } catch {
        Write-Host "  Failed: $_" -ForegroundColor Yellow
    }
}

Write-Host "`n=== Step 2: Deleting standard FTDI driver packages (keep Digilent) ===" -ForegroundColor Cyan
# Standard FTDI drivers to remove (keep digiftdibus.inf / digiftdiport.inf / xusbdrvr.inf)
$toDelete = @(
    "oem121.inf", "oem171.inf", "oem40.inf",   # ftdibus.inf
    "oem165.inf", "oem172.inf", "oem69.inf"    # ftdiport.inf
)
foreach ($inf in $toDelete) {
    Write-Host "Deleting: $inf"
    pnputil /delete-driver $inf /uninstall /force 2>&1 | ForEach-Object { Write-Host "  $_" }
}

Write-Host "`n=== Step 3: Scanning for hardware changes ===" -ForegroundColor Cyan
pnputil /scan-devices 2>&1 | ForEach-Object { Write-Host $_ }

Write-Host "`n=== Final FTDI device state ===" -ForegroundColor Cyan
Get-PnpDevice | Where-Object { $_.InstanceId -match "VID_0403" } | Format-Table -AutoSize FriendlyName, Status, InstanceId

Write-Host "=== Final driver packages ===" -ForegroundColor Cyan
pnputil /enum-drivers | Select-String -Pattern "ftdibus|ftdiport|digilent|xusbdrvr" -Context 1,0

Write-Host "`n=== DONE ===" -ForegroundColor Green
Write-Host "Now unplug Basys3 USB cable, wait 5 seconds, and replug."
Write-Host "Windows should re-enumerate using Digilent drivers (digiftdibus.inf / digiftdiport.inf)."
Write-Host "Then open Vivado Hardware Manager to verify JTAG target detection."
Write-Host "`nPress Enter to close..." -ForegroundColor Cyan
Read-Host
