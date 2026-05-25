$enc = [Text.Encoding]::GetEncoding('shift_jis')
$files = Get-ChildItem -Path '.' -Include *.cpp, *.h -Recurse
foreach ($f in $files) {
    $text = [IO.File]::ReadAllText($f.FullName, $enc)
    $new = [regex]::Replace($text, '\bm_x\b', 'mvPosition.x')
    $new = [regex]::Replace($new, '\bm_y\b', 'mvPosition.y')
    $new = [regex]::Replace($new, '(?m)^[ \t]*float\s+mvPosition\.x\s*,\s*mvPosition\.y\s*;.*$\r?\n?', '')
    if ($new -ne $text) {
        [IO.File]::WriteAllText($f.FullName, $new, $enc)
        Write-Host "Updated $($f.Name)"
    }
}
