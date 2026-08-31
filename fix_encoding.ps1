$content = Get-Content 'Source\Boss.cpp' -Encoding UTF8
$content = $content -replace 'I will be waiting for you in the next stage\.\.\.!', '次のステージで待っているぞ……！'
Set-Content -Path 'Source\Boss.cpp' -Value $content -Encoding Default
