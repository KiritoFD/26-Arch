# Run hw_server with debug logging to see why it can't find the board
Write-Host "=== Starting hw_server with debug ===" -ForegroundColor Cyan

$hw_server = "C:\Xilinx\Vivado\2019.2\bin\unwrapped\win64.o\hw_server.exe"

# Start hw_server in background
$proc = Start-Process -FilePath $hw_server -ArgumentList "-d" -PassThru -WindowStyle Hidden -RedirectStandardOutput "hw_server_stdout.log" -RedirectStandardError "hw_server_stderr.log"

Write-Host "hw_server PID: $($proc.Id)"
Start-Sleep -Seconds 3

# Check if it's running
if (-not $proc.HasExited) {
    Write-Host "hw_server is running" -ForegroundColor Green
    Write-Host "Stopping hw_server..."
    Stop-Process -Id $proc.Id -Force
} else {
    Write-Host "hw_server exited with code: $($proc.ExitCode)" -ForegroundColor Red
}

Write-Host ""
Write-Host "=== hw_server stdout ===" -ForegroundColor Yellow
if (Test-Path "hw_server_stdout.log") {
    Get-Content "hw_server_stdout.log"
}

Write-Host ""
Write-Host "=== hw_server stderr ===" -ForegroundColor Yellow
if (Test-Path "hw_server_stderr.log") {
    Get-Content "hw_server_stderr.log"
}

Write-Host ""
Write-Host "=== Check Digilent Adept runtime installed ===" -ForegroundColor Cyan
$adeptReg = Get-ChildItem "HKLM:\SOFTWARE\Digilent" -ErrorAction SilentlyContinue
if ($adeptReg) {
    Write-Host "Digilent registry found"
    $adeptReg | Format-List
} else {
    Write-Host "Digilent registry NOT found - Adept runtime may not be installed" -ForegroundColor Red
}

# Check for djtgcfg
Write-Host ""
Write-Host "=== djtgcfg utility ===" -ForegroundColor Cyan
Get-ChildItem "C:\Program Files*","C:\Xilinx" -Filter "djtgcfg.exe" -Recurse -ErrorAction SilentlyContinue | Select-Object FullName
