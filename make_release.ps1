# ============================================
# spell_Burst リリースフォルダ作成スクリプト
# Visual Studio で Release x64 ビルド後に実行
# ============================================

$projectDir  = $PSScriptRoot
$releaseExe  = Join-Path $projectDir "x64\Release\spell_Burst.exe"
$outputDir   = Join-Path $projectDir "..\spell_Burst_Release"

# exeが存在するか確認
if (-not (Test-Path $releaseExe)) {
    Write-Host "ERROR: exe が見つかりません: $releaseExe" -ForegroundColor Red
    Write-Host "先に Visual Studio で Release x64 ビルドを実行してください。" -ForegroundColor Yellow
    pause
    exit 1
}

# 出力フォルダを作成
New-Item -ItemType Directory -Force -Path $outputDir | Out-Null

# exe をコピー
Copy-Item -Path $releaseExe -Destination $outputDir -Force

# Resource フォルダをコピー
Copy-Item -Path (Join-Path $projectDir "Resource") -Destination $outputDir -Recurse -Force

Write-Host "完了！リリースフォルダを作成しました:" -ForegroundColor Green
Write-Host $outputDir -ForegroundColor Cyan
Write-Host ""
Write-Host "内容:"
Get-ChildItem $outputDir | Format-Table Name, Length, LastWriteTime
pause
