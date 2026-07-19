$file = 'Source\EnemyManager.h'
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
        $outLines += "     * フェーズ進行状況やタイマーなどの進行を初期化する。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] 各種変数がリセットされる"
        $outLines += "     */"
        $outLines += "    void Initialize();"
    } elseif ($lines[$i] -match '^\s*void Update\(\);') {
        $outLines += "    /*"
        $outLines += "     * タイマーによる敵の生成、ボスの出現、フェーズ移行などを毎フレーム処理する。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] 敵が生成されたりフェーズが進む"
        $outLines += "     */"
        $outLines += "    void Update();"
    } elseif ($lines[$i] -match '^\s*void Draw\(\);') {
        $outLines += "    /*"
        $outLines += "     * 画面上部に次のフェーズまでの要求撃破数や、ボス出現の警告UIなどを描画する。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] 画面に描画される"
        $outLines += "     */"
        $outLines += "    void Draw();"
    } elseif ($lines[$i] -match '^\s*void DeleteEnemy\(\);') {
        $outLines += "    /*"
        $outLines += "     * 生存している全ての敵（ボス以外）を削除・破棄する。"
        $outLines += "     * [入力] なし"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] オブジェクト管理から敵が削除される"
        $outLines += "     */"
        $outLines += "    void DeleteEnemy();"
    } elseif ($lines[$i] -match '^\s*void SpawnEnemy\(float x, float y\);') {
        $outLines += "    /*"
        $outLines += "     * 指定された座標に基本的な敵オブジェクトを生成し、リストに登録する。"
        $outLines += "     * [入力] x: 生成座標X, y: 生成座標Y"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] 敵がゲーム内にスポーンする"
        $outLines += "     */"
        $outLines += "    void SpawnEnemy(float x, float y);"
    } elseif ($lines[$i] -match '^\s*void SpawnEnemy_Target\(float x, float y, int spawnnum\);') {
        $outLines += "    /*"
        $outLines += "     * ターゲットに向けて発射されるような、特定の動きを持つ敵を生成する。"
        $outLines += "     * [入力] x: 生成座標X, y: 生成座標Y, spawnNum: 生成する数"
        $outLines += "     * [出力] なし"
        $outLines += "     * [副作用] 敵がゲーム内にスポーンする"
        $outLines += "     */"
        $outLines += "    void SpawnEnemy_Target(float x, float y, int spawnNum);"
    } elseif ($lines[$i] -match '^\s*//\s*\[') {
        continue
    } elseif ($lines[$i] -match '^\s*//\s*---') {
        continue
    } else {
        $outLines += $lines[$i]
    }
    $i++
}
[System.IO.File]::WriteAllLines($file, $outLines, [System.Text.Encoding]::GetEncoding(932))

$file2 = 'Source\EnemyManager.cpp'
$content2 = [System.IO.File]::ReadAllText($file2, [System.Text.Encoding]::GetEncoding(932))
$content2 = $content2 -replace 'SpawnEnemy_Target\(float x, float y, int spawnnum\)', 'SpawnEnemy_Target(float x, float y, int spawnNum)'
$content2 = $content2 -replace 'for \(int i = 0; i < spawnnum; i\+\+\)', 'for (int i = 0; i < spawnNum; i++)'
[System.IO.File]::WriteAllText($file2, $content2, [System.Text.Encoding]::GetEncoding(932))
