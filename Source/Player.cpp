#include "SoundManager.h"
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
<<<<<<< HEAD
#include "SpecialBullet.h"
#include "ResourceManager.h"
#include "SpellCardBullet.h"
#include "GameScene.h"

=======
#include "MasterSpark.h"
#include "RainbowWaveManager.h"
#include "SpellCardBullet.h"
#include "SpecialBullet.h"
#include "ResourceManager.h"
#include "GameScene.h"

int Player::s_selectedCharacterType = 1;

>>>>>>> main
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
<<<<<<< HEAD
=======
    if (mpBarrier) {
        mpBarrier->SetDeleteFlag(true);
        mpBarrier = nullptr;
    }
>>>>>>> main
    m_levelUpTimer = 0;
    m_stunTimer = 0;
}

// プレイヤーの初期化�E琁E
// ゲーム開始時めE��トライ時に呼ばれ、HPめE��ベル、座標などを�E期状態に戻します、E
void Player::Initialize() {
<<<<<<< HEAD
    m_x = (float)Utility::SCREEN_WIDTH / 2.0f;
    m_y = (float)Utility::SCREEN_HEIGHT / 2.0f;
=======
    mvPosition.x = (float)Utility::SCREEN_WIDTH / 2.0f;
    mvPosition.y = (float)Utility::SCREEN_HEIGHT / 2.0f;
>>>>>>> main
    m_speed = 5.0f;
    m_maxHp = 10;
    m_hp = m_maxHp;
    m_levelUpTimer = 0;
    m_stunTimer = 0;
    m_attackMode = AttackMode_Melee;
    m_specialCooldown = 0;
    mfAttack = 1;
<<<<<<< HEAD
    m_attackTimer = 20; // 発封E��隔を短く（連封E��E
=======
<<<<<<< HEAD
    m_attackTimer = 20; // 発射間隔を短く（連射）
>>>>>>> 240f2f277102418da5ddb286e12d12d717854dca
    m_AttackInterval =0 ;
    m_AttackTimer_2 = 60;
=======
    m_attackTimer = 20; // 逋ｺ蟆・俣髫斐ｒ遏ｭ縺擾ｼ磯€｣蟆・ｼ・
    m_AttackInterval =0 ;
    m_AttackTimer_2 = 60;
    m__BarrierCount = 0;
>>>>>>> main
    // Level & XP system initialization
    m_level = 1;
    m_xp = 0;
    m_xpNeeded = 5; // Level 1 needs 5 XP to level up
<<<<<<< HEAD
    m_levelUpTimer = 0;
    
    m_spellGauge = 0;
    m_maxSpellGauge = 10; // 敵10体�EでゲージMAX

    // Create a circular collider with small radius (Touhou style)
    mpCollider = new CapsuleCollider(this, mvPosition, mvPosition, 4.0f);
=======
    m_levelUpTimer = 0;                  
    
    m_spellGauge = 0;
    m_maxSpellGauge = 10; // 謨ｵ10菴灘・縺ｧ繧ｲ繝ｼ繧ｸMAX

    // Create a circular collider with small radius (Touhou style)
    mpCollider = new CapsuleCollider(this, mvPosition, mvPosition, 4.0f);
	mpBarrier = new Barrier(mvPosition.x, mvPosition.y, 60.0f,tag2D_BarierPla);
>>>>>>> main
}

// 毎フレーム呼ばれる更新処琁E
// キー入力による移動や、画面外に出なぁE��ぁE��する制限、各種タイマ�Eの更新を行います、E
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
        return; // スタン中は入力と攻撁E��スキチE�E
    }

    // 低速移動（フォーカス�E�モーチE
    bool isFocus = InputManager::CheckPressKey(KEY_INPUT_LSHIFT);
