$file = 'Source\SceneManager.h'
$lines = [System.IO.File]::ReadAllLines($file, [System.Text.Encoding]::GetEncoding(932))
$outLines = @()

foreach ($line in $lines) {
    $l = $line
    $l = $l -replace '\bSCENE_TYPE\b', 'SceneType'
    $l = $l -replace '\bSCENE_NONE\b', 'kSceneNone'
    $l = $l -replace '\bSCENE_RESET\b', 'kSceneReset'
    $l = $l -replace '\bSCENE_NAME\b', 'kSceneName'
    $l = $l -replace '\bSCENE_TITLE\b', 'kSceneTitle'
    $l = $l -replace '\bSCENE_OPERATION\b', 'kSceneOperation'
    $l = $l -replace '\bSCENE_RULE\b', 'kSceneRule'
    $l = $l -replace '\bSCENE_TUTORIAL\b', 'kSceneTutorial'
    $l = $l -replace '\bSCENE_LEVEL\b', 'kSceneLevel'
    $l = $l -replace '\bSCENE_GAME\b', 'kSceneGame'
    $l = $l -replace '\bSCENE_3DHARD\b', 'kScene3dHard'
    $l = $l -replace '\bSCENE_RESULT\b', 'kSceneResult'
    $l = $l -replace '\bSCENE_RESULTWIN\b', 'kSceneResultWin'
    $l = $l -replace '\bSCENE_NORMALRESULTSCENE\b', 'kSceneNormalResultScene'
    $l = $l -replace '\bSCENE_3D\b', 'kScene3d'
    
    $l = $l -replace '\bbool kSceneHard\b', 'bool is_scene_hard_'
    $l = $l -replace '\bbool kSceneNormal\b', 'bool is_scene_normal_'
    
    $l = $l -replace 'SetSceneHard\(bool Hard\)', 'SetSceneHard(bool isHard)'
    $l = $l -replace 'SetSceneNormal\(bool Normal\)', 'SetSceneNormal(bool isNormal)'
    
    $l = $l -replace 'kSceneHard = Hard', 'is_scene_hard_ = isHard'
    $l = $l -replace 'return kSceneHard', 'return is_scene_hard_'
    
    $l = $l -replace 'kSceneNormal=Normal', 'is_scene_normal_ = isNormal'
    $l = $l -replace 'return kSceneNormal', 'return is_scene_normal_'
    
    $outLines += $l
}

[System.IO.File]::WriteAllLines($file, $outLines, [System.Text.Encoding]::GetEncoding(932))
