$files = Get-ChildItem -Path Source -Include *.cpp -Recurse
foreach ($file in $files) {
    $c = [System.IO.File]::ReadAllText($file.FullName, [System.Text.Encoding]::GetEncoding(932))
    if ($c -match 'currentStage|playFrameCount|isTimeAttackActive') {
        $c = $c -replace '\bGameScene::currentStage\b', 'GameScene::current_stage_'
        $c = $c -replace '\bGameScene::playFrameCount\b', 'GameScene::play_frame_count_'
        $c = $c -replace '\bGameScene::isTimeAttackActive\b', 'GameScene::is_time_attack_active_'
        $c = $c -replace '(?<!\w)currentStage(?!\w)', 'current_stage_'
        $c = $c -replace '(?<!\w)playFrameCount(?!\w)', 'play_frame_count_'
        $c = $c -replace '(?<!\w)isTimeAttackActive(?!\w)', 'is_time_attack_active_'
        [System.IO.File]::WriteAllText($file.FullName, $c, [System.Text.Encoding]::GetEncoding(932))
    }
}
