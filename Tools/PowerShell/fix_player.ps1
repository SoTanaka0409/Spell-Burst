# Player.h - fix parameter names, add comments for non-trivial methods
$file = 'Source\Player.h'
$content = [System.IO.File]::ReadAllText($file, [System.Text.Encoding]::GetEncoding(932))
$content = $content -replace '\s*float attack;', "    float attack_power_;"
$content = $content -replace 'virtual void TakeDamage\(int damage_\) override;', "    /*
     * プレイヤーにダメージを与える（バリアや無敵判定考慮）。
     * [入力] damage: 受けるダメージ量
     * [出力] なし
     * [副作用] HPを減らし、死亡判定やHPバーの更新が発生する
     */
    virtual void TakeDamage(int damage) override;"
$content = $content -replace 'void AddXp\(int amount\);', "    /*
     * プレイヤーにXP（経験値）を加算し、レベルアップを処理する。
     * [入力] amount: 追加するXP量
     * [出力] なし
     * [副作用] XPが加算され、条件を満たすとlevel_が増加する
     */
    void AddXp(int amount);"
[System.IO.File]::WriteAllText($file, $content, [System.Text.Encoding]::GetEncoding(932))

# Player.cpp - fix variable names
$file2 = 'Source\Player.cpp'
$content2 = [System.IO.File]::ReadAllText($file2, [System.Text.Encoding]::GetEncoding(932))
$content2 = $content2 -replace '\battack\b(?!\s*_|\w)', 'attack_power_'
$content2 = $content2 -replace 'Player::TakeDamage\(int damage_\)', 'Player::TakeDamage(int damage)'
$content2 = $content2 -replace 'Character::TakeDamage\(damage_\)', 'Character::TakeDamage(damage)'
[System.IO.File]::WriteAllText($file2, $content2, [System.Text.Encoding]::GetEncoding(932))
