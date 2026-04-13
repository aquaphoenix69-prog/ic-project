$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

if (-not (Test-Path ".\build\SurvivalIsland.exe")) {
    Write-Host "Build not found. Running build first..."
    .\build.ps1
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
}

& ".\build\SurvivalIsland.exe"
