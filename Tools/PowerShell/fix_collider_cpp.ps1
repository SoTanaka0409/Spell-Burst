$file1 = 'Source\Collider.cpp'
$content1 = [System.IO.File]::ReadAllText($file1, [System.Text.Encoding]::GetEncoding(932))
$content1 = $content1 -replace 'collider_\)', 'collider)'
[System.IO.File]::WriteAllText($file1, $content1, [System.Text.Encoding]::GetEncoding(932))

$file2 = 'Source\ColliderManager.cpp'
$content2 = [System.IO.File]::ReadAllText($file2, [System.Text.Encoding]::GetEncoding(932))
$content2 = $content2 -replace 'collider_list_\.push_back\(Collider\);', 'collider_list_.push_back(collider);'
$content2 = $content2 -replace 'collider_list_\.remove\(collider_\);', 'collider_list_.remove(collider);'
[System.IO.File]::WriteAllText($file2, $content2, [System.Text.Encoding]::GetEncoding(932))
