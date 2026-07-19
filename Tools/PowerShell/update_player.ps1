
$fileH = "Source\Player.h"
$cH = [System.IO.File]::ReadAllText($fileH, [System.Text.Encoding]::GetEncoding(932))
$cH = $cH -replace "void OnDeath\(\);", "virtual void OnDeath() override;"
[System.IO.File]::WriteAllText($fileH, $cH, [System.Text.Encoding]::GetEncoding(932))

