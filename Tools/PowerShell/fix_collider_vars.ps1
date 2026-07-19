$files = Get-ChildItem -Path Source -Include *.cpp,*.h -Recurse
$replacements = @{
    '\bparentObject\b' = 'parent_object_'
    '\bposition2\b' = 'position2_'
}

foreach ($file in $files) {
    $content = [System.IO.File]::ReadAllText($file.FullName, [System.Text.Encoding]::GetEncoding(932))
    $changed = $false
    foreach ($key in $replacements.Keys) {
        if ($content -match $key) {
            $content = $content -replace $key, $replacements[$key]
            $changed = $true
        }
    }
    if ($changed) {
        [System.IO.File]::WriteAllText($file.FullName, $content, [System.Text.Encoding]::GetEncoding(932))
    }
}
