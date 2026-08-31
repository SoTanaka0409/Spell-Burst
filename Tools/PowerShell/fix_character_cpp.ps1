$file = 'Source\Character.cpp'
$content = [System.IO.File]::ReadAllText($file, [System.Text.Encoding]::GetEncoding(932))
$content = $content -replace 'Character::Character\(Vector2 pos, int max_hp_, float speed_\)', 'Character::Character(Vector2 pos, int maxHp, float speed)'
$content = $content -replace 'max_hp_\(max_hp_\)', 'max_hp_(maxHp)'
$content = $content -replace 'speed_\(speed_\)', 'speed_(speed)'
$content = $content -replace 'Character::TakeDamage\(int damage_\)', 'Character::TakeDamage(int damage)'
$content = $content -replace 'hp_ -= damage_;', 'hp_ -= damage;'
[System.IO.File]::WriteAllText($file, $content, [System.Text.Encoding]::GetEncoding(932))
