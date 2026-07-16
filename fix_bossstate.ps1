$files = @('Source\BossState.h', 'Source\BossStateAttack.h', 'Source\BossStateAttack.cpp')
foreach ($path in $files) {
    if (Test-Path $path) {
        $content = [System.IO.File]::ReadAllText($path, [System.Text.Encoding]::GetEncoding(932))
        $content = $content -replace '\bbossType\b', 'boss_type_'
        $content = $content -replace '\btargetX\b', 'target_x_'
        $content = $content -replace '\btargetY\b', 'target_y_'
        $content = $content -replace '\bpatternIndex\b', 'pattern_index_'
        $content = $content -replace '\bisDying\b', 'is_dying_'
        $content = $content -replace '\bdeathTimer\b', 'death_timer_'
        $content = $content -replace '\binvincibleTimer\b', 'invincible_timer_'
        $content = $content -replace '\binvincibleCycleTimer\b', 'invincible_cycle_timer_'
        [System.IO.File]::WriteAllText($path, $content, [System.Text.Encoding]::GetEncoding(932))
    }
}
