$files = Get-ChildItem -Path Source -Include *.cpp,*.h -Recurse
$replacements = @{
    '\bSCENE_TYPE\b' = 'SceneType'
    '\bSCENE_NONE\b' = 'kSceneNone'
    '\bSCENE_RESET\b' = 'kSceneReset'
    '\bSCENE_NAME\b' = 'kSceneName'
    '\bSCENE_TITLE\b' = 'kSceneTitle'
    '\bSCENE_OPERATION\b' = 'kSceneOperation'
    '\bSCENE_RULE\b' = 'kSceneRule'
    '\bSCENE_TUTORIAL\b' = 'kSceneTutorial'
    '\bSCENE_LEVEL\b' = 'kSceneLevel'
    '\bSCENE_GAME\b' = 'kSceneGame'
    '\bSCENE_3DHARD\b' = 'kScene3dHard'
    '\bSCENE_RESULT\b' = 'kSceneResult'
    '\bSCENE_RESULTWIN\b' = 'kSceneResultWin'
    '\bSCENE_NORMALRESULTSCENE\b' = 'kSceneNormalResultScene'
    '\bSCENE_3D\b' = 'kScene3d'
}

foreach ($file in $files) {
    $content = [System.IO.File]::ReadAllText($file.FullName, [System.Text.Encoding]::GetEncoding(932))
    $changed = $false
    foreach ($key in $replacements.Keys) {
        if ($content -match $key) {
            $content = $content -replace $key, $replacements[$key]
            $changed = $true
        }
    }
    if ($changed) {
        [System.IO.File]::WriteAllText($file.FullName, $content, [System.Text.Encoding]::GetEncoding(932))
    }
}
