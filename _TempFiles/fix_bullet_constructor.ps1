$enc = [System.Text.Encoding]::GetEncoding("shift_jis")
$path = "Source\Bullet.h"
$content = [System.IO.File]::ReadAllText($path, $enc)
$content = $content.Replace("Bullet(float x, float y,float damage);", "Bullet(float x, float y, int damage);")
[System.IO.File]::WriteAllText($path, $content, $enc)
Write-Host "Updated Bullet.h"
