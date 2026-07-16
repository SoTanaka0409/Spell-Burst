# Scene.h - fix garbled comments
$file = 'Source\Scene.h'
$lines = [System.IO.File]::ReadAllLines($file, [System.Text.Encoding]::GetEncoding(932))
$outLines = @()
foreach ($line in $lines) {
    if ($line -match '^\s*//') { continue }
    if ($line -match '^\s*virtual void Initialize\(\) = 0;') {
        $outLines += "    /*"
        $outLines += "     * シーン開始時に必要なリソース読み込みやオブジェクト生成を行う（派生クラスで実装）。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] シーンのリソースが確保される"
        $outLines += "     */"
        $outLines += "    virtual void Initialize() = 0;"
    } elseif ($line -match '^\s*virtual void Update\(\);') {
        $outLines += "    /*"
        $outLines += "     * オブジェクトのマネージャーおよび衝突判定マネージャーの更新処理を呼ぶ。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] ゲームオブジェクトが更新される"
        $outLines += "     */"
        $outLines += "    virtual void Update();"
    } elseif ($line -match '^\s*virtual void Draw\(\);') {
        $outLines += "    /*"
        $outLines += "     * オブジェクトのマネージャーの描画処理を呼ぶ。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] 画面に描画される"
        $outLines += "     */"
        $outLines += "    virtual void Draw();"
    } elseif ($line -match '^\s*virtual void Finalize\(\) = 0;') {
        $outLines += "    /*"
        $outLines += "     * シーン終了時に画像や音などのリソース解放を行う（派生クラスで実装）。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] リソースが解放される"
        $outLines += "     */"
        $outLines += "    virtual void Finalize() = 0;"
    } else {
        $outLines += $line
    }
}
[System.IO.File]::WriteAllLines($file, $outLines, [System.Text.Encoding]::GetEncoding(932))

# HUD.h - apply naming conventions
$file2 = 'Source\HUD.h'
$lines2 = [System.IO.File]::ReadAllLines($file2, [System.Text.Encoding]::GetEncoding(932))
$outLines2 = @()
foreach ($line in $lines2) {
    if ($line -match '^\s*//') { continue }
    if ($line -match '^\s*static void Initialize\(\);') {
        $outLines2 += "    /*"
        $outLines2 += "     * イージング用変数などの静的変数をリセットする。"
        $outLines2 += "     * [入力] なし"
        $outLines2 += "     * [出力] なし"
        $outLines2 += "     * [副作用] 表示比率が初期化される"
        $outLines2 += "     */"
        $outLines2 += "    static void Initialize();"
    } elseif ($line -match '^\s*static void Update\(Player\* player, EnemyManager\* enemy_manager_, Boss\* boss\);') {
        $outLines2 += "    /*"
        $outLines2 += "     * 現在のHPなどに基づき、表示用の比率（イージング）を計算・更新する。"
        $outLines2 += "     * [入力] player: プレイヤー, enemyManager: 敵マネージャー, boss: ボス"
        $outLines2 += "     * [出力] なし"
        $outLines2 += "     * [副作用] displayHpRatio_等が更新される"
        $outLines2 += "     */"
        $outLines2 += "    static void Update(Player* player, EnemyManager* enemyManager, Boss* boss);"
    } elseif ($line -match '^\s*static void Draw\(Player\* player, EnemyManager\* enemy_manager_, Boss\* boss, int cutin_timer_, int cutin_image_handle_\);') {
        $outLines2 += "    /*"
        $outLines2 += "     * 画面最前面に各UIコンポーネント（ゲームUI、カットイン等）を描画する。"
        $outLines2 += "     * [入力] player: プレイヤー, enemyManager: 敵マネージャー, boss: ボス, cutinTimer: カットインタイマー, cutinImageHandle: 画像ハンドル"
        $outLines2 += "     * [出力] なし"
        $outLines2 += "     * [副作用] 画面に描画される"
        $outLines2 += "     */"
        $outLines2 += "    static void Draw(Player* player, EnemyManager* enemyManager, Boss* boss, int cutinTimer, int cutinImageHandle);"
    } elseif ($line -match '\s*static float displayHpRatio;') {
        $outLines2 += "    static float display_hp_ratio_;"
    } elseif ($line -match '\s*static float displayXpRatio;') {
        $outLines2 += "    static float display_xp_ratio_;"
    } elseif ($line -match '\s*static float displaySpellRatio;') {
        $outLines2 += "    static float display_spell_ratio_;"
    } elseif ($line -match '\s*static float displayBarrierRatio;') {
        $outLines2 += "    static float display_barrier_ratio_;"
    } elseif ($line -match '\s*static float bossHpRatio;') {
        $outLines2 += "    static float boss_hp_ratio_;"
    } elseif ($line -match '^\s*static void DrawPlayerStatus\(Player\* player\);') {
        $outLines2 += "    static void DrawPlayerStatus(Player* player);"
    } elseif ($line -match '^\s*static void DrawBossStatus\(Boss\* boss\);') {
        $outLines2 += "    static void DrawBossStatus(Boss* boss);"
    } elseif ($line -match '^\s*static void DrawEnemyProgress\(EnemyManager\* enemy_manager_\);') {
        $outLines2 += "    static void DrawEnemyProgress(EnemyManager* enemyManager);"
    } elseif ($line -match '^\s*static void DrawCutin\(int cutin_timer_, int cutin_image_handle_\);') {
        $outLines2 += "    static void DrawCutin(int cutinTimer, int cutinImageHandle);"
    } else {
        $outLines2 += $line
    }
}
[System.IO.File]::WriteAllLines($file2, $outLines2, [System.Text.Encoding]::GetEncoding(932))

