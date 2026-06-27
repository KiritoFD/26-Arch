# Check Digilent Adept runtime and Vivado hw_server setup
Write-Host "=== Digilent Adept Runtime ===" -ForegroundColor Cyan
$adeptPaths = @(
    "C:\Program Files\Digilent\adept",
    "C:\Program Files (x86)\Digilent\adept",
    "C:\Digilent"
)
foreach ($p in $adeptPaths) {
    if (Test-Path $p) {
        Write-Host "Found: $p"
        Get-ChildItem $p -Recurse -ErrorAction SilentlyContinue | Where-Object Name -match 'djtgcfg|dpcutil|adept' | Select-Object FullName, Length
    }
}

Write-Host ""
Write-Host "=== djtgcfg.exe location ===" -ForegroundColor Cyan
Get-ChildItem "C:\Xilinx","C:\Program Files*","C:\Digilent" -Filter "djtgcfg.exe" -Recurse -ErrorAction SilentlyContinue | Select-Object FullName -First 5

Write-Host ""
Write-Host "=== Vivado install location ===" -ForegroundColor Cyan
Get-ChildItem "C:\Xilinx" -Directory -ErrorAction SilentlyContinue | Select-Object FullName

Write-Host ""
Write-Host "=== Digilent plugin in Vivado ===" -ForegroundColor Cyan
Get-ChildItem "C:\Xilinx" -Filter "digilent*" -Recurse -ErrorAction SilentlyContinue | Select-Object FullName -First 10
Get-ChildItem "C:\Xilinx" -Filter "diligent*" -Recurse -ErrorAction SilentlyContinue | Select-Object FullName -First 5

Write-Host ""
Write-Host "=== hw_server location ===" -ForegroundColor Cyan
Get-ChildItem "C:\Xilinx" -Filter "hw_server.exe" -Recurse -ErrorAction SilentlyContinue | Select-Object FullName -First 3
