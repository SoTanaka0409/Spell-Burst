$file = 'Source\Object2D.h'
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
    
    if ($lines[$i] -match '^\s*Object2D\(Vector2 init_pos\);') {
        $outLines += "    Object2D(Vector2 initPos);"
    } elseif ($lines[$i] -match '^\s*virtual void Update\(\);') {
        $outLines += "    /*"
        $outLines += "     * オブジェクトの位置や状態をフレームごとに更新する（派生クラスで実装）。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] オブジェクトの状態が更新される"
        $outLines += "     */"
        $outLines += "    virtual void Update();"
    } elseif ($lines[$i] -match '^\s*virtual void Draw\(\);') {
        $outLines += "    /*"
        $outLines += "     * オブジェクトのグラフィックを画面に描画する（派生クラスで実装）。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] 画面に描画される"
        $outLines += "     */"
        $outLines += "    virtual void Draw();"
    } elseif ($lines[$i] -match '^\s*virtual void OnEnter\(Collider\* collider_, Collider\* check\);') {
        $outLines += "    /*"
        $outLines += "     * コライダー同士が接触を開始した瞬間に呼び出されるイベントハンドラ。"
        $outLines += "     * [入力] collider: 自身のコライダー, check: 相手のコライダー"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] 派生クラスによって接触時の処理が実行される"
        $outLines += "     */"
        $outLines += "    virtual void OnEnter(Collider* collider, Collider* check);"
    } elseif ($lines[$i] -match '^\s*virtual void OnTrigger\(Collider\* collider_, Collider\* check\);') {
        $outLines += "    /*"
        $outLines += "     * コライダー同士が接触している間に毎フレーム呼び出されるイベントハンドラ。"
        $outLines += "     * [入力] collider: 自身のコライダー, check: 相手のコライダー"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] 派生クラスによって継続的な接触処理が実行される"
        $outLines += "     */"
        $outLines += "    virtual void OnTrigger(Collider* collider, Collider* check);"
    } elseif ($lines[$i] -match '^\s*virtual void OnExit\(Collider\* collider_, Collider\* check\);') {
        $outLines += "    /*"
        $outLines += "     * コライダー同士が離脱した瞬間に呼び出されるイベントハンドラ。"
        $outLines += "     * [入力] collider: 自身のコライダー, check: 相手のコライダー"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] 派生クラスによって離脱時の処理が実行される"
        $outLines += "     */"
        $outLines += "    virtual void OnExit(Collider* collider, Collider* check);"
    } else {
        $outLines += $lines[$i]
    }
    $i++
}

[System.IO.File]::WriteAllLines($file, $outLines, [System.Text.Encoding]::GetEncoding(932))
