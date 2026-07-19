$file = 'Source\Bullet.cpp'
$c = [System.IO.File]::ReadAllText($file, [System.Text.Encoding]::GetEncoding(932))
$c = $c -replace 'Projectile\(Vector2\(x, y\), Vector2\(0, -1\), 20.0f, damage_\)', 'Projectile(Vector2(x, y), Vector2(0, -1), 20.0f, damage)'
[System.IO.File]::WriteAllText($file, $c, [System.Text.Encoding]::GetEncoding(932))
