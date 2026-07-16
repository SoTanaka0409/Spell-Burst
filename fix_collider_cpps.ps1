$file1 = 'Source\CapsuleCollider.cpp'
$content1 = [System.IO.File]::ReadAllText($file1, [System.Text.Encoding]::GetEncoding(932))
$content1 = $content1 -replace 'float radius_\)', 'float radius)'
$content1 = $content1 -replace 'radius_\(radius_\)', 'radius_(radius)'
[System.IO.File]::WriteAllText($file1, $content1, [System.Text.Encoding]::GetEncoding(932))

$file2 = 'Source\SphereCollider.cpp'
$content2 = [System.IO.File]::ReadAllText($file2, [System.Text.Encoding]::GetEncoding(932))
$content2 = $content2 -replace 'float radius_\)', 'float radius)'
$content2 = $content2 -replace 'radius_\(radius_\)', 'radius_(radius)'
[System.IO.File]::WriteAllText($file2, $content2, [System.Text.Encoding]::GetEncoding(932))
