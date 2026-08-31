$file = 'Source\SphereCollider.h'
$lines = [System.IO.File]::ReadAllLines($file, [System.Text.Encoding]::GetEncoding(932))
$outLines = @()

foreach ($line in $lines) {
    if ($line -match '^\s*SphereCollider\(Object2D\* parent, Vector2 center, float radius_\);') {
        $outLines += "    /*"
        $outLines += "     * 球形コライダーの初期化を行う。"
        $outLines += "     * [入力] parent: 親オブジェクト, center: 中心座標, radius: 半径"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] コライダーのパラメータが設定され、管理リストに登録される"
        $outLines += "     */"
        $outLines += "    SphereCollider(Object2D* parent, Vector2 center, float radius);"
    } elseif ($line -match '^\s*void Update\(Collider\* check\) override;') {
        $outLines += "    /*"
        $outLines += "     * 他のコライダーとの球形衝突判定を行う。"
        $outLines += "     * [入力] check: 判定対象のコライダー"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] 衝突が検知された場合、親クラスのHitCheckを呼び出す"
        $outLines += "     */"
        $outLines += "    void Update(Collider* check) override;"
    } elseif ($line -match '^\s*void Draw\(\) override;') {
        $outLines += "    /*"
        $outLines += "     * 円形をデバッグ用に描画する。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] 画面に描画される"
        $outLines += "     */"
        $outLines += "    void Draw() override;"
    } else {
        $outLines += $line
    }
}
[System.IO.File]::WriteAllLines($file, $outLines, [System.Text.Encoding]::GetEncoding(932))
