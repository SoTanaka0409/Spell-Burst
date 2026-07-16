$file = 'Source\ObjectManager.h'
$lines = [System.IO.File]::ReadAllLines($file, [System.Text.Encoding]::GetEncoding(932))
$outLines = @()

foreach ($line in $lines) {
    if ($line -match '^(\s*size_t GetObjectCount.*)') {
        $outLines += "    // 管理しているオブジェクトの総数を取得する"
        $outLines += $matches[1]
    } elseif ($line -match '^(\s*const std::list.*GetObjectList.*)') {
        $outLines += "    // 全オブジェクトのリストを取得する"
        $outLines += $matches[1]
    } elseif ($line -match '^\s*//\s*\?|^\s*//\s*---') {
        # ignore garbled comments
    } elseif ($line -match '^\s*std::list.*object_2d_list_;') {
        $outLines += "    std::list<std::shared_ptr<Object2D>> object_2d_list_; // 2Dオブジェクトのリスト"
    } elseif ($line -match '^\s*std::weak_ptr.*player_2d_;') {
        $outLines += "    std::weak_ptr<Object2D> player_2d_; // プレイヤーのポインタ"
    } else {
        $outLines += $line
    }
}

[System.IO.File]::WriteAllLines($file, $outLines, [System.Text.Encoding]::GetEncoding(932))
