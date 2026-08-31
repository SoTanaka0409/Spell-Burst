# MeleeAttack.h - fix garbled comments and add proper ones
$file = 'Source\MeleeAttack.h'
$lines = [System.IO.File]::ReadAllLines($file, [System.Text.Encoding]::GetEncoding(932))
$outLines = @()
foreach ($line in $lines) {
    if ($line -match '^\s*//') { continue }
    if ($line -match '^\s*virtual void Update\(\) override;') {
        $outLines += "    /*"
        $outLines += "     * ライフタイマーを更新し、時間切れになったら削除する。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] life_time_が減少し、0になったらKill()を呼ぶ"
        $outLines += "     */"
        $outLines += "    virtual void Update() override;"
    } elseif ($line -match '^\s*virtual void Draw\(\) override;') {
        $outLines += "    /*"
        $outLines += "     * 近接攻撃の範囲エフェクトを描画する。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] 画面に描画される"
        $outLines += "     */"
        $outLines += "    virtual void Draw() override;"
    } elseif ($line -match '^\s*virtual void OnTrigger\(Collider\* collider, Collider\* check\) override;') {
        $outLines += "    /*"
        $outLines += "     * 当たり判定が敵キャラクターと接触した際にダメージを与える。"
        $outLines += "     * [入力] collider: 自身のコライダー, check: 相手のコライダー"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] 敵にダメージが入る"
        $outLines += "     */"
        $outLines += "    virtual void OnTrigger(Collider* collider, Collider* check) override;"
    } else {
        $outLines += $line
    }
}
[System.IO.File]::WriteAllLines($file, $outLines, [System.Text.Encoding]::GetEncoding(932))
