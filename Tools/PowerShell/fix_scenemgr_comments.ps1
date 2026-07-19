$file = 'Source\SceneManager.h'
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
    
    if ($lines[$i] -match '^\s*void Initialize\(\);') {
        $outLines += "    /*"
        $outLines += "     * 最初のシーン（通常はTITLE等）のInitializeを呼び出し初期化する。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] シーンが初期化される"
        $outLines += "     */"
    } elseif ($lines[$i] -match '^\s*void Draw\(\);') {
        $outLines += "    /*"
        $outLines += "     * 現在のシーンのDraw関数を呼び出し、描画処理を委譲する。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] 画面にシーンの要素が描画される"
        $outLines += "     */"
    } elseif ($lines[$i] -match '^\s*void Update\(\);') {
        $outLines += "    /*"
        $outLines += "     * 現在のシーンのUpdate関数を呼び出す。また、次シーンが予約されていれば遷移処理を行う。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] シーンの更新や切り替えが発生する"
        $outLines += "     */"
    } elseif ($lines[$i] -match '^\s*void Finalize\(\);') {
        $outLines += "    /*"
        $outLines += "     * 現在のシーンのFinalizeを呼び出し、メモリを解放する。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] シーンのリソースが解放される"
        $outLines += "     */"
    } elseif ($lines[$i] -match '^\s*void ChangeSceneIfNeeded\(\);') {
        $outLines += "    /*"
        $outLines += "     * next_scene_type_が設定されている場合、旧シーンを破棄して新シーンを生成・初期化する。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] シーンの切り替えが完了する"
        $outLines += "     */"
    } elseif ($lines[$i] -match '^\s*void SetNextScene\(SceneType next\)') {
        $outLines += "    /*"
        $outLines += "     * 次のシーンを予約する。"
        $outLines += "     * [入力] next: 次に遷移したいシーンの種別"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] 次回Update時にシーン遷移が行われる"
        $outLines += "     */"
    }
    
    $outLines += $lines[$i]
    $i++
}

[System.IO.File]::WriteAllLines($file, $outLines, [System.Text.Encoding]::GetEncoding(932))
