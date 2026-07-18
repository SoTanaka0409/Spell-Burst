
$file = "Source\Character.cpp"
$c = [System.IO.File]::ReadAllText($file, [System.Text.Encoding]::GetEncoding(932))
$c = $c -replace "void Character::TakeDamage\(int damage\)\s*\{", "void Character::TakeDamage(int damage)`r`n{`r`n    if (!is_active_) return;"
[System.IO.File]::WriteAllText($file, $c, [System.Text.Encoding]::GetEncoding(932))

