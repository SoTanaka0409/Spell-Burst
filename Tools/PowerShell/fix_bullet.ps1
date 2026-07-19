$file = 'Source\Bullet.h'
$content = [System.IO.File]::ReadAllText($file, [System.Text.Encoding]::GetEncoding(932))
$content = $content -replace 'Bullet\(float x, float y, int damage_\)', 'Bullet(float x, float y, int damage)'
$content = $content -replace '\brecivedDamage\b', 'received_damage_'
$content = $content -replace '\bmaxrecivedDamage\b', 'max_received_damage_'
[System.IO.File]::WriteAllText($file, $content, [System.Text.Encoding]::GetEncoding(932))

$file2 = 'Source\Bullet.cpp'
$content2 = [System.IO.File]::ReadAllText($file2, [System.Text.Encoding]::GetEncoding(932))
$content2 = $content2 -replace 'Bullet\(float x, float y, int damage_\)', 'Bullet(float x, float y, int damage)'
$content2 = $content2 -replace 'Projectile\(Vector2\(x, y\), Vector2\(0.f, -1.f\), 10.f, damage_\)', 'Projectile(Vector2(x, y), Vector2(0.f, -1.f), 10.f, damage)'
$content2 = $content2 -replace '\brecivedDamage\b', 'received_damage_'
$content2 = $content2 -replace '\bmaxrecivedDamage\b', 'max_received_damage_'
[System.IO.File]::WriteAllText($file2, $content2, [System.Text.Encoding]::GetEncoding(932))
