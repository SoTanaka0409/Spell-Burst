# --- Enemy.h fix ---
$file = 'Source\Enemy.h'
$lines = [System.IO.File]::ReadAllLines($file, [System.Text.Encoding]::GetEncoding(932))
$outLines = @()

foreach ($line in $lines) {
    if ($line -match '^\s*// .*') {
        continue
    }
    if ($line -match '    float targetX, targetY;') {
        $outLines += "    float target_x_;"
        $outLines += "    float target_y_;"
    } elseif ($line -match 'Enemy\(float x, float y, int enemy_type_ = 1\)') {
        $outLines += "    Enemy(float x, float y, int enemyType = 1);"
    } elseif ($line -match '^\s*virtual void TakeDamage\(int damage_\) override;') {
        $outLines += "    /*"
        $outLines += "     * 敵キャラクターにダメージを与える。"
        $outLines += "     * [入力] damage: 受けるダメージ量"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] HPを減らし、0以下になったらOnDeathを呼ぶ"
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
    } elseif ($line -match '^\s*void OnDeath\(\);') {
        $outLines += "    /*"
        $outLines += "     * 敵の死亡時処理を行う（スコアやXP付与）。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] 削除フラグが立ち、プレイヤーにXPが付与される"
        $outLines += "     */"
        $outLines += "    void OnDeath();"
    } elseif ($line -match '^\s*void UpdateAttackPattern\(\);') {
        $outLines += "    /*"
        $outLines += "     * 敵タイプに応じた攻撃パターンを毎フレーム更新する。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] タイマーに応じて弾が生成される"
        $outLines += "     */"
        $outLines += "    void UpdateAttackPattern();"
    } else {
        $outLines += $line
    }
}
[System.IO.File]::WriteAllLines($file, $outLines, [System.Text.Encoding]::GetEncoding(932))
