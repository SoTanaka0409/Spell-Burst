$file = 'Source\Player.cpp'
$content = [System.IO.File]::ReadAllText($file, [System.Text.Encoding]::GetEncoding(932))
# The Attack() method wrongly became attack_power_() - fix: the function was "attack" (lowercase),
# so the member was renamed to attack_power_ but the function should have been "Attack"
$content = $content -replace 'Player::attack_power_\(\)', 'Player::Attack()'
$content = $content -replace 'attack_power_\(\)', 'Attack()'
[System.IO.File]::WriteAllText($file, $content, [System.Text.Encoding]::GetEncoding(932))
