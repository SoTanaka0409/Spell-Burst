
$fileH = "Source\Boss.h"
$cH = [System.IO.File]::ReadAllText($fileH, [System.Text.Encoding]::GetEncoding(932))
$cH = $cH -replace "void UpdateDamage\(\);", "virtual void OnDeath() override;"
[System.IO.File]::WriteAllText($fileH, $cH, [System.Text.Encoding]::GetEncoding(932))

$fileCpp = "Source\Boss.cpp"
$cCpp = [System.IO.File]::ReadAllText($fileCpp, [System.Text.Encoding]::GetEncoding(932))
$cCpp = $cCpp -replace "UpdateDamage\(\);", "OnDeath();"
$cCpp = $cCpp -replace "void Boss::UpdateDamage\(\)", "void Boss::OnDeath()"
$cCpp = $cCpp -replace "Character::TakeDamage\(damage\);", "hp_ = std::clamp(hp_ - damage, 0, max_hp_);"
[System.IO.File]::WriteAllText($fileCpp, $cCpp, [System.Text.Encoding]::GetEncoding(932))

