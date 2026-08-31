$file = 'Source\SceneManager.cpp'
$content = [System.IO.File]::ReadAllText($file, [System.Text.Encoding]::GetEncoding(932))
$content = $content -replace '\bkSceneHard\b', 'is_scene_hard_'
$content = $content -replace '\bkSceneNormal\b', 'is_scene_normal_'
[System.IO.File]::WriteAllText($file, $content, [System.Text.Encoding]::GetEncoding(932))
