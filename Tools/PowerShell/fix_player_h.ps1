$file = 'Source\Player.h'
$c = [System.IO.File]::ReadAllText($file, [System.Text.Encoding]::GetEncoding(932))
$c = $c -replace 'private:\s+float attack_power_;', "private:
    float attack_power_;"
[System.IO.File]::WriteAllText($file, $c, [System.Text.Encoding]::GetEncoding(932))
