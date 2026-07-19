$file = 'Source\InputManager.h'
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
    
    if ($lines[$i] -match '^\s*static int CheckDownKey\(int KeyCode\);') {
        $outLines += "    /*"
        $outLines += "     * キーが押された瞬間かどうかを判定する。"
        $outLines += "     * [入力] keyCode: 確認対象のキーコード"
        $outLines += "     * [出力] キーが押された瞬間だけ1、それ以外は0"
        $outLines += "     * [副作用] 前フレームの状態をバッファに保存する"
        $outLines += "     */"
        $outLines += "    static int CheckDownKey(int keyCode);"
    } elseif ($lines[$i] -match '^\s*static int CheckUpKey\(int KeyCode\);') {
        $outLines += "    /*"
        $outLines += "     * キーが離された瞬間かどうかを判定する。"
        $outLines += "     * [入力] keyCode: 確認対象のキーコード"
        $outLines += "     * [出力] キーが離された瞬間だけ1、それ以外は0"
        $outLines += "     * [副作用] 前フレームの状態をバッファに保存する"
        $outLines += "     */"
        $outLines += "    static int CheckUpKey(int keyCode);"
    } elseif ($lines[$i] -match '^\s*static int CheckPressKey\(int KeyCode\);') {
        $outLines += "    /*"
        $outLines += "     * キーが押されている状態かどうかを判定する。"
        $outLines += "     * [入力] keyCode: 確認対象のキーコード"
        $outLines += "     * [出力] キーが押されている間は1、それ以外は0"
        $outLines += "     * [副作用] なし"
        $outLines += "     */"
        $outLines += "    static int CheckPressKey(int keyCode);"
    } elseif ($lines[$i] -match '^\s*static int ActionDown\(InputAction action\);') {
        $outLines += "    /*"
        $outLines += "     * アクションに対応するキーが押された瞬間か判定する。"
        $outLines += "     * [入力] action: 確認するゲームアクション"
        $outLines += "     * [出力] 押された瞬間だけ1"
        $outLines += "     * [副作用] なし"
        $outLines += "     */"
        $outLines += "    static int ActionDown(InputAction action);"
    } elseif ($lines[$i] -match '^\s*static int ActionPress\(InputAction action\);') {
        $outLines += "    /*"
        $outLines += "     * アクションに対応するキーが押されているか判定する。"
        $outLines += "     * [入力] action: 確認するゲームアクション"
        $outLines += "     * [出力] 押されている間は1"
        $outLines += "     * [副作用] なし"
        $outLines += "     */"
        $outLines += "    static int ActionPress(InputAction action);"
    } elseif ($lines[$i] -match '^\s*static int ActionUp\(InputAction action\);') {
        $outLines += "    /*"
        $outLines += "     * アクションに対応するキーが離された瞬間か判定する。"
        $outLines += "     * [入力] action: 確認するゲームアクション"
        $outLines += "     * [出力] 離された瞬間だけ1"
        $outLines += "     * [副作用] なし"
        $outLines += "     */"
        $outLines += "    static int ActionUp(InputAction action);"
    } else {
        $outLines += $lines[$i]
    }
    $i++
}

[System.IO.File]::WriteAllLines($file, $outLines, [System.Text.Encoding]::GetEncoding(932))
