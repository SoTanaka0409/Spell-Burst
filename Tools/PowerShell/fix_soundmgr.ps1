$file = 'Source\SoundManager.h'
$lines = [System.IO.File]::ReadAllLines($file, [System.Text.Encoding]::GetEncoding(932))
$outLines = @()

$i = 0
while ($i -lt $lines.Length) {
    if ($lines[$i] -match '^\s*//\s*サウンドハンドルを取得') {
        $outLines += "    /*"
        $outLines += "     * サウンドハンドルを取得する（キャッシュになければロードする）。"
        $outLines += "     * [入力] path: 音声ファイルのパス"
        $outLines += "     * [出力] サウンドハンドル"
        $outLines += "     * [副作用] メモリに音声データがロードされ、マップに登録される"
        $outLines += "     */"
        $outLines += "    int GetSound(const std::string& path);"
        $i += 2
        continue
    } elseif ($lines[$i] -match '^\s*//\s*BGMの再生') {
        $outLines += "    /*"
        $outLines += "     * BGMをループ再生する。"
        $outLines += "     * [入力] path: 音声ファイルのパス"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] 現在のBGMが停止し、新しいBGMが再生される"
        $outLines += "     */"
        $outLines += "    void PlayBGM(const std::string& path);"
        $i += 2
        continue
    } elseif ($lines[$i] -match '^\s*//\s*SEの再生') {
        $outLines += "    /*"
        $outLines += "     * SEを単発再生する。"
        $outLines += "     * [入力] path: 音声ファイルのパス"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] SEが再生される"
        $outLines += "     */"
        $outLines += "    void PlaySE(const std::string& path);"
        $i += 2
        continue
    } elseif ($lines[$i] -match '^\s*//\s*BGMの停止') {
        $outLines += "    /*"
        $outLines += "     * 再生中のBGMを停止する。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] BGMの再生が止まる"
        $outLines += "     */"
        $outLines += "    void StopBGM();"
        $i += 2
        continue
    } elseif ($lines[$i] -match '^\s*//\s*すべての音を停止') {
        $outLines += "    /*"
        $outLines += "     * 再生中のすべての音を停止する。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] すべての音声が停止する"
        $outLines += "     */"
        $outLines += "    void StopAll();"
        $i += 2
        continue
    } elseif ($lines[$i] -match '^\s*//\s*すべての音のメモリ解放') {
        $outLines += "    /*"
        $outLines += "     * ロード済みのすべての音声のメモリを解放する。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] すべてのサウンドハンドルが削除され、マップがクリアされる"
        $outLines += "     */"
        $outLines += "    void ClearAll();"
        $i += 2
        continue
    } elseif ($lines[$i] -match 'std::unordered_map.*soundMap;') {
        $outLines += "    std::unordered_map<std::string, int> sound_map_;"
        $i++
        continue
    }
    
    $outLines += $lines[$i]
    $i++
}

[System.IO.File]::WriteAllLines($file, $outLines, [System.Text.Encoding]::GetEncoding(932))
