$files = @('Source\EnemyBullet.cpp', 'Source\PlayerHomingBullet.cpp', 'Source\RainbowBullet.cpp',
            'Source\SpecialBullet.cpp', 'Source\SpellCardBullet.cpp', 'Source\MasterSpark.cpp', 'Source\MeleeAttack.cpp')
foreach ($path in $files) {
    if (Test-Path $path) {
        $content = [System.IO.File]::ReadAllText($path, [System.Text.Encoding]::GetEncoding(932))
        # Replace dir when used as member (dir. or dir =, but not 'direction' or 'dir_')
        $content = $content -replace '(?<![a-zA-Z_])\bdir\b(?!_|[a-zA-Z_])', 'dir_'
        [System.IO.File]::WriteAllText($path, $content, [System.Text.Encoding]::GetEncoding(932))
    }
}
