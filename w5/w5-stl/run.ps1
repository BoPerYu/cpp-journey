param([string]$Target = "")

Set-Location $PSScriptRoot

if (-not (Test-Path -LiteralPath "build\CMakeCache.txt")) {
    cmake -S . -B build -G "Visual Studio 18 2026" -A x64
    if ($LASTEXITCODE -ne 0) { exit 1 }
}

if ($Target -eq "") {
    cmake --build build --config Debug --parallel
    exit $LASTEXITCODE
}

cmake -S . -B build
if ($LASTEXITCODE -ne 0) { exit 1 }

cmake --build build --config Debug --target $Target --parallel
if ($LASTEXITCODE -ne 0) { exit 1 }

& ".\build\Debug\$Target.exe"
exit $LASTEXITCODE
