
$file = "Source\Enemy.cpp"
$c = [System.IO.File]::ReadAllText($file, [System.Text.Encoding]::GetEncoding(932))
$c = $c -replace "#include `"Utility.h`"", "#include `"Utility.h`"`r`n#include `"BulletFactory.h`"`r`n#include `"EffectManager.h`""

# Particle replacement
$c = $c -replace "(?s)for \(int i = 0; i < 20; i\+\+\)\s*\{\s*float speed_ = 1\.0f \+ static_cast<float>\(rand\(\) % 30\) / 10\.0f;\s*float angle = static_cast<float>\(rand\(\) % 360\) \* 3\.14159f / 180\.0f;\s*int life = 20 \+ rand\(\) % 20;\s*float size_ = 5\.0f \+ static_cast<float>\(rand\(\) % 15\);\s*int color_ = GetColor\(255, 50 \+ rand\(\) % 100, 0\);\s*ObjectManager::Instantiate<ExplosionParticle>\(position_\.x, position_\.y, speed_, angle, color_, life, size_\);\s*\}", "EffectManager::SpawnExplosion(position_, 20, GetColor(255, 100, 0), 15.0f, 4.0f);"

# NWay Bullet
$c = $c -replace "(?s)for \(int i = -1; i <= 1; i\+\+\)\s*\{\s*float angle = baseAngle \+ \(i \* 15\.0f \* 3\.14159f / 180\.0f\);\s*ObjectManager::Instantiate<EnemyBullet>\(position_, Vector2::FromAngle\(angle\), 3\.5f\);\s*\}", "BulletFactory::SpawnNWayBullets(position_, baseAngle, 3, 30.0f * DX_PI_F / 180.0f, 3.5f);"

[System.IO.File]::WriteAllText($file, $c, [System.Text.Encoding]::GetEncoding(932))

