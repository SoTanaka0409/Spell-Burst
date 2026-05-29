#include "Player.h"
#include <cmath>
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
#include "MasterSpark.h"
#include "RainbowWaveManager.h"
#include "SpellCardBullet.h"
#include "SpecialBullet.h"
#include "ResourceManager.h"
#include "GameScene.h"
#include "SoundManager.h"
#include"DebugLog.h"

int Player::s_selectedCharacterType = 1;

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
    if (mpBarrier) {
        mpBarrier->SetDeleteFlag(true);
        mpBarrier = nullptr;
    }
    m_levelUpTimer = 0;
    m_stunTimer = 0;
}

// 繝励Ξ繧､繝､繝ｼ縺ｮ蛻晄悄蛹門・逅・
// 繧ｲ繝ｼ繝髢句ｧ区凾繧・Μ繝医Λ繧､譎ゅ↓蜻ｼ縺ｰ繧後？P繧・Ξ繝吶Ν縲∝ｺｧ讓吶↑縺ｩ繧貞・譛溽憾諷九↓謌ｻ縺励∪縺吶・
void Player::Initialize() {
    mvPosition.x = (float)Utility::SCREEN_WIDTH / 2.0f;
    mvPosition.y = (float)Utility::SCREEN_HEIGHT / 2.0f;
   
    
    m_levelUpTimer = 0;
    m_stunTimer = 0;
    m_attackMode = AttackMode_Melee;
    m_specialCooldown = 0;
    mfAttack = 1;
    m_attackTimer = 20; // 騾具ｽｺ陝・・菫｣鬮ｫ譁撰ｽ帝￥・ｭ邵ｺ謫ｾ・ｼ逎ｯ竄ｬ・｣陝・・・ｼ繝ｻ
    m_AttackInterval =0 ;
    m_AttackTimer_2 = 60;
    m__BarrierCount = 0;
    // Level & XP system initialization
    m_level = 1;
    m_xp = 0;
    m_xpNeeded = 5; // Level 1 needs 5 XP to level up
    m_levelUpTimer = 0;                  
    
    m_spellGauge = 0;
    m_maxSpellGauge = 10; // 隰ｨ・ｵ10闖ｴ轣倥・邵ｺ・ｧ郢ｧ・ｲ郢晢ｽｼ郢ｧ・ｸMAX

    if (s_selectedCharacterType == 1)//逕ｷ諤ｧ
    {
        m_speed = 5.0f;
        m_maxHp = 15;
        m_hp = m_maxHp;
    }
    else if (s_selectedCharacterType == 2)//螂ｳ諤ｧ
    {
        m_speed = 7.0f;
        m_maxHp = 10;
        m_hp = m_maxHp;
    }
    else if (s_selectedCharacterType == 3)//縺翫§縺輔ｓ
    {
        m_speed = 5.0f;
        m_maxHp = 10;
        m_hp = m_maxHp;
        mfAttack = 2;//邏皮ｲ九↑轣ｫ蜉帙ｒ縺ゅ￡繧・
    }
    else
    {
        m_speed = 5.0f;
        m_maxHp = 10;
        m_hp = m_maxHp;
    }

    // Create a circular collider with small radius (Touhou style)
    mpCollider = new CapsuleCollider(this, mvPosition, mvPosition, 4.0f);
	mpBarrier = new Barrier(mvPosition.x, mvPosition.y, 60.0f,tag2D_BarierPla);
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
    
    // 繝舌Μ繧｢繧偵・繝ｬ繧､繝､繝ｼ縺ｫ霑ｽ蠕薙＆縺帙ｋ
    if (mpBarrier) {
        mpBarrier->SetPosition(mvPosition);
    }

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
    // Draw Barrier Aura
    if (mpBarrier != nullptr && mpBarrier->IsDeployed() && mpBarrier->GetHitCount() > 0) {
        int hitCount = mpBarrier->GetHitCount();
        float ratio = static_cast<float>(hitCount) / 30.0f;
        
        SetDrawBlendMode(DX_BLENDMODE_ADD, static_cast<int>(255 * ratio * 0.8f));
        int auraColor = (hitCount >= 30) ? GetColor(255, 255, 100) : GetColor(100, 200, 255);
        
        for (int i = 0; i < 5; i++) {
            float radiusBase = 60.0f + sinf(GetNowCount() * 0.005f + i) * 10.0f;
            DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), static_cast<int>(radiusBase - i * 5), auraColor, TRUE);
        }
        
        int time = GetNowCount();
        int numParticles = static_cast<int>(15 * ratio);
        for (int i = 0; i < numParticles; i++) {
            float angle = (time * 0.002f) + (i * DX_PI_F * 2.0f / numParticles);
            float dist = 40.0f + sinf(time * 0.005f + i * 1.5f) * 15.0f;
            int px = static_cast<int>(mvPosition.x + cosf(angle) * dist);
            int py = static_cast<int>(mvPosition.y + sinf(angle) * dist);
            DrawCircle(px, py, 6 + i % 3, auraColor, TRUE);
        }
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }

    if (m_stunTimer > 0) {
        // 繧ｹ繧ｿ繝ｳ荳ｭ縺ｯ髱偵＞蜀・ｒ謠冗判
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 50, GetColor(0, 200, 255), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }

    int s_playerGraphHandle = -1;
    if (s_selectedCharacterType == 1) {
        s_playerGraphHandle = ResourceManager::GetInstance()->GetGraph("Resource/player.png");
    } else if (s_selectedCharacterType == 2) {
        s_playerGraphHandle = ResourceManager::GetInstance()->GetGraph("Resource/player2.png");
    } else if (s_selectedCharacterType == 3) {
        s_playerGraphHandle = ResourceManager::GetInstance()->GetGraph("Resource/player3.png");
    }

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
    if (true) {
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 5, GetColor(255, 255, 255), TRUE); // 螟匁棧・育區・・
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 3, GetColor(255, 0, 0), TRUE); // 荳ｭ蠢・ｼ郁ｵ､・・
    }
}

