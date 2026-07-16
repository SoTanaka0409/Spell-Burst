# GameScene.h - fix garbled comments, apply naming conventions to static variables
$file = 'Source\GameScene.h'
$lines = [System.IO.File]::ReadAllLines($file, [System.Text.Encoding]::GetEncoding(932))
$outLines = @()

foreach ($line in $lines) {
    if ($line -match '^\s*//') { continue }
    if ($line -match '\s*static int currentStage;') {
        $outLines += "    static int current_stage_;          // 現在プレイ中のステージ番号"
    } elseif ($line -match '\s*static int playFrameCount;') {
        $outLines += "    static int play_frame_count_;        // プレイ開始からの経過フレーム数（スコアやタイムアタック用）"
    } elseif ($line -match '\s*static bool isTimeAttackActive;') {
        $outLines += "    static bool is_time_attack_active_;  // タイムアタックモードが有効かどうかのフラグ"
    } elseif ($line -match '^\s*GameScene\(\);') {
        $outLines += "    /*"
        $outLines += "     * オブジェクトの生成・破棄を行う（実際の初期化処理はInitializeで実行）。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] メンバーが初期化される"
        $outLines += "     */"
        $outLines += "    GameScene();"
    } elseif ($line -match '^\s*void Initialize\(\) override;') {
        $outLines += "    /*"
        $outLines += "     * マネージャーの生成、各種リソース（画像やサウンド）の確保、タイマーの初期化を行う。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] ゲーム開始に必要なリソースが確保される"
        $outLines += "     */"
        $outLines += "    void Initialize() override;"
    } elseif ($line -match '^\s*void Update\(\) override;') {
        $outLines += "    /*"
        $outLines += "     * ヒットストップ適用時は各オブジェクト（敵、弾、壁など）の状態を更新し、遷移条件を処理する。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] ゲーム全体の状態が進行する"
        $outLines += "     */"
        $outLines += "    void Update() override;"
    } elseif ($line -match '^\s*void Draw\(\) override;') {
        $outLines += "    /*"
        $outLines += "     * オフスクリーン(screen_handle_)に一度描画した後、画面揺れのズレを加算してメイン画面へ転送する。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] 画面に描画される"
        $outLines += "     */"
        $outLines += "    void Draw() override;"
    } elseif ($line -match '^\s*void Finalize\(\) override;') {
        $outLines += "    /*"
        $outLines += "     * 確保したマネージャーやリソースを解放し、メモリリークを防ぐ。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] リソースが解放される"
        $outLines += "     */"
        $outLines += "    void Finalize() override;"
    } elseif ($line -match '^\s*void TriggerCutin\(\);') {
        $outLines += "    /*"
        $outLines += "     * ボスのスペルカード発動時やボス出現時などのカットイン演出タイマーを起動する。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] cutin_timer_が設定される"
        $outLines += "     */"
        $outLines += "    void TriggerCutin();"
    } elseif ($line -match '^\s*void AddScreenShake\(int duration, float magnitude\);') {
        $outLines += "    /*"
        $outLines += "     * 画面揺れタイマーを設定し、現在の残量を上書き適用する（強烈な衝突や大爆発時に使用）。"
        $outLines += "     * [入力] duration: 揺らすフレーム数, magnitude: 揺れの強さ"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] shake_timer_とshake_magnitude_が更新される"
        $outLines += "     */"
        $outLines += "    void AddScreenShake(int duration, float magnitude);"
    } elseif ($line -match '^\s*void AddHitStop\(int duration\);') {
        $outLines += "    /*"
        $outLines += "     * 強い爆発が起きたなど、ゲーム全体の更新処理を一時停止（ヒットストップ）させ、臨場感を演出する。"
        $outLines += "     * [入力] duration: 停止フレーム数"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] hit_stop_timer_が設定される"
        $outLines += "     */"
        $outLines += "    void AddHitStop(int duration);"
    } elseif ($line -match '^\s*void AddDamageFlash\(int duration, unsigned int color\);') {
        $outLines += "    /*"
        $outLines += "     * 画面を指定色でフラッシュさせ、ダメージや爆発の視覚的フィードバックを演出する。"
        $outLines += "     * [入力] duration: フラッシュするフレーム数, color: フラッシュ色"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] damage_flash_timer_とdamage_flash_color_が設定される"
        $outLines += "     */"
        $outLines += "    void AddDamageFlash(int duration, unsigned int color);"
    } else {
        $outLines += $line
    }
}
[System.IO.File]::WriteAllLines($file, $outLines, [System.Text.Encoding]::GetEncoding(932))

# GameScene.cpp - apply static variable renames
$file2 = 'Source\GameScene.cpp'
$content2 = [System.IO.File]::ReadAllText($file2, [System.Text.Encoding]::GetEncoding(932))
$content2 = $content2 -replace '\bGameScene::currentStage\b', 'GameScene::current_stage_'
$content2 = $content2 -replace '\bcurrentStage\b', 'current_stage_'
$content2 = $content2 -replace '\bGameScene::playFrameCount\b', 'GameScene::play_frame_count_'
$content2 = $content2 -replace '\bplayFrameCount\b', 'play_frame_count_'
$content2 = $content2 -replace '\bGameScene::isTimeAttackActive\b', 'GameScene::is_time_attack_active_'
$content2 = $content2 -replace '\bisTimeAttackActive\b', 'is_time_attack_active_'
[System.IO.File]::WriteAllText($file2, $content2, [System.Text.Encoding]::GetEncoding(932))

# Fix other files referencing the GameScene statics
$otherFiles = @('Source\HUD.cpp', 'Source\HUD.h', 'Source\EnemyManager.cpp', 'Source\ResultScene.cpp')
foreach ($path in $otherFiles) {
    if (Test-Path $path) {
        $c = [System.IO.File]::ReadAllText($path, [System.Text.Encoding]::GetEncoding(932))
        $c = $c -replace '\bGameScene::currentStage\b', 'GameScene::current_stage_'
        $c = $c -replace '\bGameScene::playFrameCount\b', 'GameScene::play_frame_count_'
        $c = $c -replace '\bGameScene::isTimeAttackActive\b', 'GameScene::is_time_attack_active_'
        $c = $c -replace '\bcurrentStage\b', 'current_stage_'
        $c = $c -replace '\bplayFrameCount\b', 'play_frame_count_'
        $c = $c -replace '\bisTimeAttackActive\b', 'is_time_attack_active_'
        [System.IO.File]::WriteAllText($path, $c, [System.Text.Encoding]::GetEncoding(932))
    }
}
