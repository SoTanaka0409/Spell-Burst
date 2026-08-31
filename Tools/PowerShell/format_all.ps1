$files = Get-ChildItem -Path Source -Include *.cpp,*.h -Recurse

foreach ($file in $files) {
    $lines = [System.IO.File]::ReadAllLines($file.FullName, [System.Text.Encoding]::GetEncoding(932))
    $newLines = @()
    $changed = $false
    
    foreach ($line in $lines) {
        if ($line -match '^(\s*)(.*[^\s])\s*\{(\s*(?://.*)?)$') {
            $indent = $matches[1]
            $content = $matches[2]
            $trail = $matches[3]
            
            $newLines += "$indent$content"
            $newLines += "$indent{$trail"
            $changed = $true
        } else {
            $newLines += $line
        }
    }
    
    if ($changed) {
        [System.IO.File]::WriteAllLines($file.FullName, $newLines, [System.Text.Encoding]::GetEncoding(932))
    }
}
