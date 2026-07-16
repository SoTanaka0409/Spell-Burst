$file = 'Source\InputManager.cpp'
$content = [System.IO.File]::ReadAllText($file, [System.Text.Encoding]::GetEncoding(932))
$content = $content -replace '\bKeyCode\b', 'keyCode'
[System.IO.File]::WriteAllText($file, $content, [System.Text.Encoding]::GetEncoding(932))
