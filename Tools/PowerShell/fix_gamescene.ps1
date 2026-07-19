
$file = "Source\GameScene.cpp"
$c = [System.IO.File]::ReadAllText($file, [System.Text.Encoding]::GetEncoding(932))
$c = $c -replace "void EnemyManager::DrawBackground\(\)", "void GameScene::DrawBackground()"
[System.IO.File]::WriteAllText($file, $c, [System.Text.Encoding]::GetEncoding(932))

