$file = 'Source\CapsuleCollider.h'
$lines = [System.IO.File]::ReadAllLines($file, [System.Text.Encoding]::GetEncoding(932))
$outLines = @()

foreach ($line in $lines) {
    if ($line -match '^\s*CapsuleCollider\(Object2D\* parent, Vector2 pos1, Vector2 pos2, float radius_\);') {
        $outLines += "    /*"
        $outLines += "     * カプセルコライダーの初期化を行う。"
        $outLines += "     * [入力] parent: 親オブジェクト, pos1: 始点, pos2: 終点, radius: 半径"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] コライダーのパラメータが設定され、管理リストに登録される"
        $outLines += "     */"
        $outLines += "    CapsuleCollider(Object2D* parent, Vector2 pos1, Vector2 pos2, float radius);"
    } elseif ($line -match '^\s*void Update\(Collider\* check\) override;') {
        $outLines += "    /*"
        $outLines += "     * 他のコライダーとのカプセル衝突判定を行う。"
        $outLines += "     * [入力] check: 判定対象のコライダー"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] 衝突が検知された場合、親クラスのHitCheckを呼び出す"
        $outLines += "     */"
        $outLines += "    void Update(Collider* check) override;"
    } elseif ($line -match '^\s*void Draw\(\) override;') {
        $outLines += "    /*"
        $outLines += "     * カプセル形状をデバッグ用に描画する。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] 画面に描画される"
        $outLines += "     */"
        $outLines += "    void Draw() override;"
    } elseif ($line -match '^\s*//ww') {
        continue
    } else {
        $outLines += $line
    }
}
[System.IO.File]::WriteAllLines($file, $outLines, [System.Text.Encoding]::GetEncoding(932))
