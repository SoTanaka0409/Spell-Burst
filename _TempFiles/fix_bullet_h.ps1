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

# --- Bullet.h ---
$bullet_repl = [ordered]@{
    'Bullet(float x, float y, float damage);' = 'Bullet(float x, float y, int damage);'
    'float m_speed;        ' = 'float m_speed;        // 弾の進行速度'
    'bool m_isActive;      ' = 'bool m_isActive;      // 弾が画面内に存在し有効かどうかのフラグ'
    'int m_damage;         ' = 'int m_damage;         // 敵に与えるダメージ量'
    'int m_recivedDamage;      ' = 'int m_recivedDamage;      // （貫通弾などで）これまでに与えたダメージの蓄積'
    'int m_MaxrecivedDamage; ' = 'int m_MaxrecivedDamage; // この弾が与えられる最大ダメージ上限（貫通制限）'
    'CapsuleCollider* mpCollider;' = 'CapsuleCollider* mpCollider; // 当たり判定用コライダー'
}
Replace-InFile -Path "Source\Bullet.h" -Replacements $bullet_repl

Write-Host "All replacements done!"
