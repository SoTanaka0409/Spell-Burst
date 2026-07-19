$file = 'Source\ColliderManager.h'
$lines = [System.IO.File]::ReadAllLines($file, [System.Text.Encoding]::GetEncoding(932))
$outLines = @()

$i = 0
while ($i -lt $lines.Length) {
    if ($lines[$i] -match '^\s*//') {
        # skip all // lines
        while ($i -lt $lines.Length -and $lines[$i] -match '^\s*//') {
            $i++
        }
    }
    
    if ($lines[$i] -match '^\s*void Update\(\);') {
        $outLines += "    /*"
        $outLines += "     * 管理している全コライダーの衝突判定を行う。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] 衝突が発生した場合、各コライダーのイベントが発火する"
        $outLines += "     */"
        $outLines += "    void Update();"
    } elseif ($lines[$i] -match '^\s*void Draw\(\);') {
        $outLines += "    /*"
        $outLines += "     * 管理している全コライダーのデバッグ描画を行う。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] 画面にコライダーの形状が描画される"
        $outLines += "     */"
        $outLines += "    void Draw();"
    } elseif ($lines[$i] -match '^\s*void AddCollider\(Collider\* Collider\);') {
        $outLines += "    /*"
        $outLines += "     * 新しいコライダーを管理リストに追加する。"
        $outLines += "     * [入力] collider: 追加するコライダー"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] collider_list_に追加される"
        $outLines += "     */"
        $outLines += "    void AddCollider(Collider* collider);"
    } elseif ($lines[$i] -match '^\s*void DeleteAllCollider\(\);') {
        $outLines += "    /*"
        $outLines += "     * 全てのコライダーをリストから削除し、メモリを解放する。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] collider_list_が空になる"
        $outLines += "     */"
        $outLines += "    void DeleteAllCollider();"
    } elseif ($lines[$i] -match '^\s*void DeleteAllColliderIfNeeded\(\);') {
        $outLines += "    /*"
        $outLines += "     * 削除フラグが立っているコライダーをリストから除外し、破棄する。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] 該当するコライダーがメモリから解放される"
        $outLines += "     */"
        $outLines += "    void DeleteAllColliderIfNeeded();"
    } elseif ($lines[$i] -match '^\s*void RemoveCollider\(Collider\* collider\);') {
        $outLines += "    /*"
        $outLines += "     * 指定されたコライダーを管理リストから除外する（破棄はしない）。"
        $outLines += "     * [入力] collider: 削除するコライダー"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] collider_list_から要素が削除される"
        $outLines += "     */"
        $outLines += "    void RemoveCollider(Collider* collider);"
    } elseif ($lines[$i] -match 'Instance') {
        $outLines += ($lines[$i] -replace 'Instance', 'instance_')
    } else {
        $outLines += $lines[$i]
    }
    $i++
}
[System.IO.File]::WriteAllLines($file, $outLines, [System.Text.Encoding]::GetEncoding(932))

$file2 = 'Source\ColliderManager.cpp'
$content2 = [System.IO.File]::ReadAllText($file2, [System.Text.Encoding]::GetEncoding(932))
$content2 = $content2 -replace '\bInstance\b', 'instance_'
$content2 = $content2 -replace 'ColliderManager::AddCollider\(Collider\* Collider\)', 'ColliderManager::AddCollider(Collider* collider)'
$content2 = $content2 -replace 'collider_list_\.push_back\(Collider\);', 'collider_list_.push_back(collider);'
[System.IO.File]::WriteAllText($file2, $content2, [System.Text.Encoding]::GetEncoding(932))
