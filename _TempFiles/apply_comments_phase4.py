import os

def replace_in_file(filepath, replacements):
    with open(filepath, 'r', encoding='cp932') as f:
        content = f.read()
    
    for old, new in replacements:
        if old not in content:
            print(f"Warning: Could not find '{old}' in {filepath}")
        content = content.replace(old, new)
        
    with open(filepath, 'w', encoding='cp932') as f:
        f.write(content)
    print(f"Updated {filepath}")

# --- HUD.cpp ---
hud_replacements = [
    ('// Player HP', '// プレイヤーの現在体力を数値で明示するためHPを描画'),
    ('// Player HP Bar (New!)', '// 視覚的に直感的な体力把握を可能にするためゲージを描画'),
    ('// Level & XP HUD', '// 成長度合いをフィードバックするためレベルと経験値枠を描画'),
    ('// Spell Card Gauge', '// スペルカード（必殺技）の準備状況を視覚的に通知するためのゲージ処理'),
    ('// LEVEL UP! Flash Effect', '// レベルアップ時の視覚的な報酬感を高めるため一定フレーム文字を点滅描画'),
    ('// Slide in quickly', '// カットイン登場時の勢いを演出するためイージングをかけて高速移動'),
    ('// Hold and slightly drift', '// プレイヤーにカットイン内容を視認させるため中央付近で微速移動を維持'),
    ('// Slide out quickly', '// 演出終了後に速やかに画面外へ退場させるための座標計算')
]
replace_in_file('Source/HUD.cpp', hud_replacements)

# --- Main.cpp ---
main_replacements = [
    ('// Truncate log file', '// 起動毎に最新のログを出力するため、既存のログファイルを破棄して初期化'),
    ('// Start debug console', '// 開発中の動作確認およびエラー調査を容易にするためコンソールを割り当て'),
    ('// Init DX Library', '// DxLibの基本設定および初期化（ログファイル出力を無効化）'),
    ('    SetDrawScreen(DX_SCREEN_BACK);', '    // 描画先を裏画面に設定し、チラつきのないダブルバッファリングを実現\n    SetDrawScreen(DX_SCREEN_BACK);'),
    ('// Main loop', '// OSのメッセージ処理とESCキーによる安全な終了を保証するためのメインループ')
]
replace_in_file('Source/Main.cpp', main_replacements)

# --- MeleeAttack.cpp ---
melee_replacements = [
    ('SetTag(Tag2D_PlayerBullet); // So it\'s recognized as a player attack', 'SetTag(Tag2D_PlayerBullet); // プレイヤーの攻撃として当たり判定を処理させるため専用タグを設定'),
    ('m_lifetime = 10; // Active for 10 frames\n    m_damage = 3;    // High damage melee slash', 'm_lifetime = 10; // 近接攻撃であるため短期間（10フレーム）で消失させる\n    m_damage = 3;    // リスクに見合った高威力のダメージ設定'),
    ('// Create a large circular collider in front of the player (radius 80)', '// 近接攻撃の当たり判定として、キャラクター前方に巨大な円形コライダーを配置'),
    ('// Draw a beautiful white and cyan slash arc pointing upwards using overlapping circles', '// 剣の軌跡を表現するため、複数の円を円弧状に配置して斬撃エフェクトを描画'),
    ('// Draw 9 small circles forming an arc pointing upwards (from 210 degrees to 330 degrees)', '// 210度から330度の範囲で円弧を描くように9つの点を計算して描画'),
    ('// Draw inner white circle for a glowing hot core effect', '// 斬撃の中心が熱を帯びて光っているような演出のため内側に白い円を重ねる'),
    ('// Melee attack cannot be killed/destroyed by bullets', '// 近接攻撃は敵弾によって相殺されない仕様とするため空処理'),
    ('// To avoid dealing damage every single frame, we could track hit enemies, \n                // but for a short 10-frame melee slash, dealing damage once is best.\n                // We\'ll tag the enemy or simply check if they are already hit.\n                // For simplicity and high impact, we\'ll deal damage.', '// 攻撃判定は短期間（10フレーム）であるため、ヒット間隔を管理せず即座にダメージを与える')
]
replace_in_file('Source/MeleeAttack.cpp', melee_replacements)

# --- Obstacle.cpp ---
obstacle_replacements = [
    ('SetTag(Tag2D_Enemy); // Treated like an enemy so bullets hit it', 'SetTag(Tag2D_Enemy); // プレイヤーの弾や体当たり判定の対象とするため便宜上敵タグを付与'),
    ('// If a player bullet hits the obstacle', '// プレイヤー側の攻撃と衝突した場合の処理（特殊弾かどうかで分岐）'),
    ('// If player touches it, damage player', '// プレイヤー自身が障害物に衝突した場合、回避ペナルティとしてダメージを与える')
]
replace_in_file('Source/Obstacle.cpp', obstacle_replacements)

