
$fileH = "Source\Enemy.h"
$cH = [System.IO.File]::ReadAllText($fileH, [System.Text.Encoding]::GetEncoding(932))
$cH = $cH -replace "\s*virtual void TakeDamage\(int damage\) override;", ""
$cH = $cH -replace "void OnDeath\(\);", "virtual void OnDeath() override;"
[System.IO.File]::WriteAllText($fileH, $cH, [System.Text.Encoding]::GetEncoding(932))

$fileCpp = "Source\Enemy.cpp"
$cCpp = [System.IO.File]::ReadAllText($fileCpp, [System.Text.Encoding]::GetEncoding(932))
$cCpp = $cCpp -replace "(?s)void Enemy::TakeDamage\(int damage\).*?void Enemy::OnDeath\(\)", "void Enemy::OnDeath()"
[System.IO.File]::WriteAllText($fileCpp, $cCpp, [System.Text.Encoding]::GetEncoding(932))

