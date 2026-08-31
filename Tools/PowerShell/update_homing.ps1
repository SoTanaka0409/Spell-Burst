
$file = "Source\EnemyBullet.cpp"
$c = [System.IO.File]::ReadAllText($file, [System.Text.Encoding]::GetEncoding(932))
$c = $c -replace "(?s)Vector2 targetPos\(player->GetX\(\), player->GetY\(\)\);.*?dir_ = Vector2::FromAngle\(currentAngle \+ diff \* 0\.05f\);", "Vector2 targetPos(player->GetX(), player->GetY());`r`n              dir_ = Utility::CalculateHomingDirection(dir_, position_, targetPos, 0.05f);"
[System.IO.File]::WriteAllText($file, $c, [System.Text.Encoding]::GetEncoding(932))

$file2 = "Source\PlayerHomingBullet.cpp"
$c2 = [System.IO.File]::ReadAllText($file2, [System.Text.Encoding]::GetEncoding(932))
$c2 = $c2 -replace "(?s)Vector2 toTarget = \(closestTarget - position_\)\.Normalized\(\);.*?dir_ = dir_\.Normalized\(\);", "dir_ = Utility::CalculateHomingDirection(dir_, position_, closestTarget, 0.1f);"
[System.IO.File]::WriteAllText($file2, $c2, [System.Text.Encoding]::GetEncoding(932))

