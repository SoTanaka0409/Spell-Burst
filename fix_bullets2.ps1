# EnemyBullet.h
$file = 'Source\EnemyBullet.h'
$lines = [System.IO.File]::ReadAllLines($file, [System.Text.Encoding]::GetEncoding(932))
$outLines = @()
foreach ($line in $lines) {
    if ($line -match '^\s*//') { continue }
    if ($line -match 'EnemyBullet\(Vector2 pos, Vector2 dir, float speed_, bool can_reflect_ = false, bool is_stun_bullet_ = false, int homingFrames = 0, int homingDelayFrames = 0\)') {
        $outLines += "    /*"
        $outLines += "     * 敵弾を初期化する。直進・反射・スタン・ホーミングなど多様な属性をサポートする。"
        $outLines += "     * [入力] pos: 初期座標, dir: 進行方向, speed: 速度, canReflect: 反射弾か, isStun: スタン弾か, homingFrames: 追尾フレーム数, homingDelayFrames: 追尾開始遅延"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] コライダーが生成される"
        $outLines += "     */"
        $outLines += "    EnemyBullet(Vector2 pos, Vector2 dir, float speed, bool canReflect = false, bool isStunBullet = false, int homingFrames = 0, int homingDelayFrames = 0);"
    } elseif ($line -match '    void Update\(\) override;') {
        $outLines += "    /*"
        $outLines += "     * 弾の座標を更新し、追尾処理や画面端での反射・消滅判定を行う。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] 座標が更新され、必要に応じて弾が消滅する"
        $outLines += "     */"
        $outLines += "    void Update() override;"
    } elseif ($line -match '    void Draw\(\) override;') {
        $outLines += "    /*"
        $outLines += "     * 弾の画像やエフェクトを描画する。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] 画面に描画される"
        $outLines += "     */"
        $outLines += "    void Draw() override;"
    } elseif ($line -match '    virtual void OnTrigger\(Collider\* collider, Collider\* check\) override;') {
        $outLines += "    /*"
        $outLines += "     * プレイヤーやバリアとの衝突時にダメージ付与や弾消し処理を行う。"
        $outLines += "     * [入力] collider: 自身のコライダー, check: 相手のコライダー"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] 相手にダメージが入り、弾が削除される"
        $outLines += "     */"
        $outLines += "    virtual void OnTrigger(Collider* collider, Collider* check) override;"
    } else {
        $outLines += $line
    }
}
[System.IO.File]::WriteAllLines($file, $outLines, [System.Text.Encoding]::GetEncoding(932))

# EnemyBullet.cpp
$file2 = 'Source\EnemyBullet.cpp'
$content2 = [System.IO.File]::ReadAllText($file2, [System.Text.Encoding]::GetEncoding(932))
$content2 = $content2 -replace 'EnemyBullet\(Vector2 pos, Vector2 dir, float speed_, bool can_reflect_, bool is_stun_bullet_, int homingFrames, int homingDelayFrames\)', 'EnemyBullet(Vector2 pos, Vector2 dir, float speed, bool canReflect, bool isStunBullet, int homingFrames, int homingDelayFrames)'
$content2 = $content2 -replace 'Projectile\(pos, dir_, speed_, 10\)', 'Projectile(pos, dir, speed, 10)'
$content2 = $content2 -replace 'can_reflect_\(can_reflect_\)', 'can_reflect_(canReflect)'
$content2 = $content2 -replace 'is_stun_bullet_\(is_stun_bullet_\)', 'is_stun_bullet_(isStunBullet)'
$content2 = $content2 -replace 'has_reflected_\(false\)', 'has_reflected_(false)'
[System.IO.File]::WriteAllText($file2, $content2, [System.Text.Encoding]::GetEncoding(932))

# PlayerHomingBullet.h/.cpp
$file3 = 'Source\PlayerHomingBullet.h'
$content3 = [System.IO.File]::ReadAllText($file3, [System.Text.Encoding]::GetEncoding(932))
$content3 = $content3 -replace 'PlayerHomingBullet\(Vector2 pos, Vector2 dir, float speed_\)', 'PlayerHomingBullet(Vector2 pos, Vector2 dir, float speed)'
[System.IO.File]::WriteAllText($file3, $content3, [System.Text.Encoding]::GetEncoding(932))

$file4 = 'Source\PlayerHomingBullet.cpp'
$content4 = [System.IO.File]::ReadAllText($file4, [System.Text.Encoding]::GetEncoding(932))
$content4 = $content4 -replace 'PlayerHomingBullet\(Vector2 pos, Vector2 dir, float speed_\)', 'PlayerHomingBullet(Vector2 pos, Vector2 dir, float speed)'
$content4 = $content4 -replace 'Projectile\(pos, dir, speed_, 10\)', 'Projectile(pos, dir, speed, 10)'
[System.IO.File]::WriteAllText($file4, $content4, [System.Text.Encoding]::GetEncoding(932))
