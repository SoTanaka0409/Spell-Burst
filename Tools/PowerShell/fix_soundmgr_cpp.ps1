$file = 'Source\SoundManager.cpp'
$content = [System.IO.File]::ReadAllText($file, [System.Text.Encoding]::GetEncoding(932))
$content = $content -replace '\bsoundMap\b', 'sound_map_'
[System.IO.File]::WriteAllText($file, $content, [System.Text.Encoding]::GetEncoding(932))
