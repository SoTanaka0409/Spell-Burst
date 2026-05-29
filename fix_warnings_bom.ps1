$enc = [System.Text.Encoding]::GetEncoding("shift_jis")

function Replace-InFile {
    param (
        [string]$Path,
        [hashtable]$Replacements
    )
    
    $content = [System.IO.File]::ReadAllText($Path, $enc)
    
    foreach ($old in $Replacements.Keys) {
        $new = $Replacements[$old]
        if ($content -notmatch [regex]::Escape($old)) {
            Write-Host "Warning: Could not find '$old' in $Path"
        }
        $content = $content -replace [regex]::Escape($old), $new
    }
    
    [System.IO.File]::WriteAllText($Path, $content, $enc)
    Write-Host "Updated $Path"
}

# --- Utility.h ---
$util_repl = [ordered]@{
    'int count = (times.size() < 5) ? times.size() : 5;' = 'int count = (times.size() < 5) ? static_cast<int>(times.size()) : 5;'
}
Replace-InFile -Path "Source\Utility.h" -Replacements $util_repl

# --- Bullet.cpp ---
$bullet_repl = [ordered]@{
    'Bullet::Bullet(float x, float y,float damage)' = 'Bullet::Bullet(float x, float y, int damage)'
}
Replace-InFile -Path "Source\Bullet.cpp" -Replacements $bullet_repl

# --- TitleScene.cpp ---
$title_repl = [ordered]@{
    'DrawStringToHandle(Utility::SCREEN_WIDTH - 300, 100 + i * 50, rankStr, GetColor(255, 215, 0), rankFont);' = 'DrawStringToHandle(Utility::SCREEN_WIDTH - 300, 100 + static_cast<int>(i) * 50, rankStr, GetColor(255, 215, 0), rankFont);'
}
Replace-InFile -Path "Source\TitleScene.cpp" -Replacements $title_repl

Write-Host "All replacements done!"
