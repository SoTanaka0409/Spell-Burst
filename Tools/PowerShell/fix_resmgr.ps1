$file = 'Source\ResourceManager.h'
$lines = [System.IO.File]::ReadAllLines($file, [System.Text.Encoding]::GetEncoding(932))
$outLines = @()

foreach ($line in $lines) {
    if ($line -match 'std::map.*graphMap;') {
        $outLines += "    std::map<std::string, int> graph_map_;"
    } elseif ($line -match 'std::map.*fontMap;') {
        $outLines += "    std::map<std::pair<int, int>, int> font_map_;"
    } elseif ($line -match '^\s*int GetGraph\(const std::string& path\);') {
        $outLines += "    /*"
        $outLines += "     * 画像のグラフィックハンドルを取得する（キャッシュになければロードする）。"
        $outLines += "     * [入力] path: 画像ファイルのパス"
        $outLines += "     * [出力] グラフィックハンドル"
        $outLines += "     * [副作用] メモリに画像データがロードされ、マップに登録される"
        $outLines += "     */"
        $outLines += "    int GetGraph(const std::string& path);"
    } elseif ($line -match '^\s*int GetFont\(int size_, int thickness\);') {
        $outLines += "    /*"
        $outLines += "     * 指定されたサイズと太さのフォントハンドルを取得する（なければ作成する）。"
        $outLines += "     * [入力] size: フォントのサイズ, thickness: フォントの太さ"
        $outLines += "     * [出力] フォントハンドル"
        $outLines += "     * [副作用] 新しいフォントが作成され、マップに登録される"
        $outLines += "     */"
        $outLines += "    int GetFont(int size, int thickness);"
    } elseif ($line -match '^\s*void ClearAll\(\);') {
        $outLines += "    /*"
        $outLines += "     * ロード済みのすべての画像・フォントメモリを解放する。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] すべてのハンドルが削除され、マップが空になる"
        $outLines += "     */"
        $outLines += "    void ClearAll();"
    } else {
        $outLines += $line
    }
}

[System.IO.File]::WriteAllLines($file, $outLines, [System.Text.Encoding]::GetEncoding(932))
