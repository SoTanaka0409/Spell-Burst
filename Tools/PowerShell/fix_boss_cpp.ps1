$file = 'Source\Boss.cpp'
$content = [System.IO.File]::ReadAllText($file, [System.Text.Encoding]::GetEncoding(932))
$replacements = @{
    '\bbossType\b' = 'boss_type_'
    '\btargetX\b' = 'target_x_'
    '\btargetY\b' = 'target_y_'
    '\bpatternIndex\b' = 'pattern_index_'
    '\bisDying\b' = 'is_dying_'
    '\bdeathTimer\b' = 'death_timer_'
    '\blives\b' = 'lives_'
    '\binvincibleTimer\b' = 'invincible_timer_'
    '\binvincibleCycleTimer\b' = 'invincible_cycle_timer_'
    'Boss::TakeDamage\(int damage_\)' = 'Boss::TakeDamage(int damage)'
    'Character::TakeDamage\(damage_\)' = 'Character::TakeDamage(damage)'
}
foreach ($key in $replacements.Keys) {
    $content = $content -replace $key, $replacements[$key]
}
[System.IO.File]::WriteAllText($file, $content, [System.Text.Encoding]::GetEncoding(932))
