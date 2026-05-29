$enc = [System.Text.Encoding]::GetEncoding("shift_jis")

function Replace-InFile {
    param (
        [string]$Path,
        [hashtable]$Replacements
    )
    
    $content = [System.IO.File]::ReadAllText($Path, $enc)
    
    foreach ($old in $Replacements.Keys) {
        $new = $Replacements[$old]
        if ($content -notmatch [regex]::Escape($old)) {
            Write-Host "Warning: Could not find '$old' in $Path"
        }
        $content = $content -replace [regex]::Escape($old), $new
    }
    
    [System.IO.File]::WriteAllText($Path, $content, $enc)
    Write-Host "Updated $Path"
}

# --- Player.h ---
$player_repl = [ordered]@{
    'float m_speed;' = 'float m_speed; // プレイヤーの基本移動速度'
    'int m_hp;' = 'int m_hp; // 現在の体力値（ステータス）'
    'int m_maxHp;' = 'int m_maxHp; // 最大体力値（上限）'
    'float mfAttack;' = 'float mfAttack; // 攻撃力の倍率・ベース値'
    'float m_attackTimer{};' = 'float m_attackTimer{}; // 通常攻撃の発射間隔を管理するタイマー'
    'float m_AttackInterval{};' = 'float m_AttackInterval{}; // 通常攻撃が撃てるようになるまでの必要フレーム数'
    'float m_AttackTimer_2{};' = 'float m_AttackTimer_2{}; // 特殊攻撃（またはサブ攻撃）のタイマー'
    'float m_AttackInterval_2{};' = 'float m_AttackInterval_2{}; // 特殊攻撃のインターバル'
    'float m__BarrierCount{};' = 'float m__BarrierCount{}; // バリアの展開可能回数や残量'
    'AttackMode m_attackMode;' = 'AttackMode m_attackMode; // 現在の攻撃モード（通常・特殊）'
    'int m_specialCooldown;' = 'int m_specialCooldown; // スペルカード等の再使用待機時間'
    'CapsuleCollider* mpCollider;' = 'CapsuleCollider* mpCollider; // 当たり判定用コライダー'
    'Barrier* mpBarrier;' = 'Barrier* mpBarrier; // バリアオブジェクトのポインタ'
    'int m_level;' = 'int m_level; // 現在のプレイヤーレベル'
    'int m_xp;' = 'int m_xp; // 現在獲得している経験値'
    'int m_xpNeeded;' = 'int m_xpNeeded; // 次のレベルアップに必要な経験値量'
    'int m_levelUpTimer;' = 'int m_levelUpTimer; // レベルアップ演出（文字表示など）の表示タイマー'
    'int m_spellGauge;' = 'int m_spellGauge; // 必殺技（スペルカード）を使用するためのゲージ量'
    'int m_maxSpellGauge;' = 'int m_maxSpellGauge; // スペルゲージの最大値'
    'int m_stunTimer;' = 'int m_stunTimer; // 被弾時などの操作不能（スタン）フレーム数'
}
Replace-InFile -Path "Source\Player.h" -Replacements $player_repl

# --- Boss.h ---
$boss_repl = [ordered]@{
    'float m_speed;' = 'float m_speed; // ボスの移動速度'
    'int m_hp;' = 'int m_hp; // ボスの現在の体力（フェーズごと）'
    'int m_maxHp;' = 'int m_maxHp; // 現在のフェーズにおける最大体力'
    'bool m_isActive;' = 'bool m_isActive; // ボスが現在アクティブ（戦闘中）かどうか'
    'int m_bossType;' = 'int m_bossType; // ボスの種類や行動パターンの識別子'
    'float m_targetX, m_targetY;' = 'float m_targetX, m_targetY; // ボスが次に向かう移動目標座標'
    'int m_attackTimer;' = 'int m_attackTimer; // 弾幕攻撃を発射するためのインターバル管理タイマー'
    'int m_patternIndex;' = 'int m_patternIndex; // 現在実行中の攻撃パターンのインデックス'
    'bool m_isDying;' = 'bool m_isDying; // 死亡演出中かどうかのフラグ'
    'int m_deathTimer;' = 'int m_deathTimer; // 死亡演出（爆発など）の進行を管理するタイマー'
    'int m_lives;' = 'int m_lives; // ボスの残りフェーズ数（残機）'
    'int m_invincibleTimer;' = 'int m_invincibleTimer; // フェーズ移行時などの無敵時間タイマー'
    'int m_invincibleCycleTimer;' = 'int m_invincibleCycleTimer; // 無敵時の点滅エフェクト用タイマー'
    'CapsuleCollider* mpCollider;' = 'CapsuleCollider* mpCollider; // 当たり判定用コライダー'
}
Replace-InFile -Path "Source\Boss.h" -Replacements $boss_repl