<<<<<<< HEAD
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
=======
    float currentSpeed = (isFocus ? 2.0f : m_speed) * Utility::TimeScale;

    if (InputManager::CheckPressKey(KEY_INPUT_W)) { mvPosition.y -= currentSpeed; }
    if (InputManager::CheckPressKey(KEY_INPUT_S)) { mvPosition.y += currentSpeed; }
    if (InputManager::CheckPressKey(KEY_INPUT_A)) { mvPosition.x -= currentSpeed; }
    if (InputManager::CheckPressKey(KEY_INPUT_D)) { mvPosition.x += currentSpeed; }

    // Clamp inside screen with 45.0f padding
    if (mvPosition.x < 45.0f) mvPosition.x = 45.0f;
    if (mvPosition.x > Utility::SCREEN_WIDTH - 45.0f) mvPosition.x = Utility::SCREEN_WIDTH - 45.0f;
    if (mvPosition.y < 45.0f) mvPosition.y = 45.0f;
    if (mvPosition.y > Utility::SCREEN_HEIGHT - 45.0f) mvPosition.y = Utility::SCREEN_HEIGHT - 45.0f;

    mvPosition = VGet(mvPosition.x, mvPosition.y, 0.0f);
    
    // バリアをプレイヤーに追従させる
    if (mpBarrier) {
        mpBarrier->SetPosition(mvPosition);
    }
>>>>>>> main

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

// プレイヤーの描画処琁E
// プレイヤー自身の画像を描画します、E
void Player::Draw() {
    if (m_stunTimer > 0) {
        // スタン中は青い冁E��描画
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 50, GetColor(0, 200, 255), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }

<<<<<<< HEAD
    int s_playerGraphHandle = ResourceManager::GetInstance()->GetGraph("Resource/player.png");
=======
    int s_playerGraphHandle = -1;
    if (s_selectedCharacterType == 1) {
        s_playerGraphHandle = ResourceManager::GetInstance()->GetGraph("Resource/player.png");
    } else if (s_selectedCharacterType == 2) {
        s_playerGraphHandle = ResourceManager::GetInstance()->GetGraph("Resource/player2.png");
    } else if (s_selectedCharacterType == 3) {
        s_playerGraphHandle = ResourceManager::GetInstance()->GetGraph("Resource/player3.png");
    }
>>>>>>> main

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

    // 低速移動中は当たり判定（コア�E�を描画する
    if (InputManager::CheckPressKey(KEY_INPUT_LSHIFT)) {
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 5, GetColor(255, 255, 255), TRUE); // 外枠�E�白�E�E
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 3, GetColor(255, 0, 0), TRUE); // 中忁E��赤�E�E
    }
}

// ダメージを受ける処琁E
// 敵めE��の弾と当たった際に呼ばれ、HPを減らします、EPぁEになるとリザルト画面�E�敗北）に移行します、E
void Player::TakeDamage(int damage) {
    m_hp -= damage;
    if (m_hp <= 0) {
        m_hp = 0;
        ResultScene::s_isVictory = false;
        Master::sceneManager->SetNextScene(SceneManager::SCENE_RESULT);
    }
}
<<<<<<< HEAD
// 攻撁E�E琁E
// 選択されてぁE��攻撁E��ード（通常弾、近接、忁E��技�E�に応じて弾を生成�E発封E��ます、E
=======
// 攻撃処理
// 選択されている攻撃モード（通常弾、近接、必殺技）に応じて弾を生成・発射します。
<<<<<<< HEAD
=======


