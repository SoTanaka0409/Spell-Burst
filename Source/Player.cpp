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

int Player::selectedCharacterType = 1;

Player::Player() 
    : Character(Vector2((float)Utility::SCREEN_WIDTH / 2.0f, (float)Utility::SCREEN_HEIGHT / 2.0f), 15, 5.0f)
{
    SetTag(Tag2D_Player);
    Initialize();
}

Player::~Player() {
    if (barrier) {
        barrier->SetDeleteFlag(true);
        barrier = nullptr;
    }
}

void Player::Initialize() {
    position.x = (float)Utility::SCREEN_WIDTH / 2.0f;
    position.y = (float)Utility::SCREEN_HEIGHT / 2.0f;
    
    levelUpTimer = 0;
    stunTimer = 0;
    attackMode = AttackMode_Melee;
    specialCooldown = 0;
    attack = 1;
    attackTimer = 20;
    attackInterval = 0;
    attackTimer2 = 60;
    barrierCount = 0;

    level = 1;
    xp = 0;
    xpNeeded = 5;
    levelUpTimer = 0;                  
    
    spellGauge = 0;
    maxSpellGauge = 10;

    if (selectedCharacterType == 1)
    {
        speed = 5.0f;
        maxHp = 15;
        hp = maxHp;
    }
    else if (selectedCharacterType == 2)
    {
        speed = 7.0f;
        maxHp = 10;
        hp = maxHp;
    }
    else if (selectedCharacterType == 3)
    {
        speed = 5.0f;
        maxHp = 10;
        hp = maxHp;
        attack = 2;
    }
    else
    {
        speed = 5.0f;
        maxHp = 10;
        hp = maxHp;
    }

    if (collider) delete collider;
    collider = new CapsuleCollider(this, position, position, 4.0f);
	barrier = new Barrier(position.x, position.y, 60.0f,Tag2D_BarrierPlayer);
}

void Player::Update()
{
    Character::Update(); // スタンタイマーなどの処理

    if (levelUpTimer > 0) {
        levelUpTimer--;
    }

    if (stunTimer > 0) {
        return;
    }

    bool isFocus = InputManager::CheckPressKey(KEY_INPUT_LSHIFT);
    float currentSpeed = (isFocus ? 2.0f : speed) * Utility::TimeScale;

    if (InputManager::CheckPressKey(KEY_INPUT_W)) { position.y -= currentSpeed; }
    if (InputManager::CheckPressKey(KEY_INPUT_S)) { position.y += currentSpeed; }
    if (InputManager::CheckPressKey(KEY_INPUT_A)) { position.x -= currentSpeed; }
    if (InputManager::CheckPressKey(KEY_INPUT_D)) { position.x += currentSpeed; }

    if (position.x < 45.0f) position.x = 45.0f;
    if (position.x > Utility::SCREEN_WIDTH - 45.0f) position.x = Utility::SCREEN_WIDTH - 45.0f;
    if (position.y < 45.0f) position.y = 45.0f;
    if (position.y > Utility::SCREEN_HEIGHT - 45.0f) position.y = Utility::SCREEN_HEIGHT - 45.0f;

    if (barrier) {
        barrier->SetPosition(position);
    }

    if (InputManager::CheckDownKey(KEY_INPUT_Q)) {
        if (attackMode == AttackMode_Melee) attackMode = AttackMode_Special;
        else attackMode = AttackMode_Melee;
    }

    Attack();
}

void Player::Draw() {
    if (barrier != nullptr && barrier->IsDeployed() && barrier->GetHitCount() > 0) {
        int hitCount = barrier->GetHitCount();
        float ratio = static_cast<float>(hitCount) / 30.0f;
        
        SetDrawBlendMode(DX_BLENDMODE_ADD, static_cast<int>(255 * ratio * 0.8f));
        int auraColor = (hitCount >= 30) ? GetColor(255, 255, 100) : GetColor(100, 200, 255);
        
        for (int i = 0; i < 5; i++) {
            float radiusBase = 60.0f + sinf(GetNowCount() * 0.005f + i) * 10.0f;
            DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(radiusBase - i * 5), auraColor, TRUE);
        }
        
        int time = GetNowCount();
        int numParticles = static_cast<int>(15 * ratio);
        for (int i = 0; i < numParticles; i++) {
            float angle = (time * 0.002f) + (i * DX_PI_F * 2.0f / numParticles);
            float dist = 40.0f + sinf(time * 0.005f + i * 1.5f) * 15.0f;
            int px = static_cast<int>(position.x + cosf(angle) * dist);
            int py = static_cast<int>(position.y + sinf(angle) * dist);
            DrawCircle(px, py, 6 + i % 3, auraColor, TRUE);
        }
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }

    if (stunTimer > 0) {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
        DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), 50, GetColor(0, 200, 255), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }

    int playerGraphHandle = -1;
    if (selectedCharacterType == 1) {
        playerGraphHandle = ResourceManager::GetInstance()->GetGraph("Resource/player.png");
    } else if (selectedCharacterType == 2) {
        playerGraphHandle = ResourceManager::GetInstance()->GetGraph("Resource/player2.png");
    } else if (selectedCharacterType == 3) {
        playerGraphHandle = ResourceManager::GetInstance()->GetGraph("Resource/player3.png");
    }

    if (playerGraphHandle != -1) {
        DrawExtendGraph(
            static_cast<int>(position.x - 45.0f), 
            static_cast<int>(position.y - 45.0f), 
            static_cast<int>(position.x + 45.0f), 
            static_cast<int>(position.y + 45.0f), 
            playerGraphHandle, 
            TRUE
        );
    } else {
        DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), 45, GetColor(0, 255, 0), TRUE);
    }
    if (true) {
        DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), 5, GetColor(255, 255, 255), TRUE);
        DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), 3, GetColor(255, 0, 0), TRUE);
    }
}

