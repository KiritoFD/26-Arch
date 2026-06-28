param([string]$Script, [int]$TimeoutSec=15, [string]$ExtraArgs='')
if ($ExtraArgs -ne '') {
    $p = Start-Process python -ArgumentList @($Script, $ExtraArgs) -NoNewWindow -PassThru
} else {
    $p = Start-Process python -ArgumentList $Script -NoNewWindow -PassThru
}
if (-not $p.WaitForExit($TimeoutSec * 1000)) {
    $p.Kill()
    Write-Host "TIMEOUT-KILLED after $TimeoutSec sec"
} else {
    Write-Host "EXIT_CODE=$($p.ExitCode)"
}
