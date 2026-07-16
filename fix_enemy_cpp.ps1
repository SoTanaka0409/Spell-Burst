# Fix Enemy.cpp
$file = 'Source\Enemy.cpp'
$content = [System.IO.File]::ReadAllText($file, [System.Text.Encoding]::GetEncoding(932))
$content = $content -replace 'Enemy\(float x, float y, int enemy_type_\b', 'Enemy(float x, float y, int enemyType'
$content = $content -replace 'enemy_type_\(enemy_type_\)', 'enemy_type_(enemyType)'
$content = $content -replace 'Enemy::TakeDamage\(int damage_\)', 'Enemy::TakeDamage(int damage)'
$content = $content -replace 'Character::TakeDamage\(damage_\)', 'Character::TakeDamage(damage)'
$content = $content -replace '\btargetX\b', 'target_x_'
$content = $content -replace '\btargetY\b', 'target_y_'
[System.IO.File]::WriteAllText($file, $content, [System.Text.Encoding]::GetEncoding(932))
