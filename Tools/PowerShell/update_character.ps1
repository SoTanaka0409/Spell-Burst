
$file = "Source\Character.h"
$c = [System.IO.File]::ReadAllText($file, [System.Text.Encoding]::GetEncoding(932))
$c = $c -replace "virtual void Kill\(\);", "virtual void Kill();`r`n`r`n    /*`r`n     * キャラクター死亡時の演出処理を行う（派生クラスでオーバーライドする）。`r`n     * [入力] なし`r`n     * [出力] なし`r`n     * [副作用] サウンド再生やパーティクル生成、スコア加算など`r`n     */`r`n    virtual void OnDeath();"
[System.IO.File]::WriteAllText($file, $c, [System.Text.Encoding]::GetEncoding(932))

$fileCpp = "Source\Character.cpp"
$cCpp = [System.IO.File]::ReadAllText($fileCpp, [System.Text.Encoding]::GetEncoding(932))
$cCpp = $cCpp -replace "if \(hp_ == 0\)\s*\{\s*Kill\(\);\s*\}", "if (hp_ == 0)`r`n    {`r`n        OnDeath();`r`n        Kill();`r`n    }"
$cCpp += "`r`nvoid Character::OnDeath()`r`n{`r`n    // デフォルトは何もしない。派生クラスで演出を実装。`r`n}`r`n"
[System.IO.File]::WriteAllText($fileCpp, $cCpp, [System.Text.Encoding]::GetEncoding(932))