>>>>>>> main
>>>>>>> 240f2f277102418da5ddb286e12d12d717854dca
void Player::Attack()
{
    int mouseInput = GetMouseInput(); // マウスの状態を取征E
    bool zPressed = InputManager::CheckPressKey(KEY_INPUT_Z);
    
    m_AttackInterval++;
    m_AttackInterval_2++;
    // Cooldown decrement
    if (m_specialCooldown > 0) {
        m_specialCooldown--;
    }
    
    // Zキーが押されてぁE��間、メインショチE��を発封E
    if ( m_AttackInterval >= m_attackTimer)
    {
        m_AttackInterval = 0;//intervalの初期匁E
            int numBullets = m_level;
            float spacing = 20.0f;
<<<<<<< HEAD
            float startX = m_x - (numBullets - 1) * spacing / 2.0f;
            for (int i = 0; i < numBullets; ++i) 
            {
                new Bullet(startX + i * spacing, m_y - 45.0f, mfAttack);
=======
            float startX = mvPosition.x - (numBullets - 1) * spacing / 2.0f;
            for (int i = 0; i < numBullets; ++i) 
            {
                new Bullet(startX + i * spacing, mvPosition.y - 45.0f, mfAttack);
>>>>>>> main
            }
            
        
        
    }

    if (mouseInput & MOUSE_INPUT_LEFT&&m_AttackInterval_2>=m_AttackTimer_2)
    {
        m_AttackInterval_2 = 0;
        if (m_attackMode == AttackMode_Melee) {
<<<<<<< HEAD
            new MeleeAttack(m_x, m_y - 70.0f);
=======
            new MeleeAttack(mvPosition.x, mvPosition.y - 70.0f);
>>>>>>> main
        }
        else if (m_attackMode == AttackMode_Special)
        {
            if (m_specialCooldown == 0)
            {
<<<<<<< HEAD
                new SpecialBullet(m_x, m_y - 90.0f);
=======
                new SpecialBullet(mvPosition.x, mvPosition.y - 90.0f);
>>>>>>> main
                m_specialCooldown = 180; // 3 seconds cooldown
            }
        }
    }
    if (mouseInput & MOUSE_INPUT_LEFT)
    {
<<<<<<< HEAD
        new SpecialBullet(m_x, m_y - 90.0f);
    }

    // スペルカード�E発動！Eキー�E�E
    if (InputManager::CheckPressKey(KEY_INPUT_X)) {
        if (m_spellGauge >= m_maxSpellGauge) {
            m_spellGauge = 0; // ゲージ消費
            new SpellCardBullet(m_x, m_y - 90.0f);
=======
        new SpecialBullet(mvPosition.x, mvPosition.y - 90.0f);
    }

    // スペルカードの発動（Xキー）
    if (InputManager::CheckDownKey(KEY_INPUT_X)) {
        if (m_spellGauge >= m_maxSpellGauge) {
            m_spellGauge = 0; // ゲージ消費
            
            if (s_selectedCharacterType == 1) {
                new MasterSpark(mvPosition.x, mvPosition.y);
            } else if (s_selectedCharacterType == 2) {
                new RainbowWaveManager(mvPosition.x, mvPosition.y);
            } else if (s_selectedCharacterType == 3) {
                new SpellCardBullet(mvPosition.x, mvPosition.y - 90.0f);
            }
>>>>>>> main
            
            GameScene* gs = dynamic_cast<GameScene*>(Master::sceneManager->GetCurrentScene());
            if (gs != nullptr) {
                gs->TriggerCutin();
            }
        }
    }
}

// 経験値�E�EP�E��E獲得とレベルアチE�E処琁E
// 敵を倒した時に呼ばれ、一定値を趁E��るとレベルアチE�EしてHPを�E回復します、E
void Player::AddXp(int amount) {
    m_xp += amount;
    
    // スペルゲージも一緒に増加させめE
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

<<<<<<< HEAD
// 他�Eオブジェクトと重なってぁE��時�E処琁E
// 敵本体とぶつかった場合にダメージを受けます、E
=======
// 他のオブジェクトと重なっている時の処理
// 敵本体とぶつかった場合にダメージを受けます。
<<<<<<< HEAD
>>>>>>> 240f2f277102418da5ddb286e12d12d717854dca
void Player::OnTrigger(Collider* collider, Collider* check) {
=======
void Player::OnTrigger(Collider* collider, Collider* check) 
{
   
>>>>>>> main
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

void Player::Heal(int amount) {
    m_hp += amount;
    if (m_hp > m_maxHp) {
        m_hp = m_maxHp;
    }
}