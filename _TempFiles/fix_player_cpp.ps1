$enc = [System.Text.Encoding]::GetEncoding("shift_jis")
$path = "Source\Player.cpp"
$content = [System.IO.File]::ReadAllText($path, $enc)
$content = $content.Replace("new Bullet(startX + i * spacing, mvPosition.y - 45.0f, mfAttack);", "new Bullet(startX + i * spacing, mvPosition.y - 45.0f, static_cast<int>(mfAttack));")
[System.IO.File]::WriteAllText($path, $content, $enc)
Write-Host "Updated Player.cpp"