# --- Enemy.h ---
$enemy_repl = [ordered]@{
    'float m_speed;' = 'float m_speed; // 敵キャラクターの移動速度'
    'bool m_isActive;' = 'bool m_isActive; // 画面内に存在し活動状態にあるかどうかのフラグ'
    'int m_hp;' = 'int m_hp; // 現在の体力値'
    'int m_maxHp;' = 'int m_maxHp; // 体力の最大値（描画用）'
    'CapsuleCollider* mpCollider;' = 'CapsuleCollider* mpCollider; // 当たり判定用コライダー'
    'int m_enemyType;      ' = 'int m_enemyType;      // 敵の種別（外見や行動パターンを決定）'
    'int m_attackTimer;    ' = 'int m_attackTimer;    // 弾を発射するまでのインターバルタイマー'
    'float m_targetX, m_targetY; ' = 'float m_targetX, m_targetY; // ランダム移動時の目的地座標'
}
Replace-InFile -Path "Source\Enemy.h" -Replacements $enemy_repl

# --- Bullet.h ---
$bullet_repl = [ordered]@{
    'float m_speed;        ' = 'float m_speed;        // 弾の進行速度'
    'bool m_isActive;      ' = 'bool m_isActive;      // 弾が画面内に存在し有効かどうかのフラグ'
    'int m_damage;         ' = 'int m_damage;         // 敵に与えるダメージ量'
    'int m_recivedDamage;      ' = 'int m_recivedDamage;      // （貫通弾などで）これまでに与えたダメージの蓄積'
    'int m_MaxrecivedDamage; ' = 'int m_MaxrecivedDamage; // この弾が与えられる最大ダメージ上限（貫通制限）'
    'CapsuleCollider* mpCollider;' = 'CapsuleCollider* mpCollider; // 当たり判定用コライダー'
}
Replace-InFile -Path "Source\Bullet.h" -Replacements $bullet_repl

# --- EnemyBullet.h ---
$enemybullet_repl = [ordered]@{
    'float m_dx, m_dy;   ' = 'float m_dx, m_dy;   // X・Y方向への移動ベクトル（毎フレーム加算）'
    'float m_speed;      ' = 'float m_speed;      // 弾の進行速度'
    'bool m_isActive;    ' = 'bool m_isActive;    // 画面内に存在し有効かどうかのフラグ'
    'CapsuleCollider* mpCollider;' = 'CapsuleCollider* mpCollider; // 当たり判定用コライダー'
    'bool m_canReflect;' = 'bool m_canReflect; // 画面端で反射する仕様の弾かどうか'
    'bool m_hasReflected;' = 'bool m_hasReflected; // すでに反射を一度行ったかどうかのフラグ'
    'bool m_isStunBullet; ' = 'bool m_isStunBullet; // 当たった相手を行動不能（スタン）にする状態異常弾かどうか'
    'int m_homingTimer;   ' = 'int m_homingTimer;   // ホーミング（追尾）処理が有効な残りフレーム数'
    'int m_homingDelayTimer;' = 'int m_homingDelayTimer; // 発射後、ホーミングを開始するまでの遅延タイマー'
}
Replace-InFile -Path "Source\EnemyBullet.h" -Replacements $enemybullet_repl

# --- HUD.h ---
$hud_repl = [ordered]@{
    'static float s_displayHpRatio;' = 'static float s_displayHpRatio; // アニメーション補間用のHP表示比率'
    'static float s_displayXpRatio;' = 'static float s_displayXpRatio; // アニメーション補間用の経験値表示比率'
    'static float s_displaySpellRatio;' = 'static float s_displaySpellRatio; // アニメーション補間用のスペルゲージ表示比率'
    'static float s_displayBarrierRatio;' = 'static float s_displayBarrierRatio; // アニメーション補間用のバリアゲージ表示比率'
    'static float s_bossHpRatio;' = 'static float s_bossHpRatio; // アニメーション補間用のボスHP表示比率'
}
Replace-InFile -Path "Source\HUD.h" -Replacements $hud_repl

# --- TitleScene.h ---
$titlescene_repl = [ordered]@{
    'int m_bgGraph;' = 'int m_bgGraph; // タイトル背景画像のハンドル'
    'float m_bgScrollX;' = 'float m_bgScrollX; // 背景スクロール演出のためのX座標オフセット'
    'int m_uiButtonGraph;' = 'int m_uiButtonGraph; // 選択ボタンUIの画像ハンドル'
    'std::vector<int> m_rankings;' = 'std::vector<int> m_rankings; // クリアタイムなどのランキングデータ保持'
}
Replace-InFile -Path "Source\TitleScene.h" -Replacements $titlescene_repl

Write-Host "All replacements done!"
