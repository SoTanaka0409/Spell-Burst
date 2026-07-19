# Main.cpp - clean up garbled Japanese comments, add proper ones
$file = 'Source\Main.cpp'
$lines = [System.IO.File]::ReadAllLines($file, [System.Text.Encoding]::GetEncoding(932))
$outLines = @()
foreach ($line in $lines) {
    if ($line -match '// .*[^\x00-\x7F].*') {
        # Replace garbled comment lines with clean versions based on context
        if ($line -match 'fopen_s') {
            $outLines += $line
        } elseif ($line -match 'AllocConsole') {
            $outLines += $line
        } elseif ($line -match 'SetOutApplicationLogValidFlag') {
            $outLines += $line
        } elseif ($line -match 'SetDrawScreen') {
            $outLines += $line
        } elseif ($line -match 'ProcessMessage') {
            $outLines += $line
        } else {
            continue
        }
    } elseif ($line -match '// .*ログ') {
        $outLines += "    // 起動毎に最新のログを出力するため、既存のログファイルを破棄して初期化"
    } elseif ($line -match '// .*コンソール') {
        $outLines += "    // 開発中の動作確認およびエラー調査を容易にするためコンソールを割り当て"
    } elseif ($line -match '// DxLib') {
        $outLines += "    // DxLibの基本設定および初期化（ログファイル出力を無効化）"
    } elseif ($line -match '// .*ブルバッファリング') {
        $outLines += "    // 描画先を裏画面に設定し、チラつきのないダブルバッファリングを実現"
    } elseif ($line -match '// OS') {
        $outLines += "    // OSのメッセージ処理・ESCキーによる安全な終了を保証するためのメインループ"
    } else {
        $outLines += $line
    }
}
[System.IO.File]::WriteAllLines($file, $outLines, [System.Text.Encoding]::GetEncoding(932))