# --- RainbowWaveManager.cpp ---
rainbow_replacements = [
    (', m_lifeTimer(120) // 3 seconds duration\n    , m_spawnInterval(10) // Spawn a row every 5 frames', ', m_lifeTimer(120) // 管理オブジェクト自体の生存期間（3秒）\n    , m_spawnInterval(10) // 弾を生成するインターバル（5フレームごと）'),
    ('// Spawn a horizontal line of colorful bullets at the bottom of the screen', '// 画面下部から画面全体を覆うように弾を配置するため、等間隔に座標を計算'),
    ('float yPos = static_cast<float>(Utility::SCREEN_HEIGHT) + 20.0f; // Just below screen', 'float yPos = static_cast<float>(Utility::SCREEN_HEIGHT) + 20.0f; // 画面外から出現させるため下部にオフセット'),
    ('// This manager is invisible, it just spawns bullets', '// 弾の生成管理のみを行う不可視オブジェクトであるため描画処理は不要'),
    ('// No collision for the manager itself', '// 自身は当たり判定を持たず、生成した弾に判定を委ねるため空処理')
]
replace_in_file('Source/RainbowWaveManager.cpp', rainbow_replacements)

# --- ResultScene.cpp ---
result_replacements = [
    ('// Confetti', '// 勝利の祝福感を演出するため、紙吹雪に見立てたパーティクルを描画'),
    ('// Draw rotated rect manually or just circle if we can\'t be bothered with rotation math', '// 複雑な回転計算を省き、描画負荷を下げるためシンプルな円で代用')
]
replace_in_file('Source/ResultScene.cpp', result_replacements)

# --- RuleScene.cpp ---
rule_replacements = [
    ('m_ruleGraphs[4] = -1; // Or load new images if available', 'm_ruleGraphs[4] = -1; // 将来的なスライド追加に備えてあらかじめ枠を確保し初期化'),
    ('// Back Button', '// プレイヤーがタイトルへ戻る操作を行った際の遷移処理'),
    ('// Next Button', '// 次のページへ進む処理（最終ページの場合はタイトルへ戻る）'),
    ('// Prev Button', '// 前のページへ戻る処理（最初のページでは無効）'),
    ('float maxHeight = 650.0f; // Expand height', 'float maxHeight = 650.0f; // 説明画像が見やすくなるよう描画領域を大きめに設定'),
    ('// Draw Back button', '// 直感的な操作を促すため、戻るボタンにマウスが重なった際に色を変化させる'),
    ('// Draw Prev button', '// 現在位置を明示するため、2ページ目以降のみ前へ戻るボタンを描画'),
    ('// Draw Next button', '// スライド進行状況に合わせて、次へボタンと完了ボタンの表示を切り替えつつ描画')
]
replace_in_file('Source/RuleScene.cpp', rule_replacements)

# --- Scene.cpp ---
scene_replacements = [
    ('// Create object manager', '// シーン固有のオブジェクトおよび当たり判定を管理するため専用のマネージャーを生成'),
    ('// Draw', '// 全オブジェクトの描画処理をマネージャー経由で一括実行'),
    ('// Update', '// 全オブジェクトの状態更新および当たり判定処理を一括実行')
]
replace_in_file('Source/Scene.cpp', scene_replacements)

# --- SpecialBullet.cpp ---
special_replacements = [
    ('SetTag(Tag2D_PlayerBullet); // So it\'s recognized as a player projectile', 'SetTag(Tag2D_PlayerBullet); // プレイヤー側の攻撃として判定させるためのタグ設定'),
    ('m_damage = 5; // Ultimate piercing damage!', 'm_damage = 5; // 必殺技としての威力を表現するための高ダメージ設定'),
    ('// Create a giant circular collider with radius 90 (previously 60)', '// 画面広範囲の敵を巻き込むため、通常弾よりも極めて巨大な当たり判定を設定'),
    ('// Draw a giant glowing golden energy sphere representing the ultimate sushi attack!', '// 強力なエネルギー弾であることを視覚的に強調するため、輝く金色の球体を描画'),
    ('// Draw concentric circles for a nice glowing effect', '// 光の重なりによる発光感を出すため、色とサイズを変えた複数の円を同心円状に描画'),
    ('// Add cross lines to make it look like a giant ultimate energy blast', '// 十字のラインを重ねることで、エネルギーが凝縮され溢れ出しているような演出を追加'),
    ('// Ultimate piercing bullet does not get killed on impact!', '// 敵を貫通して一網打尽にする仕様とするため、衝突時の消滅処理を行わない'),
    ('// Deal high ultimate damage (does not call Kill() so it pierces through!)', '// 貫通弾であるため、敵にダメージを与えつつ自身はそのまま直進させる')
]
replace_in_file('Source/SpecialBullet.cpp', special_replacements)

# --- StageSelectScene.cpp ---
stage_replacements = [
    ('// Draw Back button', '// 誤操作を防ぐため、画面左上に明確な「戻る」ボタンを配置してホバー判定'),
    ('// Char 1', '// プレイヤー1（ノーマルシェフ）の選択状態およびホバー演出を描画'),
    ('// Char 2', '// プレイヤー2（ガールシェフ）の選択状態およびホバー演出を描画'),
    ('// Char 3', '// プレイヤー3（オールドシェフ）の選択状態およびホバー演出を描画')
]
replace_in_file('Source/StageSelectScene.cpp', stage_replacements)

# --- TitleScene.cpp ---
title_replacements = [
    ('// Update Background scroll', '// 背景画像を常に左方向へスクロールさせ、躍動感のあるタイトル画面を演出'),
    ('DrawBox(x, y, x + btnW, y + btnH, GetColor(0, 200, 255), TRUE); // Glow effect', 'DrawBox(x, y, x + btnW, y + btnH, GetColor(0, 200, 255), TRUE); // 選択可能なUIであることを強調するため発光エフェクトを加算')
]
replace_in_file('Source/TitleScene.cpp', title_replacements)

print("All replacements done!")
