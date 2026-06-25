# Read serial port while reprogramming FPGA
# This ensures we capture UART output from the moment CPU starts

$port = New-Object System.IO.Ports.SerialPort COM4,115200,None,8,One
$port.ReadTimeout = 1000
$port.Open()
Write-Output "Serial port COM4 opened, waiting for data..."

# Start programming FPGA in background
$progJob = Start-Job -ScriptBlock {
    $env:PATH = "G:\Vivado\2018.3\bin;$env:PATH"
    & "G:\Vivado\2018.3\bin\vivado.bat" -mode batch -source "g:\GitHub\26-Arch\vivado\program_fpga.tcl" -log "g:\GitHub\26-Arch\vivado\program_log2.txt" 2>&1
}

# Read serial port for 60 seconds
$startTime = Get-Date
$allData = ""
while (((Get-Date) - $startTime).TotalSeconds -lt 60) {
    try {
        $data = $port.ReadExisting()
        if ($data.Length -gt 0) {
            $allData += $data
            Write-Output "Received: [$data]"
        }
    } catch {}

    # Check if programming is done
    $state = Get-Job -Id $progJob.Id | Select-Object -ExpandProperty State
    if ($state -eq "Completed" -and $allData.Length -gt 0) {
        # Wait a bit more for any remaining data
        Start-Sleep -Seconds 3
        try {
            $data = $port.ReadExisting()
            if ($data.Length -gt 0) {
                $allData += $data
                Write-Output "Final: [$data]"
            }
        } catch {}
        break
    }
    Start-Sleep -Milliseconds 100
}

$port.Close()
Remove-Job -Force -Id $progJob.Id -ErrorAction SilentlyContinue

Write-Output "`n=== Total UART Output ==="
Write-Output $allData
Write-Output "=== End ==="
if ($allData.Length -eq 0) {
    Write-Output "WARNING: No UART output received!"
}
