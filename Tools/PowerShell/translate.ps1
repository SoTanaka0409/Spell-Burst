function Translate-Text($text) {
    if (-not ($text -match '[\p{IsHiragana}\p{IsKatakana}\p{IsCJKUnifiedIdeographs}]')) { return $text }
    
    $uri = "https://translate.googleapis.com/translate_a/single?client=gtx&sl=ja&tl=en&dt=t&q=$([uri]::EscapeDataString($text))"
    try {
        $response = Invoke-RestMethod -Uri $uri -ErrorAction Stop
        $translated = $response[0][0][0]
        return $translated
    } catch {
        return $text
    }
}

$cache = @{}
$files = Get-ChildItem -Path "Source\*.cpp", "Source\*.h"
foreach ($f in $files) {
    $bytes = [System.IO.File]::ReadAllBytes($f.FullName)
    $encoding = "ShiftJIS"
    $utf8 = [System.Text.Encoding]::UTF8.GetString($bytes)
    if (-not $utf8.Contains([char]0xFFFD)) {
        $encoding = "UTF8"
    }
    
    $text = ""
    if ($encoding -eq "UTF8") {
        $text = $utf8
    } else {
        $text = [System.Text.Encoding]::GetEncoding(932).GetString($bytes)
    }
    
    $lines = $text -split "`r`n"
    if ($lines.Length -le 1) { $lines = $text -split "`n" }
    
    $changed = $false
    for ($i = 0; $i -lt $lines.Length; $i++) {
        if ($lines[$i] -match '^(.*?)//(.*)$') {
            $code = $matches[1]
            $comment = $matches[2].Trim()
            if ($comment -match '[\p{IsHiragana}\p{IsKatakana}\p{IsCJKUnifiedIdeographs}]') {
                if (-not $cache.ContainsKey($comment)) {
                    $cache[$comment] = Translate-Text $comment
                    Start-Sleep -Milliseconds 150
                }
                $translated = $cache[$comment]
                $lines[$i] = "$code// $translated"
                $changed = $true
            }
        }
    }
    
    if ($changed) {
        $newText = [string]::Join("`r`n", $lines)
        if ($encoding -eq "UTF8") {
            # UTF8 with BOM by default in powershell WriteAllText? No, UTF8 without BOM. Wait!
            # DxLib usually expects Shift-JIS or UTF-8 with BOM.
            # To be safe, I'll write as UTF8 with BOM.
            [System.IO.File]::WriteAllText($f.FullName, $newText, [System.Text.Encoding]::UTF8)
        } else {
            [System.IO.File]::WriteAllText($f.FullName, $newText, [System.Text.Encoding]::GetEncoding(932))
        }
    }
}
Write-Host "Translation completed."
