$files = Get-ChildItem -Path Source -Include *.cpp,*.h -Recurse
foreach ($file in $files) {
    $content = [System.IO.File]::ReadAllText($file.FullName, [System.Text.Encoding]::GetEncoding(932))
    if ($content -match 'Collider\*\s*collider_') {
        $content = $content -replace 'Collider\*\s*collider_', 'Collider* collider'
        [System.IO.File]::WriteAllText($file.FullName, $content, [System.Text.Encoding]::GetEncoding(932))
    }
}
