# Deep check Digilent Adept runtime installation
Write-Host "=== Digilent Registry ===" -ForegroundColor Cyan
Get-ChildItem "HKLM:\SOFTWARE\Digilent" -Recurse -ErrorAction SilentlyContinue | ForEach-Object {
    Write-Host $_.Name
    $props = Get-ItemProperty $_.PSPath
    $props.PSObject.Properties | Where-Object { $_.Name -notmatch 'PS' } | ForEach-Object {
        Write-Host ("  " + $_.Name + " = " + $_.Value)
    }
}

Write-Host ""
Write-Host "=== Digilent Adept files ===" -ForegroundColor Cyan
$adeptDirs = @(
    "C:\Program Files\Digilent",
    "C:\Program Files (x86)\Digilent",
    "C:\Windows\System32\digilent",
    "C:\Windows\SysWOW64\digilent"
)
foreach ($d in $adeptDirs) {
    if (Test-Path $d) {
        Write-Host "Found: $d"
        Get-ChildItem $d -Recurse -ErrorAction SilentlyContinue | Select-Object FullName, Length | Format-Table -AutoSize
    }
}

Write-Host ""
Write-Host "=== Digilent DLLs in System32 ===" -ForegroundColor Cyan
Get-ChildItem "C:\Windows\System32","C:\Windows\SysWOW64" -Filter "digilent*" -ErrorAction SilentlyContinue | Select-Object FullName, Length
Get-ChildItem "C:\Windows\System32","C:\Windows\SysWOW64" -Filter "dpcutil*" -ErrorAction SilentlyContinue | Select-Object FullName, Length

Write-Host ""
Write-Host "=== Try running install_digilent.exe (dry run) ===" -ForegroundColor Cyan
$installer = "C:\Xilinx\Vivado\2019.2\data\xicom\cable_drivers\nt64\digilent\install_digilent.exe"
if (Test-Path $installer) {
    Write-Host "Installer found: $installer"
    Write-Host "Run this manually to install Digilent cable drivers"
}

Write-Host ""
Write-Host "=== Run hw_server longer and check cable detection ===" -ForegroundColor Cyan
$hw_server = "C:\Xilinx\Vivado\2019.2\bin\unwrapped\win64.o\hw_server.exe"
$proc = Start-Process -FilePath $hw_server -PassThru -WindowStyle Hidden -RedirectStandardOutput "hw_server2.log" -RedirectStandardError "hw_server2_err.log"
Start-Sleep -Seconds 5
if (-not $proc.HasExited) {
    Write-Host "hw_server running, PID=$($proc.Id)" -ForegroundColor Green
    # Try to connect via TCP and list targets
    Start-Sleep -Seconds 2
    Stop-Process -Id $proc.Id -Force
}
Write-Host "`nhw_server output:"
if (Test-Path "hw_server2.log") { Get-Content "hw_server2.log" }
if (Test-Path "hw_server2_err.log") { Get-Content "hw_server2_err.log" }