// 繝繝｡繝ｼ繧ｸ繧貞女縺代ｋ蜃ｦ逅・
// 謨ｵ繧・雰縺ｮ蠑ｾ縺ｨ蠖薙◆縺｣縺滄圀縺ｫ蜻ｼ縺ｰ繧後？P繧呈ｸ帙ｉ縺励∪縺吶・P縺・縺ｫ縺ｪ繧九→繝ｪ繧ｶ繝ｫ繝育判髱｢・域風蛹暦ｼ峨↓遘ｻ陦後＠縺ｾ縺吶・
void Player::TakeDamage(int damage) {
    m_hp -= damage;
    SoundManager::GetInstance()->PlaySE("Resource/SE/蠑鍋泙縺悟絢縺輔ｋ.mp3");
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
            float startX = mvPosition.x - (numBullets - 1) * spacing / 2.0f;
            for (int i = 0; i < numBullets; ++i) 
            {
                new Bullet(startX + i * spacing, mvPosition.y - 45.0f, mfAttack);
            }
            
        
        
    }
    if (DebugOn)
    {
        if (mouseInput & MOUSE_INPUT_LEFT && m_AttackInterval_2 >= m_AttackTimer_2)
        {
            m_AttackInterval_2 = 0;
            if (m_attackMode == AttackMode_Melee) {
                new MeleeAttack(mvPosition.x, mvPosition.y - 70.0f);
            }
            else if (m_attackMode == AttackMode_Special)
            {
                if (m_specialCooldown == 0)
                {
                    new SpecialBullet(mvPosition.x, mvPosition.y - 90.0f);
                    m_specialCooldown = 180; // 3 seconds cooldown
                }
            }
        }
    }
    if (mouseInput & MOUSE_INPUT_LEFT)
    {
        if (DebugOn)
        {
            new SpecialBullet(mvPosition.x, mvPosition.y - 90.0f);
        }
    }

    // 繧ｹ繝壹Ν繧ｫ繝ｼ繝峨・逋ｺ蜍包ｼ・繧ｭ繝ｼ・・
    if (mouseInput&&MOUSE_INPUT_LEFT) 
    {
        if (m_spellGauge >= m_maxSpellGauge) {
            m_spellGauge = 0; // 繧ｲ繝ｼ繧ｸ豸郁ｲｻ
            SoundManager::GetInstance()->PlaySE("Resource/SE/蜑｣縺ｧ譁ｬ繧・.mp3");
            
            if (s_selectedCharacterType == 1)
            {
                SoundManager::GetInstance()->PlaySE("Resource/SE/豌怜ｼｾ2.mp3");
                new MasterSpark(mvPosition.x, mvPosition.y);
            } else if (s_selectedCharacterType == 2) {
                SoundManager::GetInstance()->PlaySE("Resource/SE/閨夜ｭ疲ｳ・mp3");
                new RainbowWaveManager(mvPosition.x, mvPosition.y);
            } else if (s_selectedCharacterType == 3) {
                SoundManager::GetInstance()->PlaySE("Resource/SE/豌怜ｼｾ2.mp3");
                new SpellCardBullet(mvPosition.x, mvPosition.y - 90.0f);
            }
            
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
    
    // 繧ｹ繝壹Ν繧ｲ繝ｼ繧ｸ荳頑・
    int oldGauge = m_spellGauge;
    m_spellGauge += amount;
    if (m_spellGauge >= m_maxSpellGauge) {
        m_spellGauge = m_maxSpellGauge;
        if (oldGauge < m_maxSpellGauge) {
            // 繧ｲ繝ｼ繧ｸ縺勲AX縺ｫ縺ｪ縺｣縺溽椪髢薙↓SE繧剃ｸ蝗槭□縺鷹ｳｴ繧峨☆
            SoundManager::GetInstance()->PlaySE("Resource/SE/繧ｹ繝・・繧ｿ繧ｹ荳頑・鬲疲ｳ・.mp3");
        }
    }
    // Level-up loop (handles multiple level-ups from one big XP gain)
    while (m_xp >= m_xpNeeded) {
        m_xp -= m_xpNeeded;
        m_level++;
        SoundManager::GetInstance()->PlaySE("Resource/SE/繧ｹ繝・・繧ｿ繧ｹ荳頑・鬲疲ｳ・.mp3");
        m_xpNeeded = m_level * 5; // Each level requires (level * 5) XP
        // Bonus on level up: full HP restore
        m_hp = m_maxHp;
        m_levelUpTimer = 120; // Show "LEVEL UP!" for 120 frames (~2 seconds)
    }
}

void Player::OnEnter(Collider* collider, Collider* check) {}

// 莉悶・繧ｪ繝悶ず繧ｧ繧ｯ繝医→驥阪↑縺｣縺ｦ縺・ｋ譎ゅ・蜃ｦ逅・
// 謨ｵ譛ｬ菴薙→縺ｶ縺､縺九▲縺溷ｴ蜷医↓繝繝｡繝ｼ繧ｸ繧貞女縺代∪縺吶・
void Player::OnTrigger(Collider* collider, Collider* check) 
{
   
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
