$enc = [System.Text.Encoding]::GetEncoding("shift_jis")
$files = Get-ChildItem Source\*.cpp, Source\*.h

foreach ($file in $files) {
    $content = [System.IO.File]::ReadAllText($file.FullName, $enc)
    
    $modified = $false
    
    # We want to insert NOMINMAX if not already present
    if ($content -notmatch "NOMINMAX") {
        if ($content -match '#include\s*["<]DxLib\.h[">]') {
            $content = $content -replace '#include\s*["<]DxLib\.h[">]', "#ifndef NOMINMAX`r`n#define NOMINMAX`r`n#endif`r`n#include `"DxLib.h`""
            $modified = $true
        } elseif ($content -match '#include\s*["<]Dxlib\.h[">]') {
            $content = $content -replace '#include\s*["<]Dxlib\.h[">]', "#ifndef NOMINMAX`r`n#define NOMINMAX`r`n#endif`r`n#include `"DxLib.h`""
            $modified = $true
        }
    }
    
    if ($modified) {
        # Read the original bytes to see if it had a BOM
        $bytes = [System.IO.File]::ReadAllBytes($file.FullName)
        $hasBom = ($bytes.Length -ge 3 -and $bytes[0] -eq 239 -and $bytes[1] -eq 187 -and $bytes[2] -eq 191)
        
        if ($hasBom) {
            $utf8 = New-Object System.Text.UTF8Encoding $true
            [System.IO.File]::WriteAllText($file.FullName, $content, $utf8)
        } else {
            [System.IO.File]::WriteAllText($file.FullName, $content, $enc)
        }
        Write-Host "Updated $($file.Name)"
    }
}
