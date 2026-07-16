# Obstacle.h add comments
$file = 'Source\Obstacle.h'
$lines = [System.IO.File]::ReadAllLines($file, [System.Text.Encoding]::GetEncoding(932))
$outLines = @()
foreach ($line in $lines) {
    if ($line -match '^\s*virtual void OnTrigger\(Collider\* collider, Collider\* check\) override;') {
        $outLines += "    /*"
        $outLines += "     * プレイヤー等と接触中に毎フレーム呼ばれる。岩のダメージ処理。"
        $outLines += "     * [入力] collider: 自身のコライダー, check: 相手のコライダー"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] プレイヤーにダメージが入る"
        $outLines += "     */"
        $outLines += "    virtual void OnTrigger(Collider* collider, Collider* check) override;"
    } elseif ($line -match '^\s*virtual void OnEnter\(Collider\* collider, Collider\* check\) override;') {
        $outLines += "    /*"
        $outLines += "     * コライダーに接触した瞬間に呼ばれる（接触開始イベント）。"
        $outLines += "     * [入力] collider: 自身のコライダー, check: 相手のコライダー"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] 接触した相手の種類に応じた初期処理が行われる"
        $outLines += "     */"
        $outLines += "    virtual void OnEnter(Collider* collider, Collider* check) override;"
    } else {
        $outLines += $line
    }
}
[System.IO.File]::WriteAllLines($file, $outLines, [System.Text.Encoding]::GetEncoding(932))

# Barrier.h: apply naming conventions
$file2 = 'Source\Barrier.h'
$lines2 = [System.IO.File]::ReadAllLines($file2, [System.Text.Encoding]::GetEncoding(932))
$outLines2 = @()
foreach ($line in $lines2) {
    if ($line -match '^\s*//') { continue }
    if ($line -match 'Barrier\(float x, float y, float radius_, Object2D::Tag2D obj\)') {
        $outLines2 += "    /*"
        $outLines2 += "     * バリアオブジェクトを初期化する。"
        $outLines2 += "     * [入力] x: 座標X, y: 座標Y, radius: 半径, obj: タグ種別"
        $outLines2 += "     * [出力] なし"
        $outLines2 += "     * [副作用] コライダーが生成され管理リストに登録される"
        $outLines2 += "     */"
        $outLines2 += "    Barrier(float x, float y, float radius, Object2D::Tag2D obj);"
    } elseif ($line -match '^\s*virtual void Update\(\) override;') {
        $outLines2 += "    /*"
        $outLines2 += "     * バリアの展開カウントダウン、コライダーの有無を管理する。"
        $outLines2 += "     * [入力] なし"
        $outLines2 += "     * [出力] なし"
        $outLines2 += "     * [副作用] タイマーが更新されコライダーが生成・削除される"
        $outLines2 += "     */"
        $outLines2 += "    virtual void Update() override;"
    } elseif ($line -match '^\s*virtual void Draw\(\) override;') {
        $outLines2 += "    /*"
        $outLines2 += "     * バリアのエフェクトを描画する（isDeployed=trueの時のみ）。"
        $outLines2 += "     * [入力] なし"
        $outLines2 += "     * [出力] なし"
        $outLines2 += "     * [副作用] 画面に描画される"
        $outLines2 += "     */"
        $outLines2 += "    virtual void Draw() override;"
    } elseif ($line -match '^\s*virtual void OnTrigger\(Collider\* collider, Collider\* check\) override;') {
        $outLines2 += "    /*"
        $outLines2 += "     * 敵の弾と衝突した際、その弾を防ぎhit_count_を加算する。"
        $outLines2 += "     * [入力] collider: 自身のコライダー, check: 相手のコライダー"
        $outLines2 += "     * [出力] なし"
        $outLines2 += "     * [副作用] hit_count_が更新される"
        $outLines2 += "     */"
        $outLines2 += "    virtual void OnTrigger(Collider* collider, Collider* check) override;"
    } elseif ($line -match '    int GetHitCount\(\) const { return hit_count; }') {
        $outLines2 += "    int GetHitCount() const { return hit_count_; }"
    } elseif ($line -match '    bool IsDeployed\(\) const { return isDeployed; }') {
        $outLines2 += "    bool IsDeployed() const { return is_deployed_; }"
    } elseif ($line -match '    void SetDeployInterval\(float v\) { deployInterval = v; }') {
        $outLines2 += "    void SetDeployInterval(float v) { deploy_interval_ = v; }"
    } elseif ($line -match '    void SetActiveDuration\(float v\) { activeDuration = v; }') {
        $outLines2 += "    void SetActiveDuration(float v) { active_duration_ = v; }"
    } elseif ($line -match '\s*float deployInterval;') {
        $outLines2 += "    float deploy_interval_;"
    } elseif ($line -match '\s*float activeDuration;') {
        $outLines2 += "    float active_duration_;"
    } elseif ($line -match '\s*float timer;') {
        $outLines2 += "    float timer_;"
    } elseif ($line -match '\s*float radius_;') {
        $outLines2 += "    float radius_;"
    } elseif ($line -match '\s*bool isDeployed;') {
        $outLines2 += "    bool is_deployed_;"
    } elseif ($line -match '\s*int hit_count;') {
        $outLines2 += "    int hit_count_;"
    } else {
        $outLines2 += $line
    }
}
[System.IO.File]::WriteAllLines($file2, $outLines2, [System.Text.Encoding]::GetEncoding(932))

# Barrier.cpp
$file3 = 'Source\Barrier.cpp'
$content3 = [System.IO.File]::ReadAllText($file3, [System.Text.Encoding]::GetEncoding(932))
$content3 = $content3 -replace '\bdeploy_interval_\b', 'deploy_interval_'
$content3 = $content3 -replace '\bdeployInterval\b', 'deploy_interval_'
$content3 = $content3 -replace '\bactiveDuration\b', 'active_duration_'
$content3 = $content3 -replace '\btimer\b(?!_)', 'timer_'
$content3 = $content3 -replace '\bisDeployed\b', 'is_deployed_'
$content3 = $content3 -replace '\bhit_count\b(?!_)', 'hit_count_'
$content3 = $content3 -replace 'Barrier\(float x, float y, float radius_, Object2D::Tag2D obj\)', 'Barrier(float x, float y, float radius, Object2D::Tag2D obj)'
$content3 = $content3 -replace 'radius_\(radius_\)', 'radius_(radius)'
[System.IO.File]::WriteAllText($file3, $content3, [System.Text.Encoding]::GetEncoding(932))
