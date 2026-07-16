$file = 'Source\ObjectManager.h'
$content = [System.IO.File]::ReadAllText($file, [System.Text.Encoding]::GetEncoding(932))

$content = $content -replace 'void GetObject2DByTag\(Object2D::Tag2D tag_\)', 'void GetObject2DByTag(Object2D::Tag2D tag)'
$content = $content -replace 'tag_', 'tag'

[System.IO.File]::WriteAllText($file, $content, [System.Text.Encoding]::GetEncoding(932))
