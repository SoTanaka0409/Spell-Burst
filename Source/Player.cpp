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
#include "SpecialBullet.h"
#include "ResourceManager.h"
#include "SpellCardBullet.h"
#include "GameScene.h"

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

// Encouragement Ξ connection, connection, connection
// After the conclusion? 
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
    m_attackTimer = 20; // 逋子蟆・松髫斐遏縺擾しiso”蟆・ｼ・
    m_AttackInterval =0 ;
    m_AttackTimer_2 = 60;
    // Level & XP system initialization
    m_level = 1;
    m_xp = 0;
    m_xpNeeded = 5; // Level 1 needs 5 XP to level up
    m_levelUpTimer = 0;
    
    m_spellGauge = 0;
    m_maxSpellGauge = 10; // 10 繧繧い 繧繧MAX

    // Create a circular collider with small radius (Touhou style)
    mpCollider = new CapsuleCollider(this, mvPosition, mvPosition, 4.0f);
}

// If you are weak, you will be disappointed.
// 繧ｭ繝ｼ蜈・蜉帙↓繧Physiciankｻｻ蜍輔d?∫螟?↓蜃ｺ?ｪ?・h?・↓
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
        return; // 繧ｹ繧ｿ繝ｳ荳ｭ縺ｯ蜈・蜉帙→謬さ謦・r繧ｭ繧ｭ繝・・
    }

    // 菴朱溽ｧｻ蜍繧ｼPhysician 繧ｩ繝ｼ繧ｫ繧ｹ・峨Δ繝ｼ繝・
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

// Encouragement Ξ connection, connection, connection
// Encouragement Ξ 繧、繝、繝ｼTHRESHOLD
void Player::Draw() {
    if (m_stunTimer > 0) {
        // 繧ｹ繧ｿ繝ｳ荳ｭ縺ｯdetective＞Shu・ryoban
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

    // 菴朱溽ｧｻ蜍穂kuｭ縺ｯ蠖薙◆繧繧?螳夲ｼPhysician繧'・峨謠行版縺吶k
    if (InputManager::CheckPressKey(KEY_INPUT_LSHIFT)) {
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 5, GetColor(255, 255, 255), TRUE); // 螟匁棧・生區・・
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 3, GetColor(255, 0, 0), TRUE); // Ikuo...
    }
}

// 繝繝。
// 繧繧・ambienceｮ蠑ｾ縺ｨ蠖薙◆縺”?滄圀縺ｫ蜻ｼ縺ｰ繧after?
void Player::TakeDamage(int damage) {
    m_hp -= damage;
    if (m_hp <= 0) {
        m_hp = 0;
        ResultScene::s_isVictory = false;
        Master::sceneManager->SetNextScene(SceneManager::SCENE_RESULT);
    }
}
// Pleasure...Meeting...
// After the arrogance and binding ※?・k??・Δ繝ｼ繝会ｼISO壼ｊ蠑ｾ縲∬th porcelain skewer 
void Player::Attack()
{
    int mouseInput = GetMouseInput(); // It's a joke.
    bool zPressed = InputManager::CheckPressKey(KEY_INPUT_Z);
    
    m_AttackInterval++;
    m_AttackInterval_2++;
    // Cooldown decrement
    if (m_specialCooldown > 0) {
        m_specialCooldown--;
    }
    
    // Z 繧ｭ繝ｼ縺梧款縺輔l縦縺・k髢薙√Γ繧、繝ｳ繧ｷ繝ｧ繝・YO繧 繧?蟆・
    if ( m_AttackInterval >= m_attackTimer)
    {
        m_AttackInterval = 0;// Interval 縺ｮ
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

    // 繧ｹ繝壹Ν繧ｫ繝ｼ繝尨、逋｜蜍彼ｼ、繧ｭ繝ｼ・・
    if (InputManager::CheckPressKey(KEY_INPUT_X)) {
        if (m_spellGauge >= m_maxSpellGauge) {
            m_spellGauge = 0; // 繧い繝ｼ繧
            new SpellCardBullet(m_x, m_y - 90.0f);
            
            GameScene* gs = dynamic_cast<GameScene*>(Master::sceneManager->GetCurrentScene());
            if (gs != nullptr) {
                gs->TriggerCutin();
            }
        }
    }
}

// 邨灘灘､・・P・峨・迯ｲ??→繝ｬ繝吶Ν繧``繝・・蜃ｦ逅・
// After the investigation, the investigation is completed.
void Player::AddXp(int amount) {
    m_xp += amount;
    
    // 繧ｹ繝壹Ν繧ｲ繝ｼ繧ｸ繧ゆｸ邱detective↓???輔○繧・
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

// 莉ｦｪｪｪｪｪｪｪｪｪｪｯｯｯｯｯ?繧ｧｧｯｯ?繧ｺｦｺｺｺｺｺｺｺｯｯ｜ｦｯｯｯ
// 謨譛菴薙→?ｽ縺、縺９▲縺溷ｴ荷Physician↓繝繝｡繝ｼ繧ｸ繧正女?代∪?吶・
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

void Player::Heal(int amount) {
    m_hp += amount;
    if (m_hp > m_maxHp) {
        m_hp = m_maxHp;
    }
}