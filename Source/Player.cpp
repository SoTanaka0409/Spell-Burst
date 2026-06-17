#include "Player.h"
#include <cmath>
#include "InputManager.h"
#include "Bullet.h"
#include "CapsuleCollider.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
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
    : Object2D(Vector2((float)Utility::SCREEN_WIDTH / 2.0f, (float)Utility::SCREEN_HEIGHT / 2.0f))
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
void Player::Initialize() {
    mvPosition.x = (float)Utility::SCREEN_WIDTH / 2.0f;
    mvPosition.y = (float)Utility::SCREEN_HEIGHT / 2.0f;
   
    
    m_levelUpTimer = 0;
    m_stunTimer = 0;
    m_attackMode = AttackMode_Melee;
    m_specialCooldown = 0;
    mfAttack = 1;
    m_attackTimer = 20;
    m_AttackInterval =0 ;
    m_AttackTimer_2 = 60;
    m__BarrierCount = 0;

    m_level = 1;
    m_xp = 0;
    m_xpNeeded = 5;
    m_levelUpTimer = 0;                  
    
    m_spellGauge = 0;
    m_maxSpellGauge = 10;

    if (s_selectedCharacterType == 1)
    {
        m_speed = 5.0f;
        m_maxHp = 15;
        m_hp = m_maxHp;
    }
    else if (s_selectedCharacterType == 2)
    {
        m_speed = 7.0f;
        m_maxHp = 10;
        m_hp = m_maxHp;
    }
    else if (s_selectedCharacterType == 3)
    {
        m_speed = 5.0f;
        m_maxHp = 10;
        m_hp = m_maxHp;
        mfAttack = 2;
    }
    else
    {
        m_speed = 5.0f;
        m_maxHp = 10;
        m_hp = m_maxHp;
    }


    mpCollider = new CapsuleCollider(this, mvPosition, mvPosition, 4.0f);
	mpBarrier = new Barrier(mvPosition.x, mvPosition.y, 60.0f,tag2D_BarierPla);
}
void Player::Update()
{
    if (m_levelUpTimer > 0) {
        m_levelUpTimer--;
    }

    if (m_stunTimer > 0) {
        m_stunTimer--;

        if (mpCollider) {
            mpCollider->mvPosition = mvPosition;
            mpCollider->mvPosition2 = mvPosition;
        }
        return;
    }
    bool isFocus = InputManager::CheckPressKey(KEY_INPUT_LSHIFT);
    float currentSpeed = (isFocus ? 2.0f : m_speed) * Utility::TimeScale;

    if (InputManager::CheckPressKey(KEY_INPUT_W)) { mvPosition.y -= currentSpeed; }
    if (InputManager::CheckPressKey(KEY_INPUT_S)) { mvPosition.y += currentSpeed; }
    if (InputManager::CheckPressKey(KEY_INPUT_A)) { mvPosition.x -= currentSpeed; }
    if (InputManager::CheckPressKey(KEY_INPUT_D)) { mvPosition.x += currentSpeed; }


    if (mvPosition.x < 45.0f) mvPosition.x = 45.0f;
    if (mvPosition.x > Utility::SCREEN_WIDTH - 45.0f) mvPosition.x = Utility::SCREEN_WIDTH - 45.0f;
    if (mvPosition.y < 45.0f) mvPosition.y = 45.0f;
    if (mvPosition.y > Utility::SCREEN_HEIGHT - 45.0f) mvPosition.y = Utility::SCREEN_HEIGHT - 45.0f;

    mvPosition = Vector2(mvPosition.x, mvPosition.y);
    if (mpBarrier) {
        mpBarrier->SetPosition(mvPosition);
    }

    if (mpCollider) {
        mpCollider->mvPosition = mvPosition;
        mpCollider->mvPosition2 = mvPosition;
    }

    


    if (m_levelUpTimer > 0) {
        m_levelUpTimer--;
    }


    if (InputManager::CheckDownKey(KEY_INPUT_Q)) {
        
         if (m_attackMode == AttackMode_Melee) m_attackMode = AttackMode_Special;
        else m_attackMode = AttackMode_Melee;
    }
   


    Attack();
   
}
void Player::Draw() {

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
    if (true) {
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 5, GetColor(255, 255, 255), TRUE);
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 3, GetColor(255, 0, 0), TRUE);
    }
}
void Player::TakeDamage(int damage) {
    m_hp -= damage;
    SoundManager::GetInstance()->PlaySE("Resource/SE/弓矢が刺さる.mp3");
    if (m_hp <= 0) {
        m_hp = 0;
        ResultScene::s_isVictory = false;
        Master::sceneManager->SetNextScene(SceneManager::SCENE_RESULT);
    }
}


