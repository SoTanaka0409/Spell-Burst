
$file = "Source\Character.cpp"
$c = [System.IO.File]::ReadAllText($file, [System.Text.Encoding]::GetEncoding(932))
$c = $c -replace "if \(hp_ == 0\)`r`n    \{`r`n        OnDeath\(\);`r`n        Kill\(\);`r`n    \}", "if (hp_ == 0)`r`n    {`r`n        OnDeath();`r`n    }"
$c = $c -replace "void Character::OnDeath\(\)`r`n\{`r`n    // デフォルトは何もしない。派生クラスで演出を実装。`r`n\}", "void Character::OnDeath()`r`n{`r`n    Kill(); // デフォルトでは自身を破棄する`r`n}"
[System.IO.File]::WriteAllText($file, $c, [System.Text.Encoding]::GetEncoding(932))

