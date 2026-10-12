# ============================================================================
# w4-stl 快速验证脚本（助手写的工具，不是练习）
# ----------------------------------------------------------------------------
# 用法（在 D:\Code\cpp-journey\w4\w4-stl 目录下）：
#     .\run.ps1 p01_sizeof      只构建并运行这一个目标（别的目标坏了也不影响）
#     .\run.ps1 all             构建全部，然后依次运行 build\Debug 里所有 exe
#     .\run.ps1                 只构建全部
# ============================================================================
param([string]$Target = "")

Set-Location $PSScriptRoot

$cache = Join-Path $PSScriptRoot "build\CMakeCache.txt"
if (-not (Test-Path -LiteralPath $cache)) {
    Write-Host "== 第一次 configure ==" -ForegroundColor Cyan
    cmake -S . -B build -G "Visual Studio 18 2026" -A x64
    if ($LASTEXITCODE -ne 0) { exit 1 }
}

# 每次先 configure 一次：
#   labs\ 里新加的 .cpp 只有 configure 之后才会变成目标，
#   所以"新加文件 → 直接 run"必须走这一步。
if ($Target -ne "") {
    $cfg = cmake -S . -B build 2>&1
    if ($LASTEXITCODE -ne 0) {
        $cfg | ForEach-Object { Write-Host $_ }
        Write-Host "configure 失败。" -ForegroundColor Red
        exit 1
    }
}

if ($Target -eq "") {
    cmake --build build --config Debug --parallel
    exit $LASTEXITCODE
}

if ($Target -eq "all") {
    Write-Host "== 构建全部 ==" -ForegroundColor Cyan
    cmake --build build --config Debug --parallel
    if ($LASTEXITCODE -ne 0) {
        Write-Host "构建失败，先把上面的错误修掉。" -ForegroundColor Red
        exit 1
    }
    Get-ChildItem -LiteralPath (Join-Path $PSScriptRoot "build\Debug") -Filter *.exe | ForEach-Object {
        Write-Host ("===== " + $_.BaseName + " =====") -ForegroundColor Yellow
        & $_.FullName
        Write-Host ("[退出码 " + $LASTEXITCODE + "]")
    }
    exit 0
}

Write-Host ("== 构建 " + $Target + " ==") -ForegroundColor Cyan
cmake --build build --config Debug --target $Target --parallel
if ($LASTEXITCODE -ne 0) {
    Write-Host "构建失败，先把上面的错误修掉。" -ForegroundColor Red
    exit 1
}

$exe = Join-Path $PSScriptRoot ("build\Debug\" + $Target + ".exe")
if (-not (Test-Path -LiteralPath $exe)) {
    Write-Host ("没有这个目标：" + $Target) -ForegroundColor Red
    Write-Host "现有目标："
    Get-ChildItem -LiteralPath (Join-Path $PSScriptRoot "build\Debug") -Filter *.exe |
        ForEach-Object { Write-Host ("  " + $_.BaseName) }
    exit 1
}

& $exe
