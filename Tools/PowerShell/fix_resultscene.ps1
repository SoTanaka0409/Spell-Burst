# ResultScene.h - fix garbled comments, apply naming conventions
$file = 'Source\ResultScene.h'
$lines = [System.IO.File]::ReadAllLines($file, [System.Text.Encoding]::GetEncoding(932))
$outLines = @()
foreach ($line in $lines) {
    if ($line -match '^\s*//') { continue }
    # Fix struct members  
    if ($line -match '\s*float vx_, vy_;') {
        $outLines += "    float vx_;"
        $outLines += "    float vy_;"
    } elseif ($line -match '\s*float angle;') {
        $outLines += "    float angle_;"
    } elseif ($line -match '\s*float rot_speed;') {
        $outLines += "    float rot_speed_;"
    } elseif ($line -match '\s*int life;') {
        $outLines += "    int life_;"
    } elseif ($line -match '^\s*void Initialize\(\) override;') {
        $outLines += "    /*"
        $outLines += "     * パーティクルの初期化、背景・自機画像の読み込みを行う。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] リソースが確保される"
        $outLines += "     */"
        $outLines += "    void Initialize() override;"
    } elseif ($line -match '^\s*void Update\(\) override;') {
        $outLines += "    /*"
        $outLines += "     * パーティクルの更新、およびキー入力でタイトルへの遷移処理を行う。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] タイマーが進み、シーン遷移が起きる場合がある"
        $outLines += "     */"
        $outLines += "    void Update() override;"
    } elseif ($line -match '^\s*void Draw\(\) override;') {
        $outLines += "    /*"
        $outLines += "     * 結果に応じて背景、テキスト、自機画像（敗北or喜び）、パーティクルを描画する。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] 画面に描画される"
        $outLines += "     */"
        $outLines += "    void Draw() override;"
    } elseif ($line -match '^\s*void Finalize\(\) override;') {
        $outLines += "    /*"
        $outLines += "     * 読み込んだ画像リソースを解放する。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] メモリが解放される"
        $outLines += "     */"
        $outLines += "    void Finalize() override;"
    } elseif ($line -match '^\s*void DrawOutlinedString\(') {
        $outLines += "    /*"
        $outLines += "     * 指定された座標に縁取り付きの文字列を描画するヘルパー関数。"
        $outLines += "     * [入力] x, y: 描画座標, str: 文字列, color: 文字色, outlineColor: 縁色, fontHandle: フォント"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] 画面に描画される"
        $outLines += "     */"
        $outLines += "    void DrawOutlinedString(int x, int y, const char* str, unsigned int color, unsigned int outlineColor, int fontHandle);"
    } else {
        $outLines += $line
    }
}
[System.IO.File]::WriteAllLines($file, $outLines, [System.Text.Encoding]::GetEncoding(932))

# ResultScene.cpp - fix struct member names
$file2 = 'Source\ResultScene.cpp'
$content2 = [System.IO.File]::ReadAllText($file2, [System.Text.Encoding]::GetEncoding(932))
$content2 = $content2 -replace '\b\.vx_\b', '.vx_'
$content2 = $content2 -replace '\b\.vy_\b', '.vy_'
$content2 = $content2 -replace '\.angle\b', '.angle_'
$content2 = $content2 -replace '\.rot_speed\b', '.rot_speed_'
$content2 = $content2 -replace '\.life\b', '.life_'
$content2 = $content2 -replace 'DrawOutlinedString\(int x, int y, const char\* str, unsigned int color_, unsigned int outline_color, int font_handle\)', 'DrawOutlinedString(int x, int y, const char* str, unsigned int color, unsigned int outlineColor, int fontHandle)'
$content2 = $content2 -replace '\boutline_color\b', 'outlineColor'
$content2 = $content2 -replace '\bfont_handle\b', 'fontHandle'
[System.IO.File]::WriteAllText($file2, $content2, [System.Text.Encoding]::GetEncoding(932))
