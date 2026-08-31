
$file = "Source\Obstacle.cpp"
$c = [System.IO.File]::ReadAllText($file, [System.Text.Encoding]::GetEncoding(932))
$c = $c -replace "#include `"Utility.h`"", "#include `"Utility.h`"`r`n#include `"EffectManager.h`""
$c = $c -replace "(?s)for \(int i = 0; i < 5; i\+\+\)\s*\{\s*ObjectManager::Instantiate<ExplosionParticle>\(position_\.x, position_\.y, 2\.0f, static_cast<float>\(rand\(\) % 360\) \* 3\.14159f / 180\.0f, GetColor\(150, 150, 150\), 30, 10\.0f\);\s*\}", "EffectManager::SpawnExplosion(position_, 5, GetColor(150, 150, 150), 10.0f, 2.0f);"
[System.IO.File]::WriteAllText($file, $c, [System.Text.Encoding]::GetEncoding(932))

