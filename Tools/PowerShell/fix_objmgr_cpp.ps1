$file = 'Source\ObjectManager.cpp'
$content = [System.IO.File]::ReadAllText($file, [System.Text.Encoding]::GetEncoding(932))
$content = $content -replace '\btag_\b', 'tag'
[System.IO.File]::WriteAllText($file, $content, [System.Text.Encoding]::GetEncoding(932))
