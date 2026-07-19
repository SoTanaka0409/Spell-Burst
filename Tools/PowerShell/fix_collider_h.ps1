$file = 'Source\Collider.h'
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
    
    if ($lines[$i] -match '^\s*Collider\(Object2D\* parent\);') {
        $outLines += "    /*"
        $outLines += "     * コライダーの初期化と親オブジェクトの登録を行う。"
        $outLines += "     * [入力] parent: このコライダーを所有する親オブジェクト"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] 親オブジェクトのポインタを保持する"
        $outLines += "     */"
        $outLines += "    Collider(Object2D* parent);"
    } elseif ($lines[$i] -match '^\s*virtual void Update\(Collider\* check\);') {
        $outLines += "    /*"
        $outLines += "     * 他のコライダーとの具体的な衝突計算を行う。"
        $outLines += "     * [入力] check: 判定対象となる他のコライダー"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] 衝突が検知された場合、HitCheckを呼び出す"
        $outLines += "     */"
        $outLines += "    virtual void Update(Collider* check);"
    } elseif ($lines[$i] -match '^\s*virtual void Draw\(\);') {
        $outLines += "    /*"
        $outLines += "     * コライダーの形状をデバッグ用に描画する。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] 画面に描画される"
        $outLines += "     */"
        $outLines += "    virtual void Draw();"
    } elseif ($lines[$i] -match '^\s*virtual void OnEnter\(\);') {
        $outLines += "    /*"
        $outLines += "     * 他のコライダーと接触した最初のフレームに呼ばれるイベント。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] 派生クラスの接触処理が実行される"
        $outLines += "     */"
        $outLines += "    virtual void OnEnter();"
    } elseif ($lines[$i] -match '^\s*virtual void OnTrigger\(\);') {
        $outLines += "    /*"
        $outLines += "     * 他のコライダーと接触している間呼ばれるイベント。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] 継続的な接触処理が実行される"
        $outLines += "     */"
        $outLines += "    virtual void OnTrigger();"
    } elseif ($lines[$i] -match '^\s*virtual void OnExit\(\);') {
        $outLines += "    /*"
        $outLines += "     * 他のコライダーとの接触が離れたフレームに呼ばれるイベント。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] 離脱時の処理が実行される"
        $outLines += "     */"
        $outLines += "    virtual void OnExit();"
    } elseif ($lines[$i] -match '^\s*void HitCheck\(Collider\* check, bool isHit\);') {
        $outLines += "    /*"
        $outLines += "     * 衝突状態に応じて衝突リストを更新し、各種イベントを呼び出す。"
        $outLines += "     * [入力] check: 判定対象のコライダー, isHit: 現在衝突しているか"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] collision_list_が更新される"
        $outLines += "     */"
        $outLines += "    void HitCheck(Collider* check, bool isHit);"
    } elseif ($lines[$i] -match '^\s*void RemoveCollision\(Collider\* collider\);') {
        $outLines += "    /*"
        $outLines += "     * 衝突リストから指定されたコライダーを取り除く。"
        $outLines += "     * [入力] collider: 削除するコライダー"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] collision_list_から要素が削除される"
        $outLines += "     */"
        $outLines += "    void RemoveCollision(Collider* collider);"
    } elseif ($lines[$i] -match 'Object2D\* parentObject;') {
        $outLines += "    Object2D* parent_object_;"
    } elseif ($lines[$i] -match 'Vector2 position2;') {
        $outLines += "    Vector2 position2_;"
    } elseif ($lines[$i] -match 'return parentObject;') {
        $outLines += "        return parent_object_;"
    } elseif ($lines[$i] -match 'parentObject = nullptr;') {
        $outLines += "        parent_object_ = nullptr;"
    } else {
        $outLines += $lines[$i]
    }
    $i++
}

[System.IO.File]::WriteAllLines($file, $outLines, [System.Text.Encoding]::GetEncoding(932))
