
$file = "Source\ColliderManager.cpp"
$c = [System.IO.File]::ReadAllText($file, [System.Text.Encoding]::GetEncoding(932))

$c = $c -replace "(col1->Update\(col2\);)", "`$1`r`n					col2->Update(col1);"

[System.IO.File]::WriteAllText($file, $c, [System.Text.Encoding]::GetEncoding(932))

