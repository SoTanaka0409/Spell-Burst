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

// 繝励Ξ繧､繝､繝ｼ縺ｮ蛻晄悄蛹門・逅・
// 繧ｲ繝ｼ繝髢句ｧ区凾繧・Μ繝医Λ繧､譎ゅ↓蜻ｼ縺ｰ繧後？P繧・Ξ繝吶Ν縲∝ｺｧ讓吶↑縺ｩ繧貞・譛溽憾諷九↓謌ｻ縺励∪縺吶・
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
    m_attackTimer = 20; // 逋ｺ蟆・俣髫斐ｒ遏ｭ縺擾ｼ磯｣蟆・ｼ・
    m_AttackInterval =0 ;
    m_AttackTimer_2 = 60;
    // Level & XP system initialization
    m_level = 1;
    m_xp = 0;
    m_xpNeeded = 5; // Level 1 needs 5 XP to level up
    m_levelUpTimer = 0;
    
    m_spellGauge = 0;
    m_maxSpellGauge = 10; // 謨ｵ10菴灘・縺ｧ繧ｲ繝ｼ繧ｸMAX

    // Create a circular collider with small radius (Touhou style)
    mpCollider = new CapsuleCollider(this, mvPosition, mvPosition, 4.0f);
}

// 豈弱ヵ繝ｬ繝ｼ繝蜻ｼ縺ｰ繧後ｋ譖ｴ譁ｰ蜃ｦ逅・
// 繧ｭ繝ｼ蜈･蜉帙↓繧医ｋ遘ｻ蜍輔ｄ縲∫判髱｢螟悶↓蜃ｺ縺ｪ縺・ｈ縺・↓縺吶ｋ蛻ｶ髯舌∝推遞ｮ繧ｿ繧､繝槭・縺ｮ譖ｴ譁ｰ繧定｡後＞縺ｾ縺吶・
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
        return; // 繧ｹ繧ｿ繝ｳ荳ｭ縺ｯ蜈･蜉帙→謾ｻ謦・ｒ繧ｹ繧ｭ繝・・
    }

    // 菴朱溽ｧｻ蜍包ｼ医ヵ繧ｩ繝ｼ繧ｫ繧ｹ・峨Δ繝ｼ繝・
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

// 繝励Ξ繧､繝､繝ｼ縺ｮ謠冗判蜃ｦ逅・
// 繝励Ξ繧､繝､繝ｼ閾ｪ霄ｫ縺ｮ逕ｻ蜒上ｒ謠冗判縺励∪縺吶・
void Player::Draw() {
    if (m_stunTimer > 0) {
        // 繧ｹ繧ｿ繝ｳ荳ｭ縺ｯ髱偵＞蜀・ｒ謠冗判
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

    // 菴朱溽ｧｻ蜍穂ｸｭ縺ｯ蠖薙◆繧雁愛螳夲ｼ医さ繧｢・峨ｒ謠冗判縺吶ｋ
    if (InputManager::CheckPressKey(KEY_INPUT_LSHIFT)) {
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 5, GetColor(255, 255, 255), TRUE); // 螟匁棧・育區・・
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 3, GetColor(255, 0, 0), TRUE); // 荳ｭ蠢・ｼ郁ｵ､・・
    }
}

// 繝繝｡繝ｼ繧ｸ繧貞女縺代ｋ蜃ｦ逅・
// 謨ｵ繧・雰縺ｮ蠑ｾ縺ｨ蠖薙◆縺｣縺滄圀縺ｫ蜻ｼ縺ｰ繧後？P繧呈ｸ帙ｉ縺励∪縺吶・P縺・縺ｫ縺ｪ繧九→繝ｪ繧ｶ繝ｫ繝育判髱｢・域風蛹暦ｼ峨↓遘ｻ陦後＠縺ｾ縺吶・
void Player::TakeDamage(int damage) {
    m_hp -= damage;
    if (m_hp <= 0) {
        m_hp = 0;
        ResultScene::s_isVictory = false;
        Master::sceneManager->SetNextScene(SceneManager::SCENE_RESULT);
    }
}
// 謾ｻ謦・・逅・
// 驕ｸ謚槭＆繧後※縺・ｋ謾ｻ謦・Δ繝ｼ繝会ｼ磯壼ｸｸ蠑ｾ縲∬ｿ第磁縲∝ｿ・ｮｺ謚・峨↓蠢懊§縺ｦ蠑ｾ繧堤函謌舌・逋ｺ蟆・＠縺ｾ縺吶・
void Player::Attack()
{
    int mouseInput = GetMouseInput(); // 繝槭え繧ｹ縺ｮ迥ｶ諷九ｒ蜿門ｾ・
    bool zPressed = InputManager::CheckPressKey(KEY_INPUT_Z);
    
    m_AttackInterval++;
    m_AttackInterval_2++;
    // Cooldown decrement
    if (m_specialCooldown > 0) {
        m_specialCooldown--;
    }
    
    // Z繧ｭ繝ｼ縺梧款縺輔ｌ縺ｦ縺・ｋ髢薙√Γ繧､繝ｳ繧ｷ繝ｧ繝・ヨ繧堤匱蟆・
    if ( m_AttackInterval >= m_attackTimer)
    {
        m_AttackInterval = 0;//interval縺ｮ蛻晄悄蛹・
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

    // 繧ｹ繝壹Ν繧ｫ繝ｼ繝峨・逋ｺ蜍包ｼ・繧ｭ繝ｼ・・
    if (InputManager::CheckPressKey(KEY_INPUT_X)) {
        if (m_spellGauge >= m_maxSpellGauge) {
            m_spellGauge = 0; // 繧ｲ繝ｼ繧ｸ豸郁ｲｻ
            new SpellCardBullet(m_x, m_y - 90.0f);
            
            GameScene* gs = dynamic_cast<GameScene*>(Master::sceneManager->GetCurrentScene());
            if (gs != nullptr) {
                gs->TriggerCutin();
            }
        }
    }
}

// 邨碁ｨ灘､・・P・峨・迯ｲ蠕励→繝ｬ繝吶Ν繧｢繝・・蜃ｦ逅・
// 謨ｵ繧貞偵＠縺滓凾縺ｫ蜻ｼ縺ｰ繧後∽ｸ螳壼､繧定ｶ・∴繧九→繝ｬ繝吶Ν繧｢繝・・縺励※HP繧貞・蝗槫ｾｩ縺励∪縺吶・
void Player::AddXp(int amount) {
    m_xp += amount;
    
    // 繧ｹ繝壹Ν繧ｲ繝ｼ繧ｸ繧ゆｸ邱偵↓蠅怜刈縺輔○繧・
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

// 莉悶・繧ｪ繝悶ず繧ｧ繧ｯ繝医→驥阪↑縺｣縺ｦ縺・ｋ譎ゅ・蜃ｦ逅・
// 謨ｵ譛ｬ菴薙→縺ｶ縺､縺九▲縺溷ｴ蜷医↓繝繝｡繝ｼ繧ｸ繧貞女縺代∪縺吶・
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