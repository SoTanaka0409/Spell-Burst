$file = "Source\Enemy.cpp"
$lines = [System.IO.File]::ReadAllLines($file, [System.Text.Encoding]::GetEncoding(932))
$newLines = @()

foreach ($line in $lines) {
    if ($line -match '^(\s*)(.*[^\s])\s*\{(\s*(?://.*)?)$') {
        $indent = $matches[1]
        $content = $matches[2]
        $trail = $matches[3]
        
        $newLines += "$indent$content"
        $newLines += "$indent{$trail"
    } else {
        $newLines += $line
    }
}
[System.IO.File]::WriteAllLines($file, $newLines, [System.Text.Encoding]::GetEncoding(932))
