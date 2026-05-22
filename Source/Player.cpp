#include "Player.h"
#include "InputManager.h"
#include "Bullet.h"
#include "CapsuleCollider.h"
#include "dxlib.h"
#include "Utility.h"
#include "Enemy.h"
#include "Master.h"
#include "SceneManager.h"
#include "ResultScene.h"
#include "MeleeAttack.h"
#include "SpecialBullet.h"
#include "ResourceManager.h"
#include "SpellCardBullet.h"

Player::Player() 
    : Object2D(VGet((float)Utility::SCREEN_WIDTH / 2.0f, (float)Utility::SCREEN_HEIGHT / 2.0f, 0.0f))
    , mpCollider(nullptr)
{
    SetTag(Tag2D_Player);
    Initialize();
}

Player::~Player() {
    if (mpCollider) {
        delete mpCollider;
        mpCollider = nullptr;
    }
    m_levelUpTimer = 0;
    m_stunTimer = 0;
}

// プレイヤーの初期化処理
// ゲーム開始時やリトライ時に呼ばれ、HPやレベル、座標などを初期状態に戻します。
void Player::Initialize() {
    m_x = (float)Utility::SCREEN_WIDTH / 2.0f;
    m_y = (float)Utility::SCREEN_HEIGHT / 2.0f;
    m_speed = 5.0f;
    m_maxHp = 10;
    m_hp = m_maxHp;
    m_levelUpTimer = 0;
    m_stunTimer = 0;
    m_attackMode = AttackMode_Melee;
    m_specialCooldown = 0;
    mfAttack = 1;
    m_attackTimer = 20; // 発射間隔を短く（連射）
    m_AttackInterval =0 ;
    m_AttackTimer_2 = 60;
    // Level & XP system initialization
    m_level = 1;
    m_xp = 0;
    m_xpNeeded = 5; // Level 1 needs 5 XP to level up
    m_levelUpTimer = 0;
    
    m_spellGauge = 0;
    m_maxSpellGauge = 10; // 敵10体分でゲージMAX

    // Create a circular collider with small radius (Touhou style)
    mpCollider = new CapsuleCollider(this, mvPosition, mvPosition, 4.0f);
}

// 毎フレーム呼ばれる更新処理
// キー入力による移動や、画面外に出ないようにする制限、各種タイマーの更新を行います。
void Player::Update()
{
    if (m_levelUpTimer > 0) {
        m_levelUpTimer--;
    }

    if (m_stunTimer > 0) {
        m_stunTimer--;
        // Update collider position even when stunned so we can take more hits if needed
        if (mpCollider) {
            mpCollider->mvPosition = mvPosition;
            mpCollider->mvPosition2 = mvPosition;
        }
        return; // スタン中は入力と攻撃をスキップ
    }

    // 低速移動（フォーカス）モード
    bool isFocus = InputManager::CheckPressKey(KEY_INPUT_LSHIFT);
    float currentSpeed = isFocus ? 2.0f : m_speed;

    if (InputManager::CheckPressKey(KEY_INPUT_W)) { m_y -= currentSpeed; }
    if (InputManager::CheckPressKey(KEY_INPUT_S)) { m_y += currentSpeed; }
    if (InputManager::CheckPressKey(KEY_INPUT_A)) { m_x -= currentSpeed; }
    if (InputManager::CheckPressKey(KEY_INPUT_D)) { m_x += currentSpeed; }

    // Clamp inside screen with 45.0f padding
    if (m_x < 45.0f) m_x = 45.0f;
    if (m_x > Utility::SCREEN_WIDTH - 45.0f) m_x = Utility::SCREEN_WIDTH - 45.0f;
    if (m_y < 45.0f) m_y = 45.0f;
    if (m_y > Utility::SCREEN_HEIGHT - 45.0f) m_y = Utility::SCREEN_HEIGHT - 45.0f;

    mvPosition = VGet(m_x, m_y, 0.0f);

    if (mpCollider) {
        mpCollider->mvPosition = mvPosition;
        mpCollider->mvPosition2 = mvPosition;
    }

    

    // Level-up flash timer decrement
    if (m_levelUpTimer > 0) {
        m_levelUpTimer--;
    }

    // Switch attack modes
    if (InputManager::CheckDownKey(KEY_INPUT_Q)) {
        
         if (m_attackMode == AttackMode_Melee) m_attackMode = AttackMode_Special;
        else m_attackMode = AttackMode_Melee;
    }
   

    // Firing attacks
    Attack();
   
}

