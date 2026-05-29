$enc = [System.Text.Encoding]::GetEncoding("shift_jis")
$path = "Source\Player.h"
$content = [System.IO.File]::ReadAllText($path, $enc)
$content = $content.Replace("float m_attackTimer{};", "float m_attackTimer;")
$content = $content.Replace("float m_AttackInterval{};", "float m_AttackInterval;")
$content = $content.Replace("float m_AttackTimer_2{};", "float m_AttackTimer_2;")
$content = $content.Replace("float m_AttackInterval_2{};", "float m_AttackInterval_2;")
$content = $content.Replace("float m__BarrierCount{};", "float m__BarrierCount;")
[System.IO.File]::WriteAllText($path, $content, $enc)
Write-Host "Updated Player.h"
