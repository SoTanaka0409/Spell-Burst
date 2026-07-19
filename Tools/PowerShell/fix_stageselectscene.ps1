# StageSelectScene.h - add comments
$file = 'Source\StageSelectScene.h'
$lines = [System.IO.File]::ReadAllLines($file, [System.Text.Encoding]::GetEncoding(932))
$outLines = @()
foreach ($line in $lines) {
    if ($line -match '^\s*void Initialize\(\) override;') {
        $outLines += "    /*"
        $outLines += "     * キャラクター・ステージ選択UIの初期化を行う。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] UIリソースが確保される"
        $outLines += "     */"
        $outLines += "    void Initialize() override;"
    } elseif ($line -match '^\s*void Update\(\) override;') {
        $outLines += "    /*"
        $outLines += "     * マウス入力に応じてキャラクター選択とステージ選択フェーズを更新する。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] phase_が変わりシーン遷移が起きる場合がある"
        $outLines += "     */"
        $outLines += "    void Update() override;"
    } elseif ($line -match '^\s*void Draw\(\) override;') {
        $outLines += "    /*"
        $outLines += "     * 現在のphase_に応じてキャラクター選択かステージ選択のUIを描画する。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] 画面に描画される"
        $outLines += "     */"
        $outLines += "    void Draw() override;"
    } elseif ($line -match '^\s*void Finalize\(\) override;') {
        $outLines += "    /*"
        $outLines += "     * 読み込んだリソースを解放する。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] メモリが解放される"
        $outLines += "     */"
        $outLines += "    void Finalize() override;"
    } elseif ($line -match '^\s*void DrawButton\(int x, int y, int w, int h, const char\* text, bool hover, int color_, int font24\);') {
        $outLines += "    /*"
        $outLines += "     * UIボタンをホバー状態に応じて色を変えて描画するヘルパー関数。"
        $outLines += "     * [入力] x, y: 位置, w, h: サイズ, text: テキスト, hover: ホバー中か, color: 色, font24: フォント"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] 画面に描画される"
        $outLines += "     */"
        $outLines += "    void DrawButton(int x, int y, int w, int h, const char* text, bool hover, int color, int font24);"
    } elseif ($line -match '\s*int phase_;') {
        $outLines += "    int phase_;          // 0: キャラクター選択, 1: ステージ選択"
    } else {
        $outLines += $line
    }
}
[System.IO.File]::WriteAllLines($file, $outLines, [System.Text.Encoding]::GetEncoding(932))

# StageSelectScene.cpp - fix color_ param name
$file2 = 'Source\StageSelectScene.cpp'
$content2 = [System.IO.File]::ReadAllText($file2, [System.Text.Encoding]::GetEncoding(932))
$content2 = $content2 -replace 'StageSelectScene::DrawButton\(int x, int y, int w, int h, const char\* text, bool hover, int color_, int font24\)', 'StageSelectScene::DrawButton(int x, int y, int w, int h, const char* text, bool hover, int color, int font24)'
$content2 = $content2 -replace '(?<![a-zA-Z_])color_(?![a-zA-Z_])', 'color'
[System.IO.File]::WriteAllText($file2, $content2, [System.Text.Encoding]::GetEncoding(932))
