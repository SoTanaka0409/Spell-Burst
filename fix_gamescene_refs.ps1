$files = @('Source\Boss.cpp', 'Source\BossStateAttack.cpp', 'Source\EnemyManager.cpp', 'Source\EnemyBullet.cpp', 'Source\Player.cpp', 'Source\GameScene.cpp')
foreach ($path in $files) {
    if (Test-Path $path) {
        $c = [System.IO.File]::ReadAllText($path, [System.Text.Encoding]::GetEncoding(932))
        $c = $c -replace '\bGameScene::currentStage\b', 'GameScene::current_stage_'
        $c = $c -replace '\bGameScene::playFrameCount\b', 'GameScene::play_frame_count_'
        $c = $c -replace '\bGameScene::isTimeAttackActive\b', 'GameScene::is_time_attack_active_'
        # In case they use without class scope:
        $c = $c -replace '\bcurrentStage\b', 'current_stage_'
        $c = $c -replace '\bplayFrameCount\b', 'play_frame_count_'
        $c = $c -replace '\bisTimeAttackActive\b', 'is_time_attack_active_'
        [System.IO.File]::WriteAllText($path, $c, [System.Text.Encoding]::GetEncoding(932))
    }
}
