$file = 'Source\ObjectManager.h'
$lines = [System.IO.File]::ReadAllLines($file, [System.Text.Encoding]::GetEncoding(932))
$outLines = @()

$i = 0
while ($i -lt $lines.Length) {
    if ($lines[$i] -match '^\s*//\s*\[.*?\]') {
        # skip all // lines
        while ($i -lt $lines.Length -and $lines[$i] -match '^\s*//') {
            $i++
        }
    }
    
    # Check if we are at a function declaration that needs a block comment
    if ($lines[$i] -match '^\s*void Draw\(\);') {
        $outLines += "    /*"
        $outLines += "     * 管理リストの全オブジェクトの描画処理を行う。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] 各オブジェクトが画面に描画される"
        $outLines += "     */"
    } elseif ($lines[$i] -match '^\s*void Update\(\);') {
        $outLines += "    /*"
        $outLines += "     * 管理リストの全オブジェクトの更新処理を行う。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] 各オブジェクトの状態が更新される"
        $outLines += "     */"
    } elseif ($lines[$i] -match '^\s*void AddObject\(std::shared_ptr<Object2D> object2D\);') {
        $outLines += "    /*"
        $outLines += "     * 2Dオブジェクトを管理リストに追加する。"
        $outLines += "     * [入力] object2D: 追加するオブジェクトのポインタ"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] リストにオブジェクトが追加される"
        $outLines += "     */"
    } elseif ($lines[$i] -match '^\s*void DeleteAll2D\(\);') {
        $outLines += "    /*"
        $outLines += "     * 全ての2Dオブジェクトを破棄する。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] 管理リストが空になる"
        $outLines += "     */"
    } elseif ($lines[$i] -match '^\s*void DeleteAll2DIfNeeded\(\);') {
        $outLines += "    /*"
        $outLines += "     * 削除フラグが立っているオブジェクトを破棄する。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] 該当するオブジェクトがリストから削除される"
        $outLines += "     */"
    } elseif ($lines[$i] -match '^\s*std::shared_ptr<Object2D> GetObject2DByTag') {
        $outLines += "    /*"
        $outLines += "     * 指定されたタグのオブジェクトを1つ検索して返す。"
        $outLines += "     * [入力] tag: 検索するタグ"
        $outLines += "     * [出力] 該当するオブジェクトのポインタ（なければnullptr）"
        $outLines += "     * [副作用] なし"
        $outLines += "     */"
    } elseif ($lines[$i] -match '^\s*std::vector<std::shared_ptr<Object2D>> GetObject2DListByTag') {
        $outLines += "    /*"
        $outLines += "     * 指定されたタグのオブジェクトを全て検索して返す。"
        $outLines += "     * [入力] tag: 検索するタグ"
        $outLines += "     * [出力] 該当する全オブジェクトのポインタ配列"
        $outLines += "     * [副作用] なし"
        $outLines += "     */"
    }
    
    $outLines += $lines[$i]
    $i++
}

[System.IO.File]::WriteAllLines($file, $outLines, [System.Text.Encoding]::GetEncoding(932))
