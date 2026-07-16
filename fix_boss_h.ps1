# Fix Boss.h - apply naming conventions
$file = 'Source\Boss.h'
$lines = [System.IO.File]::ReadAllLines($file, [System.Text.Encoding]::GetEncoding(932))
$outLines = @()

foreach ($line in $lines) {
    if ($line -match '^\s*//') { continue }
    if ($line -match '\s*int bossType;') {
        $outLines += "    int boss_type_;"
    } elseif ($line -match '\s*float targetX, targetY;') {
        $outLines += "    float target_x_;"
        $outLines += "    float target_y_;"
    } elseif ($line -match '\s*int patternIndex;') {
        $outLines += "    int pattern_index_;"
    } elseif ($line -match '\s*bool isDying;') {
        $outLines += "    bool is_dying_;"
    } elseif ($line -match '\s*int deathTimer;') {
        $outLines += "    int death_timer_;"
    } elseif ($line -match '\s*int lives;') {
        $outLines += "    int lives_;"
    } elseif ($line -match '\s*int invincibleTimer;') {
        $outLines += "    int invincible_timer_;"
    } elseif ($line -match '\s*int invincibleCycleTimer;') {
        $outLines += "    int invincible_cycle_timer_;"
    } elseif ($line -match 'Boss\(float x, float y, int bossType = 3\)') {
        $outLines += "    Boss(float x, float y, int bossType = 3);"
    } elseif ($line -match '    int GetLives\(\) const { return lives; }') {
        $outLines += "    int GetLives() const { return lives_; }"
    } elseif ($line -match '^\s*virtual void TakeDamage\(int damage_\) override;') {
        $outLines += "    /*"
        $outLines += "     * ボスにダメージを与える。無敵中は処理を通さない。"
        $outLines += "     * [入力] damage: 受けるダメージ量"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] HPを減らし、ライフ管理・死亡処理を呼ぶ"
        $outLines += "     */"
        $outLines += "    virtual void TakeDamage(int damage) override;"
    } elseif ($line -match '^\s*virtual void OnTrigger\(Collider\* collider, Collider\* check\) override;') {
        $outLines += "    /*"
        $outLines += "     * コライダー接触中の毎フレーム処理。プレイヤーへのダメージ等を行う。"
        $outLines += "     * [入力] collider: 自身のコライダー, check: 相手のコライダー"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] プレイヤーにダメージが入ることがある"
        $outLines += "     */"
        $outLines += "    virtual void OnTrigger(Collider* collider, Collider* check) override;"
    } elseif ($line -match '^\s*void ShootRadialBarrage\(\);') {
        $outLines += "    /*"
        $outLines += "     * ボスの攻撃パターン群（フェーズや状態に応じて呼ばれる）。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] 弾丸がゲーム内にスポーンする"
        $outLines += "     */"
        $outLines += "    void ShootRadialBarrage();"
    } elseif ($line -match '^\s*void UpdateDeath\(\);') {
        $outLines += "    /*"
        $outLines += "     * ボスの死亡演出フレームを更新し、最終的に削除フラグを立てる。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] death_timer_が減少し、0になったら破棄処理が実行される"
        $outLines += "     */"
        $outLines += "    void UpdateDeath();"
    } elseif ($line -match '    int GetBossType\(\) const { return bossType; }') {
        $outLines += "    int GetBossType() const { return boss_type_; }"
    } elseif ($line -match '    bool GetIsDying\(\) const { return isDying; }') {
        $outLines += "    bool GetIsDying() const { return is_dying_; }"
    } elseif ($line -match '    int GetInvincibleTimer\(\) const { return invincibleTimer; }') {
        $outLines += "    int GetInvincibleTimer() const { return invincible_timer_; }"
    } elseif ($line -match '    void SetInvincibleTimer\(int t\) { invincibleTimer = t; }') {
        $outLines += "    void SetInvincibleTimer(int t) { invincible_timer_ = t; }"
    } else {
        $outLines += $line
    }
}
[System.IO.File]::WriteAllLines($file, $outLines, [System.Text.Encoding]::GetEncoding(932))