// プレイヤーの描画処理
// プレイヤー自身の画像を描画します。
void Player::Draw() {
    if (m_stunTimer > 0) {
        // スタン中は青い円を描画
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 50, GetColor(0, 200, 255), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }

    int s_playerGraphHandle = ResourceManager::GetInstance()->GetGraph("Resource/player.png");

    if (s_playerGraphHandle != -1) {
        DrawExtendGraph(
            static_cast<int>(mvPosition.x - 45.0f), 
            static_cast<int>(mvPosition.y - 45.0f), 
            static_cast<int>(mvPosition.x + 45.0f), 
            static_cast<int>(mvPosition.y + 45.0f), 
            s_playerGraphHandle, 
            TRUE
        );
    } else {
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 45, GetColor(0, 255, 0), TRUE);
    }

    // 低速移動中は当たり判定（コア）を描画する
    if (InputManager::CheckPressKey(KEY_INPUT_LSHIFT)) {
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 5, GetColor(255, 255, 255), TRUE); // 外枠（白）
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 3, GetColor(255, 0, 0), TRUE); // 中心（赤）
    }
}

// ダメージを受ける処理
// 敵や敵の弾と当たった際に呼ばれ、HPを減らします。HPが0になるとリザルト画面（敗北）に移行します。
void Player::TakeDamage(int damage) {
    m_hp -= damage;
    if (m_hp <= 0) {
        m_hp = 0;
        ResultScene::s_isVictory = false;
        Master::sceneManager->SetNextScene(SceneManager::SCENE_RESULT);
    }
}
// 攻撃処理
// 選択されている攻撃モード（通常弾、近接、必殺技）に応じて弾を生成・発射します。
void Player::Attack()
{
    int mouseInput = GetMouseInput(); // マウスの状態を取得
    bool zPressed = InputManager::CheckPressKey(KEY_INPUT_Z);
    
    m_AttackInterval++;
    m_AttackInterval_2++;
    // Cooldown decrement
    if (m_specialCooldown > 0) {
        m_specialCooldown--;
    }
    
    // Zキーが押されている間、メインショットを発射
    if ( m_AttackInterval >= m_attackTimer)
    {
        m_AttackInterval = 0;//intervalの初期化
            int numBullets = m_level;
            float spacing = 20.0f;
            float startX = m_x - (numBullets - 1) * spacing / 2.0f;
            for (int i = 0; i < numBullets; ++i) 
            {
                new Bullet(startX + i * spacing, m_y - 45.0f, mfAttack);
            }
            
        
        
    }

    if (mouseInput & MOUSE_INPUT_LEFT&&m_AttackInterval_2>=m_AttackTimer_2)
    {
        m_AttackInterval_2 = 0;
        if (m_attackMode == AttackMode_Melee) {
            new MeleeAttack(m_x, m_y - 70.0f);
        }
        else if (m_attackMode == AttackMode_Special)
        {
            if (m_specialCooldown == 0)
            {
                new SpecialBullet(m_x, m_y - 90.0f);
                m_specialCooldown = 180; // 3 seconds cooldown
            }
        }
    }
    if (mouseInput & MOUSE_INPUT_LEFT)
    {
        new SpecialBullet(m_x, m_y - 90.0f);
    }

    // スペルカードの発動（Xキー）
    if (InputManager::CheckDownKey(KEY_INPUT_X)) {
       // if (m_spellGauge >= m_maxSpellGauge) 
        {
            m_spellGauge = 0; // ゲージ消費
            new SpellCardBullet(m_x, m_y - 90.0f);
        }
    }
}

// 経験値（XP）の獲得とレベルアップ処理
// 敵を倒した時に呼ばれ、一定値を超えるとレベルアップしてHPを全回復します。
void Player::AddXp(int amount) {
    m_xp += amount;
    
    // スペルゲージも一緒に増加させる
    m_spellGauge += amount;
    if (m_spellGauge > m_maxSpellGauge) {
        m_spellGauge = m_maxSpellGauge;
    }
    // Level-up loop (handles multiple level-ups from one big XP gain)
    while (m_xp >= m_xpNeeded) {
        m_xp -= m_xpNeeded;
        m_level++;
        m_xpNeeded = m_level * 5; // Each level requires (level * 5) XP
        // Bonus on level up: full HP restore
        m_hp = m_maxHp;
        m_levelUpTimer = 120; // Show "LEVEL UP!" for 120 frames (~2 seconds)
    }
}

void Player::OnEnter(Collider* collider, Collider* check) {}

// 他のオブジェクトと重なっている時の処理
// 敵本体とぶつかった場合にダメージを受けます。
void Player::OnTrigger(Collider* collider, Collider* check) {
    if (check != nullptr && check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == Tag2D_Enemy) {
            Enemy* enemy = dynamic_cast<Enemy*>(check->GetParentObject());
            if (enemy != nullptr) {
                TakeDamage(1); // Player takes 1 damage
                //enemy->Kill(); // Destroy the enemy on crash
            }
        }
    }
}
void Player::OnExit(Collider* collider, Collider* check) {}
