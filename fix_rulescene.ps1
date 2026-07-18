
$file = "Source\RuleScene.cpp"
$c = [System.IO.File]::ReadAllText($file, [System.Text.Encoding]::UTF8)

$replacement = @"
    const char* titles[] =
    {
        "1. キャラクターの選択",
        "2. 難易度の選択",
        "3. 敵を倒してレベルを上げ、ボスを倒せ！",
        "4. UIの説明",
        "5. バリアの使い方",
        "6. ボスのHPは3段階！"
    };
    const char* descs1[] =
    {
        "タイトル画面から「GAME START」を選択後、3人の中から好きなキャラクターを選ぼう！",
        "自分の腕前に合わせた難易度を選ぼう。NORMAL, HARD, VERY HARDがあるぞ。",
        "敵を倒して経験値を稼ごう。敵はウェーブ制で出現し、最後にボスが登場するぞ。",
        "画面左上には自分のHPやレベルが、",
        "バリア展開中に敵の弾を受けると弾き返すことができるぞ！",
        "ボスのHPは3回回復するぞ！"
    };
    const char* descs2[] =
    {
        "",
        "",
        "レベルが上がると攻撃力がアップし、より強力な弾を撃てるようになるぞ！",
        "右下にはボスのHPゲージが表示されるぞ！",
        "ここぞというタイミングでバリアを展開してピンチを切り抜けよう！",
        "最後まで油断せずに戦おう！"
    };
    const char* descs3[] =
    {
        "※現在選択中のキャラクターの色は少し暗く表示されます。",
        "",
        "",
        "",
        "",
        ""
    };
"@

$c = $c -replace "(?s)const char\* titles\[\] =.*?const char\* descs3\[\] =\s*\{[^}]*\};", $replacement
[System.IO.File]::WriteAllText($file, $c, [System.Text.Encoding]::UTF8)