void Player::TakeDamage(int damage) {
    Character::TakeDamage(damage);
    SoundManager::GetInstance()->PlaySE("Resource/SE/弓矢が刺さる.3");
    if (hp <= 0) {
        ResultScene::isVictory = false;
        Master::sceneManager->SetNextScene(SceneManager::SCENE_RESULT);
    }
}

void Player::Attack()
{
    int mouseInput = GetMouseInput();
    bool zPressed = InputManager::CheckPressKey(KEY_INPUT_Z);
    
    attackInterval++;
    attackInterval2++;

    if (specialCooldown > 0) {
        specialCooldown--;
    }
    if ( attackInterval >= attackTimer)
    {
        attackInterval = 0;
        int numBullets = level;
        float spacing = 20.0f;
            
        float startX = position.x - (numBullets - 1) * spacing / 2.0f;
        for (int i = 0; i < numBullets; ++i) 
        {
            new Bullet(startX + i * spacing, position.y - 45.0f, static_cast<int>(attack));
        }
    }
    if (DebugOn)
    {
        if (mouseInput & MOUSE_INPUT_LEFT && attackInterval2 >= attackTimer2)
        {
            attackInterval2 = 0;
            if (attackMode == AttackMode_Melee) {
                new MeleeAttack(position.x, position.y - 70.0f);
            }
            else if (attackMode == AttackMode_Special)
            {
                if (specialCooldown == 0)
                {
                    new SpecialBullet(position.x, position.y - 90.0f);
                    specialCooldown = 180; 
                }
            }
        }
    }
    if (mouseInput & MOUSE_INPUT_LEFT)
    {
        if (DebugOn)
        {
            new SpecialBullet(position.x, position.y - 90.0f);
        }
    }
    if (mouseInput&&MOUSE_INPUT_LEFT) 
    {
        if (spellGauge >= maxSpellGauge) {
            spellGauge = 0;
            SoundManager::GetInstance()->PlaySE("Resource/SE/剣で斬めE.3");
            
            if (selectedCharacterType == 1)
            {
                SoundManager::GetInstance()->PlaySE("Resource/SE/気弾2.3");
                new MasterSpark(position.x, position.y);
            } else if (selectedCharacterType == 2) {
                SoundManager::GetInstance()->PlaySE("Resource/SE/聖魔況Emp3");
                new RainbowWaveManager(position.x, position.y);
            } else if (selectedCharacterType == 3) {
                SoundManager::GetInstance()->PlaySE("Resource/SE/気弾2.3");
                new SpellCardBullet(position.x, position.y - 90.0f);
            }
            
            GameScene* gs = dynamic_cast<GameScene*>(Master::sceneManager->GetCurrentScene());
            if (gs != nullptr) {
                gs->TriggerCutin();
            }
        }
    }
}

void Player::AddXp(int amount) {
    xp += amount;
    int oldGauge = spellGauge;
    spellGauge += amount;
    if (spellGauge >= maxSpellGauge) {
        spellGauge = maxSpellGauge;
        if (oldGauge < maxSpellGauge) {
            SoundManager::GetInstance()->PlaySE("Resource/SE/スチE?Eタス上?E魔況E.3");
        }
    }

    while (xp >= xpNeeded) {
        xp -= xpNeeded;
        level++;
        SoundManager::GetInstance()->PlaySE("Resource/SE/スチE?Eタス上?E魔況E.3");
        xpNeeded = level * 5;

        hp = maxHp;
        levelUpTimer = 120;
    }
}

void Player::OnEnter(Collider* collider, Collider* check) {}
void Player::OnTrigger(Collider* collider, Collider* check) 
{
    if (check != nullptr && check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == Tag2D_Enemy) {
            Character* enemy = dynamic_cast<Character*>(check->GetParentObject());
            if (enemy != nullptr) {
                TakeDamage(1);
            }
        }
    }
}
void Player::OnExit(Collider* collider, Collider* check) {}
void Player::Barrier() {}