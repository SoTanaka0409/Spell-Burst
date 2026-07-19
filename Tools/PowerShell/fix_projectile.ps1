# Projectile.h fix
$file = 'Source\Projectile.h'
$lines = [System.IO.File]::ReadAllLines($file, [System.Text.Encoding]::GetEncoding(932))
$outLines = @()

$i = 0
while ($i -lt $lines.Length) {
    if ($lines[$i] -match '^\s*//\s*\[.*?\]') {
        while ($i -lt $lines.Length -and $lines[$i] -match '^\s*//') { $i++ }
    }
    if ($lines[$i] -match '    Vector2 dir;') {
        $outLines += "    Vector2 dir_;              // 進行方向（正規化ベクトル）または移動ベクトル"
    } elseif ($lines[$i] -match 'Projectile\(Vector2 pos, Vector2 dir, float speed_, int damage_\)') {
        $outLines += "    /*"
        $outLines += "     * 弾の初期化を行う。"
        $outLines += "     * [入力] pos: 初期座標, dir: 進行方向, speed: 速度, damage: ダメージ"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] コライダーが生成される"
        $outLines += "     */"
        $outLines += "    Projectile(Vector2 pos, Vector2 dir, float speed, int damage);"
    } elseif ($lines[$i] -match '^\s*virtual void Update\(\) override;') {
        $outLines += "    /*"
        $outLines += "     * 弾の座標やコライダーの位置を毎フレーム更新する。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] コライダーの座標が更新される"
        $outLines += "     */"
        $outLines += "    virtual void Update() override;"
    } elseif ($lines[$i] -match '^\s*virtual void Kill\(\);') {
        $outLines += "    /*"
        $outLines += "     * 弾を無効化し、自身とコライダーの削除フラグを立てる。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] is_active_がfalseになり削除される"
        $outLines += "     */"
        $outLines += "    virtual void Kill();"
    } elseif ($lines[$i] -match '^\s*bool IsOutOfBounds\(float margin = 50.0f\) const;') {
        $outLines += "    /*"
        $outLines += "     * 弾が画面外に出たかを判定する。"
        $outLines += "     * [入力] margin: 判定のゆとりマージン"
        $outLines += "     * [出力] 画面外に出たかどうか"
        $outLines += "     * [副作用] なし"
        $outLines += "     */"
        $outLines += "    bool IsOutOfBounds(float margin = 50.0f) const;"
    } elseif ($lines[$i] -match '    Vector2 GetDir\(\)') {
        $outLines += "    Vector2 GetDir() const { return dir_; }"
    } elseif ($lines[$i] -match '    void SetDir\(Vector2 dir\)') {
        $outLines += "    void SetDir(Vector2 dir) { dir_ = dir; }"
    } else {
        $outLines += $lines[$i]
    }
    $i++
}
[System.IO.File]::WriteAllLines($file, $outLines, [System.Text.Encoding]::GetEncoding(932))

# Projectile.cpp fix
$file2 = 'Source\Projectile.cpp'
$content2 = [System.IO.File]::ReadAllText($file2, [System.Text.Encoding]::GetEncoding(932))
$content2 = $content2 -replace 'Projectile\(Vector2 pos, Vector2 dir, float speed_, int damage_\)', 'Projectile(Vector2 pos, Vector2 dir, float speed, int damage)'
$content2 = $content2 -replace 'speed_\(speed_\)', 'speed_(speed)'
$content2 = $content2 -replace 'damage_\(damage_\)', 'damage_(damage)'
$content2 = $content2 -replace 'dir\(dir\)', 'dir_(dir)'
$content2 = $content2 -replace '\bdir\b(?!_)', 'dir_'
[System.IO.File]::WriteAllText($file2, $content2, [System.Text.Encoding]::GetEncoding(932))
