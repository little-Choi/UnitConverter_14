# Generate tests/golden_master_expected.txt from UnitConverter CLI stdout/stderr.
# Usage (from repo root):
#   .\scripts\generate_golden_master.ps1 [-BuildDir build] [-GitAdd]

param(
    [string]$BuildDir = "build",
    [switch]$GitAdd
)

$ErrorActionPreference = "Stop"
$RepoRoot = Split-Path -Parent $PSScriptRoot
Set-Location $RepoRoot

$Exe = Join-Path $BuildDir "UnitConverter.exe"
if (-not (Test-Path $Exe)) {
    Write-Host "Building UnitConverter in $BuildDir ..."
    cmake -S . -B $BuildDir | Out-Null
    cmake --build $BuildDir --target UnitConverter
}

$Scenarios = @("meter:2.5", "feet:1.0", "yard:1.0", "meter:0.0")
$Prompt = "Insert value for converting (ex: meter:2.5): "
$Scratch = Join-Path $RepoRoot "tests\.golden_master_scratch"
New-Item -ItemType Directory -Force -Path $Scratch | Out-Null

$OutPath = Join-Path $RepoRoot "tests\golden_master_expected.txt"
$Document = New-Object System.Text.StringBuilder

for ($i = 0; $i -lt $Scenarios.Count; $i++) {
    $InputLine = $Scenarios[$i]
    $InputFile = Join-Path $Scratch "input.txt"
    $StdoutFile = Join-Path $Scratch "stdout.txt"
    $StderrFile = Join-Path $Scratch "stderr.txt"

    Set-Content -Path $InputFile -Value $InputLine -NoNewline -Encoding ascii
    cmd /c "`"$Exe`" < `"$InputFile`" > `"$StdoutFile`" 2> `"$StderrFile`"" | Out-Null

    [void]$Document.AppendLine("[$InputLine]")
    $Stdout = Get-Content -Path $StdoutFile -Raw
    if ($Stdout.StartsWith($Prompt)) {
        $Stdout = $Stdout.Substring($Prompt.Length)
    }
    if ($Stdout) {
        [void]$Document.Append($Stdout.TrimEnd("`r", "`n"))
        [void]$Document.AppendLine()
    }
    $Stderr = Get-Content -Path $StderrFile -Raw
    if ($Stderr) {
        [void]$Document.Append($Stderr.TrimEnd("`r", "`n"))
        [void]$Document.AppendLine()
    }
    if ($i -lt ($Scenarios.Count - 1)) {
        [void]$Document.AppendLine("---")
    }
}

$Content = $Document.ToString()
# Normalize to LF for stable golden file on all platforms.
$Content = $Content -replace "`r`n", "`n"
if (-not $Content.EndsWith("`n")) {
    $Content += "`n"
}
[System.IO.File]::WriteAllText($OutPath, $Content, [System.Text.UTF8Encoding]::new($false))
Write-Host "Wrote $OutPath"

if ($GitAdd) {
    git add tests/golden_master_expected.txt
    Write-Host "Staged tests/golden_master_expected.txt"
}

Write-Host "Capture command per scenario:"
Write-Host "  ./UnitConverter < input.txt > actual.txt"
