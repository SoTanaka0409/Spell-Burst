$file = 'Source\Object2D.cpp'
$content = [System.IO.File]::ReadAllText($file, [System.Text.Encoding]::GetEncoding(932))
$content = $content -replace 'Object2D::Object2D\(Vector2 init_pos\)', 'Object2D::Object2D(Vector2 initPos)'
$content = $content -replace 'position_\(init_pos\)', 'position_(initPos)'
$content = $content -replace 'Object2D::OnEnter\(Collider\* collider_, Collider\* check\)', 'Object2D::OnEnter(Collider* collider, Collider* check)'
$content = $content -replace 'Object2D::OnTrigger\(Collider\* collider_, Collider\* check\)', 'Object2D::OnTrigger(Collider* collider, Collider* check)'
$content = $content -replace 'Object2D::OnExit\(Collider\* collider_, Collider\* check\)', 'Object2D::OnExit(Collider* collider, Collider* check)'
[System.IO.File]::WriteAllText($file, $content, [System.Text.Encoding]::GetEncoding(932))
