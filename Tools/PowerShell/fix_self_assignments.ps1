$file1 = 'Source\Barrier.cpp'
$c1 = [System.IO.File]::ReadAllText($file1, [System.Text.Encoding]::GetEncoding(932))
$c1 = $c1 -replace 'this->radius_ = radius_;', 'this->radius_ = radius;'
[System.IO.File]::WriteAllText($file1, $c1, [System.Text.Encoding]::GetEncoding(932))

$file2 = 'Source\Enemy.cpp'
$c2 = [System.IO.File]::ReadAllText($file2, [System.Text.Encoding]::GetEncoding(932))
$c2 = $c2 -replace 'this->enemy_type_ = enemy_type_;', 'this->enemy_type_ = enemyType;'
[System.IO.File]::WriteAllText($file2, $c2, [System.Text.Encoding]::GetEncoding(932))
