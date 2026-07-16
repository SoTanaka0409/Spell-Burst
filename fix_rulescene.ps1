# RuleScene.h - fix garbled comments
$file = 'Source\RuleScene.h'
$lines = [System.IO.File]::ReadAllLines($file, [System.Text.Encoding]::GetEncoding(932))
$outLines = @()
foreach ($line in $lines) {
    if ($line -match '^\s*//') { continue }
    if ($line -match '^\s*void Initialize\(\) override;') {
        $outLines += "    /*"
        $outLines += "     * 各スライド（画像）を読み込み配列に格納する。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] rule_graphs_に画像が読み込まれる"
        $outLines += "     */"
        $outLines += "    void Initialize() override;"
    } elseif ($line -match '^\s*void Update\(\) override;') {
        $outLines += "    /*"
        $outLines += "     * 左右キーでスライドを切り替え、ZキーまたはE最終スライドでStageSelectSceneへ遷移する。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] current_slide_が更新され、シーン遷移が起きる場合がある"
        $outLines += "     */"
        $outLines += "    void Update() override;"
    } elseif ($line -match '^\s*void Draw\(\) override;') {
        $outLines += "    /*"
        $outLines += "     * 現在選択されているルールのスライド画像と、ナビゲーションテキストを描画する。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] 画面に描画される"
        $outLines += "     */"
        $outLines += "    void Draw() override;"
    } elseif ($line -match '^\s*void Finalize\(\) override;') {
        $outLines += "    /*"
        $outLines += "     * 読み込んだ全てのスライド画像を解放する。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] メモリが解放される"
        $outLines += "     */"
        $outLines += "    void Finalize() override;"
    } else {
        $outLines += $line
    }
}
[System.IO.File]::WriteAllLines($file, $outLines, [System.Text.Encoding]::GetEncoding(932))
