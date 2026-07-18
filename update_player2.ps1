
$file = "Source\Player.cpp"
$c = [System.IO.File]::ReadAllText($file, [System.Text.Encoding]::GetEncoding(932))
$c = $c -replace "if \(hp_ <= 0\)\s*\{\s*OnDeath\(\);\s*\}", ""
[System.IO.File]::WriteAllText($file, $c, [System.Text.Encoding]::GetEncoding(932))

