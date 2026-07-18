
$file = "Source\Enemy.cpp"
$c = [System.IO.File]::ReadAllText($file, [System.Text.Encoding]::GetEncoding(932))
$c = $c -replace "void Enemy::OnDeath\(\)\s*\{", "void Enemy::OnDeath()`r`n{`r`n    Character::OnDeath();`r`n"
[System.IO.File]::WriteAllText($file, $c, [System.Text.Encoding]::GetEncoding(932))