void Player::Attack()
{
    int mouseInput = GetMouseInput();
    bool zPressed = InputManager::CheckPressKey(KEY_INPUT_Z);
    
    m_AttackInterval++;
    m_AttackInterval_2++;

    if (m_specialCooldown > 0) {
        m_specialCooldown--;
    }
    if ( m_AttackInterval >= m_attackTimer)
    {
        m_AttackInterval = 0;
            int numBullets = m_level;
            float spacing = 20.0f;
            
    // 現在のレベル(numBullets)に応じて、複数発の弾を横一列に等間隔で配置するためのオフセット計算
    float startX = mvPosition.x - (numBullets - 1) * spacing / 2.0f;
            for (int i = 0; i < numBullets; ++i) 
            {
                new Bullet(startX + i * spacing, mvPosition.y - 45.0f, static_cast<int>(mfAttack));
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
                    m_specialCooldown = 180; 
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
    if (mouseInput&&MOUSE_INPUT_LEFT) 
    {
        if (m_spellGauge >= m_maxSpellGauge) {
            m_spellGauge = 0;
            SoundManager::GetInstance()->PlaySE("Resource/SE/剣で斬めE.mp3");
            
            if (s_selectedCharacterType == 1)
            {
                SoundManager::GetInstance()->PlaySE("Resource/SE/気弾2.mp3");
                new MasterSpark(mvPosition.x, mvPosition.y);
            } else if (s_selectedCharacterType == 2) {
                SoundManager::GetInstance()->PlaySE("Resource/SE/聖魔況Emp3");
                new RainbowWaveManager(mvPosition.x, mvPosition.y);
            } else if (s_selectedCharacterType == 3) {
                SoundManager::GetInstance()->PlaySE("Resource/SE/気弾2.mp3");
                new SpellCardBullet(mvPosition.x, mvPosition.y - 90.0f);
            }
            
            GameScene* gs = dynamic_cast<GameScene*>(Master::sceneManager->GetCurrentScene());
            if (gs != nullptr) {
                gs->TriggerCutin();
            }
        }
    }
}
void Player::AddXp(int amount) {
    m_xp += amount;
    int oldGauge = m_spellGauge;
    m_spellGauge += amount;
    if (m_spellGauge >= m_maxSpellGauge) {
        m_spellGauge = m_maxSpellGauge;
        if (oldGauge < m_maxSpellGauge) {
            SoundManager::GetInstance()->PlaySE("Resource/SE/スチE?Eタス上?E魔況E.mp3");
        }
    }

    while (m_xp >= m_xpNeeded) {
        m_xp -= m_xpNeeded;
        m_level++;
        SoundManager::GetInstance()->PlaySE("Resource/SE/スチE?Eタス上?E魔況E.mp3");
        m_xpNeeded = m_level * 5;

        m_hp = m_maxHp;
        m_levelUpTimer = 120;
    }
}

void Player::OnEnter(Collider* collider, Collider* check) {}
void Player::OnTrigger(Collider* collider, Collider* check) 
{
   
    if (check != nullptr && check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == Tag2D_Enemy) {
            Enemy* enemy = dynamic_cast<Enemy*>(check->GetParentObject());
            if (enemy != nullptr) {
                TakeDamage(1);

            }
        }
    }
}
void Player::OnExit(Collider* collider, Collider* check) {}
