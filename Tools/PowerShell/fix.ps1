function Get-OriginalText($path) {
    $tempFile = [System.IO.Path]::GetTempFileName()
    cmd /c "git show HEAD:$path > $tempFile 2>nul"
    if ($LASTEXITCODE -ne 0) { return $null }
    
    $bytes = [System.IO.File]::ReadAllBytes($tempFile)
    Remove-Item $tempFile
    
    if ($bytes.Length -ge 2 -and $bytes[0] -eq 0xFF -and $bytes[1] -eq 0xFE) {
        return [System.Text.Encoding]::Unicode.GetString($bytes, 2, $bytes.Length - 2)
    }
    if ($bytes.Length -ge 3 -and $bytes[0] -eq 0xEF -and $bytes[1] -eq 0xBB -and $bytes[2] -eq 0xBF) {
        return [System.Text.Encoding]::UTF8.GetString($bytes, 3, $bytes.Length - 3)
    }
    return [System.Text.Encoding]::GetEncoding(932).GetString($bytes)
}

$files = Get-ChildItem -Path "Source" -Include *.cpp, *.h -Recurse
foreach ($file in $files) {
    $currPath = $file.FullName
    $relPath = $currPath.Substring((Get-Location).Path.Length + 1).Replace("\", "/")
    
    $origText = Get-OriginalText $relPath
    if (-not $origText) { continue }
    
    $currText = [System.IO.File]::ReadAllText($currPath)
    if (-not ($currText -match "u{FFFD}") -and -not ($currText -match "\.3"")) { continue }
    
    $origLines = $origText -split "
"
    $currLines = $currText -split "
"
    
    for ($i=0; $i -lt $currLines.Length; $i++) {
        if ($currLines[$i] -match "u{FFFD}" -or $currLines[$i] -match "\.3"") {
            # Find the most similar line in original
            # Since the C++ code part is usually identical, we can match on the first 10 chars, or just the structure.
            $strippedCurr = $currLines[$i].TrimStart()
            
            foreach ($oLine in $origLines) {
                $strippedOrig = $oLine.TrimStart()
                # Match by prefix (e.g. "SoundManager::GetInstance()->PlaySE")
                $prefix = $strippedCurr.Split('(')[0]
                if ($prefix.Length -gt 5 -and $strippedOrig.StartsWith($prefix)) {
                    $currLines[$i] = $currLines[$i].Replace($strippedCurr, $strippedOrig)
                    break
                }
                # If it's a comment
                if ($strippedCurr.StartsWith("//") -and $strippedOrig.StartsWith("//")) {
                    # very risky to match all comments, so we just check if it's roughly the same length
                    if ([math]::Abs($strippedCurr.Length - $strippedOrig.Length) -lt 20) {
                        # let's just do a greedy replacement based on line index if they are close
                        # We won't do this for all comments to avoid messing up.
                    }
                }
            }
            
            # Fallback for comments: replace if line index is valid and both are comments
            if ($currLines[$i] -match "u{FFFD}" -and $strippedCurr.StartsWith("//")) {
                if ($i -lt $origLines.Length -and $origLines[$i].TrimStart().StartsWith("//")) {
                    $currLines[$i] = $origLines[$i]
                }
            }
        }
    }
    
    [System.IO.File]::WriteAllText($currPath, ($currLines -join "
"), [System.Text.UTF8Encoding]::new($true))
    Write-Host "Fixed $relPath"
}