# HUD.cpp - fix variable names
$file3 = 'Source\HUD.cpp'
$content3 = [System.IO.File]::ReadAllText($file3, [System.Text.Encoding]::GetEncoding(932))
$content3 = $content3 -replace '\bdisplayHpRatio\b', 'display_hp_ratio_'
$content3 = $content3 -replace '\bdisplayXpRatio\b', 'display_xp_ratio_'
$content3 = $content3 -replace '\bdisplaySpellRatio\b', 'display_spell_ratio_'
$content3 = $content3 -replace '\bdisplayBarrierRatio\b', 'display_barrier_ratio_'
$content3 = $content3 -replace '\bbossHpRatio\b', 'boss_hp_ratio_'
$content3 = $content3 -replace 'HUD::Update\(Player\* player, EnemyManager\* enemy_manager_, Boss\* boss\)', 'HUD::Update(Player* player, EnemyManager* enemyManager, Boss* boss)'
$content3 = $content3 -replace 'HUD::Draw\(Player\* player, EnemyManager\* enemy_manager_, Boss\* boss, int cutin_timer_, int cutin_image_handle_\)', 'HUD::Draw(Player* player, EnemyManager* enemyManager, Boss* boss, int cutinTimer, int cutinImageHandle)'
$content3 = $content3 -replace 'HUD::DrawEnemyProgress\(EnemyManager\* enemy_manager_\)', 'HUD::DrawEnemyProgress(EnemyManager* enemyManager)'
$content3 = $content3 -replace 'HUD::DrawCutin\(int cutin_timer_, int cutin_image_handle_\)', 'HUD::DrawCutin(int cutinTimer, int cutinImageHandle)'
$content3 = $content3 -replace '(?<!\w)enemy_manager_(?!\w)', 'enemyManager'
$content3 = $content3 -replace '(?<!\w)cutin_timer_(?!\w)', 'cutinTimer'
$content3 = $content3 -replace '(?<!\w)cutin_image_handle_(?!\w)', 'cutinImageHandle'
[System.IO.File]::WriteAllText($file3, $content3, [System.Text.Encoding]::GetEncoding(932))
