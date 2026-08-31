
$file = "Source\Boss.cpp"
$c = [System.IO.File]::ReadAllText($file, [System.Text.Encoding]::GetEncoding(932))
$c = $c -replace "#include `"Utility.h`"", "#include `"Utility.h`"`r`n#include `"BulletFactory.h`"`r`n#include `"EffectManager.h`""

# ShootSpiralBarrage
$c = $c -replace "(?s)for \(int i = 0; i < bulletCount; i\+\+\)\s*\{\s*float angle = spiralAngle \+ \(i \* 2\.0f \* PI\) / bulletCount;\s*ObjectManager::Instantiate<EnemyBullet>\(position_, Vector2::FromAngle\(angle\), 2\.5f, reflect\);\s*\}", "BulletFactory::SpawnCircleBullets(position_, spiralAngle, bulletCount, 2.5f, reflect);"

# ShootFanBarrage
$c = $c -replace "(?s)for \(int i = -bulletCount/2; i <= bulletCount/2; i\+\+\)\s*\{\s*float angle = baseAngle \+ \(i \* 8\.0f \* PI / 180\.0f\);\s*ObjectManager::Instantiate<EnemyBullet>\(position_, Vector2::FromAngle\(angle\), speed_, reflect\);\s*\}", "BulletFactory::SpawnNWayBullets(position_, baseAngle, bulletCount % 2 == 0 ? bulletCount + 1 : bulletCount, (bulletCount - 1) * 8.0f * DX_PI_F / 180.0f, speed_, reflect);"

# ShootBossAttack1
$c = $c -replace "(?s)for \(int i = -2; i <= 2; i\+\+\)\s*\{\s*float angle = baseAngle \+ \(i \* 5\.0f \* PI / 180\.0f\);\s*ObjectManager::Instantiate<EnemyBullet>\(position_, Vector2::FromAngle\(angle\), 3\.5f\);\s*\}", "BulletFactory::SpawnNWayBullets(position_, baseAngle, 5, 20.0f * DX_PI_F / 180.0f, 3.5f);"
$c = $c -replace "(?s)for \(int i = -1; i <= 1; i\+\+\)\s*\{\s*float angle = baseAngle \+ \(i \* 12\.0f \* PI / 180\.0f\);\s*ObjectManager::Instantiate<EnemyBullet>\(position_, Vector2::FromAngle\(angle\), 2\.5f\);\s*\}", "BulletFactory::SpawnNWayBullets(position_, baseAngle, 3, 24.0f * DX_PI_F / 180.0f, 2.5f);"

# ShootBossAttack2
$c = $c -replace "(?s)for \(int i = 0; i < 5; i\+\+\)\s*\{\s*float angle = baseAngle \+ \(i \* 360\.0f / 5\.0f \* PI / 180\.0f\);\s*ObjectManager::Instantiate<EnemyBullet>\(position_, Vector2::FromAngle\(angle\), 3\.5f, false, false, 120, 60\);\s*\}", "BulletFactory::SpawnCircleBullets(position_, baseAngle, 5, 3.5f, false, false, 120, 60);"

# ShootBossAttack3
$c = $c -replace "(?s)for \(int i = 0; i < 6; i\+\+\)\s*\{\s*float angle = \(i \* 2\.0f \* PI\) / 6\.0f;\s*ObjectManager::Instantiate<EnemyBullet>\(position_, Vector2::FromAngle\(angle\), 4\.5f, true\);\s*\}", "BulletFactory::SpawnCircleBullets(position_, 0.0f, 6, 4.5f, true);"

# ShootBossAttack4
$c = $c -replace "(?s)for \(int i = 0; i < 24; i\+\+\)\s*\{\s*float angle = \(i \* 2\.0f \* PI\) / 24\.0f;\s*ObjectManager::Instantiate<EnemyBullet>\(position_, Vector2::FromAngle\(angle\), 2\.0f, true\);\s*\}", "BulletFactory::SpawnCircleBullets(position_, 0.0f, 24, 2.0f, true);"
$c = $c -replace "(?s)for \(int i = 0; i < 12; i\+\+\)\s*\{\s*float angle = \(i \* 2\.0f \* PI\) / 12\.0f \+ 0\.5f;\s*ObjectManager::Instantiate<EnemyBullet>\(position_, Vector2::FromAngle\(angle\), 5\.0f, false\);\s*\}", "BulletFactory::SpawnCircleBullets(position_, 0.5f, 12, 5.0f, false);"

# Update ExplosionParticles
$c = $c -replace "(?s)float size_ = 15\.0f \+ static_cast<float>\(rand\(\) % 40\);\s*int color_ = GetColor\(255, 100 \+ rand\(\) % 155, 0\);\s*ObjectManager::Instantiate<ExplosionParticle>\(position_\.x, position_\.y, speed_, angle, color_, life, size_\);", ""
$c = $c -replace "(?s)for \(int i = 0; i < 30; i\+\+\)\s*\{[^}]*\}", "EffectManager::SpawnExplosion(position_, 30, GetColor(255, 150, 0), 30.0f, 5.0f);"

[System.IO.File]::WriteAllText($file, $c, [System.Text.Encoding]::GetEncoding(932))

