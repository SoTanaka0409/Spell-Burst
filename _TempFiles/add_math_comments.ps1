function Add-Math-Comment {
    param (
        [string]$Path,
        [string]$Target,
        [string]$Comment
    )
    if (Test-Path $Path) {
        $content = [System.IO.File]::ReadAllText($Path, [System.Text.Encoding]::UTF8)
        
        $content = $content -replace '(?m)[ \t]*//.*$', ''
        
        $content = $content.Replace($Target, "`r`n    // $Comment`r`n    $Target")
        
        [System.IO.File]::WriteAllText($Path, $content, [System.Text.Encoding]::GetEncoding(932))
    }
}

Add-Math-Comment "Source\PlayerHomingBullet.cpp" "float tx = target->GetPosition().x - m_x;" "atan2を用いて目標地点への角度を求め、現在の進行角度を徐々にターゲットへ近づける旋回ベクトル計算"
Add-Math-Comment "Source\PlayerHomingBullet.cpp" "float seed = (m_x + m_y) * 0.01f;" "sin/cosとシード値を用いて、不規則に変形しながら回転する3つの頂点座標（三角形）を算出する"

Add-Math-Comment "Source\EnemyBullet.cpp" "float tx = px - mvPosition.x;" "自機の座標へ向かうベクトルを算出し、atan2で角度を求めて追尾させるホーミング計算"

Add-Math-Comment "Source\Boss.cpp" "float angle = (3.14159f * 2.0f / bulletCount) * i;" "360度または扇状に広がる弾幕の射出角度（ラジアン）を円周率から均等に分割計算"
Add-Math-Comment "Source\Boss.cpp" "float length = std::sqrt(dx * dx + dy * dy);" "自機へのベクトルを三平方の定理で求め、長さを1に正規化して一定速度の弾にする"
Add-Math-Comment "Source\Boss.cpp" "m_targetX = 100.0f + static_cast<float>(rand() % (800 - 200));" "ボスの次の移動先として、画面内に収まるランダムな座標を決定する"

Add-Math-Comment "Source\ExplosionParticle.cpp" "m_vx = speed * std::cos(angle);" "角度と速度から、X/Y方向の移動速度ベクトル（初期初速）をsin/cosで算出"

Add-Math-Comment "Source\RainbowBullet.cpp" "float waveOffset = std::sin(m_time * 0.1f) * m_amplitude;" "進行方向に対して垂直なサイン波（波打つ軌道）のオフセット計算"

Add-Math-Comment "Source\Player.cpp" "float startX = mvPosition.x - (numBullets - 1) * spacing / 2.0f;" "現在のレベル(numBullets)に応じて、複数発の弾を横一列に等間隔で配置するためのオフセット計算"

Add-Math-Comment "Source\MasterSpark.cpp" "float lineAngle = std::atan2(m_dy, m_dx);" "極太レーザーの中心軸の角度を求め、当たり判定用カプセルコライダーの始点と終点を計算"
