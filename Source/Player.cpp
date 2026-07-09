#include "Player.h"
#include "ObjectManager.h"
#include <cmath>
#include <algorithm>
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
#include "Barrier.h"
#include "ResourceManager.h"
#include "GameScene.h"
#include "SoundManager.h"
#include"DebugLog.h"

int Player::kSelectedCharacterType = 1;

Player::Player() 
    : Character(Vector2((float)Utility::SCREEN_WIDTH / 2.0f, (float)Utility::SCREEN_HEIGHT / 2.0f), 15, 5.0f)
{
    SetTag(kTag2dPlayer);
    Initialize();
}

Player::~Player() {
    if (auto b = barrier_.lock()) {
        b->SetDeleteFlag(true);
        barrier_.reset();
    }
}

void Player::Initialize() {
    position_.x = (float)Utility::SCREEN_WIDTH / 2.0f;
    position_.y = (float)Utility::SCREEN_HEIGHT / 2.0f;
    
    level_up_timer_ = 0;
    stun_timer_ = 0;
    attack_mode_ = kAttackModeMelee;
    special_cooldown_ = 0;
    attack = 1;
    attack_timer_ = 20;
    attack_interval_ = 0;
    attack_timer2_ = 60;
    barrier_count_ = 0;

    level_ = 1;
    xp_ = 0;
    xp_needed_ = 5;
    level_up_timer_ = 0;                  
    
    spell_gauge_ = 0;
    max_spell_gauge_ = 10;

    if (kSelectedCharacterType == 1)
    {
        speed_ = 5.0f;
        max_hp_ = 15;
        hp_ = max_hp_;
    }
    else if (kSelectedCharacterType == 2)
    {
        speed_ = 7.0f;
        max_hp_ = 10;
        hp_ = max_hp_;
    }
    else if (kSelectedCharacterType == 3)
    {
        speed_ = 5.0f;
        max_hp_ = 10;
        hp_ = max_hp_;
        attack = 2;
    }
    else
    {
        speed_ = 5.0f;
        max_hp_ = 10;
        hp_ = max_hp_;
    }

    if (collider_) delete collider_;
    collider_ = new CapsuleCollider(this, position_, position_, 4.0f);
    barrier_ = ObjectManager::Instantiate<Barrier>(position_.x, position_.y, 60.0f, Object2D::kTag2dBarrierPlayer);
}

void Player::Update()
{
    Character::Update(); // スタンタイマーなどの処理

    if (level_up_timer_ > 0) {
        level_up_timer_--;
    }

    if (stun_timer_ > 0) {
        return;
    }

    bool isFocus = InputManager::ActionPress(InputAction::kFocus);
    float currentSpeed = (isFocus ? 2.0f : speed_) * Utility::TimeScale;

    if (InputManager::ActionPress(InputAction::kMoveUp))    { position_.y -= currentSpeed; }
    if (InputManager::ActionPress(InputAction::kMoveDown))  { position_.y += currentSpeed; }
    if (InputManager::ActionPress(InputAction::kMoveLeft))  { position_.x -= currentSpeed; }
    if (InputManager::ActionPress(InputAction::kMoveRight)) { position_.x += currentSpeed; }

    // 画面端からはみ出さないように座標を制限（clampを使用）
    position_.x = std::clamp(position_.x, 45.0f, Utility::SCREEN_WIDTH - 45.0f);
    position_.y = std::clamp(position_.y, 45.0f, Utility::SCREEN_HEIGHT - 45.0f);

    if (auto b = barrier_.lock()) {
        b->SetPosition(position_);
    }

    if (InputManager::ActionDown(InputAction::kSwitchMode)) {
        if (attack_mode_ == kAttackModeMelee) attack_mode_ = kAttackModeSpecial;
        else attack_mode_ = kAttackModeMelee;
    }

    Attack();
}

void Player::Draw() {
    if (auto b = barrier_.lock()) {
        if (b->IsDeployed() && b->GetHitCount() > 0) {
            int hit_count = b->GetHitCount();
        float ratio = static_cast<float>(hit_count) / 30.0f;
        
        SetDrawBlendMode(DX_BLENDMODE_ADD, static_cast<int>(255 * ratio * 0.8f));
        int auraColor = (hit_count >= 30) ? GetColor(255, 255, 100) : GetColor(100, 200, 255);
        
        for (int i = 0; i < 5; i++) {
            float radiusBase = 60.0f + sinf(GetNowCount() * 0.005f + i) * 10.0f;
            DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), static_cast<int>(radiusBase - i * 5), auraColor, TRUE);
        }
        
        int time = GetNowCount();
        int numParticles = static_cast<int>(15 * ratio);
        for (int i = 0; i < numParticles; i++) {
            float angle = (time * 0.002f) + (i * DX_PI_F * 2.0f / numParticles);
            float dist = 40.0f + sinf(time * 0.005f + i * 1.5f) * 15.0f;
            int px = static_cast<int>(position_.x + cosf(angle) * dist);
            int py = static_cast<int>(position_.y + sinf(angle) * dist);
            DrawCircle(px, py, 6 + i % 3, auraColor, TRUE);
        }
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        }
    }

    if (stun_timer_ > 0) {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
        DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 50, GetColor(0, 200, 255), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }

    int playerGraphHandle = -1;
    if (kSelectedCharacterType == 1) {
        playerGraphHandle = ResourceManager::GetInstance()->GetGraph("Resource/player.png");
    } else if (kSelectedCharacterType == 2) {
        playerGraphHandle = ResourceManager::GetInstance()->GetGraph("Resource/player2.png");
    } else if (kSelectedCharacterType == 3) {
        playerGraphHandle = ResourceManager::GetInstance()->GetGraph("Resource/player3.png");
    }

    if (playerGraphHandle != -1) {
        DrawExtendGraph(
            static_cast<int>(position_.x - 45.0f), 
            static_cast<int>(position_.y - 45.0f), 
            static_cast<int>(position_.x + 45.0f), 
            static_cast<int>(position_.y + 45.0f), 
            playerGraphHandle, 
            TRUE
        );
    } else {
        DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 45, GetColor(0, 255, 0), TRUE);
    }
    if (true) {
        DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 5, GetColor(255, 255, 255), TRUE);
        DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 3, GetColor(255, 0, 0), TRUE);
    }
}

void Player::TakeDamage(int damage_) {
    Character::TakeDamage(damage_);
    SoundManager::GetInstance()->PlaySE("Resource/SE/se_button1.mp3");

    // 被弾演出: スクリーンシェイク + ダメージフラッシュ（赤）
    GameScene* scene = dynamic_cast<GameScene*>(Master::sceneManager->GetCurrentScene());
    if (scene != nullptr) {
        scene->AddScreenShake(8, 6.0f);
        scene->AddDamageFlash(15, GetColor(255, 30, 30));
    }

    if (hp_ <= 0) {
        ResultScene::kIsVictory = false;
        Master::sceneManager->SetNextScene(SceneManager::SCENE_RESULT);
    }
}

void Player::Attack()
{
    int mouseInput = GetMouseInput();
    bool zPressed = InputManager::ActionPress(InputAction::kAttack);
    
    attack_interval_++;
    attack_interval2_++;

    if (special_cooldown_ > 0) {
        special_cooldown_--;
    }
    if ( attack_interval_ >= attack_timer_)
    {
        attack_interval_ = 0;
        int numBullets = level_;
        float spacing = 20.0f;
            
        float startX = position_.x - (numBullets - 1) * spacing / 2.0f;
        for (int i = 0; i < numBullets; ++i) 
        {
            ObjectManager::Instantiate<Bullet>(startX + i * spacing, position_.y - 45.0f, static_cast<int>(attack));
        }
    }
    if (DebugOn)
    {
        if (mouseInput & MOUSE_INPUT_LEFT && attack_interval2_ >= attack_timer2_)
        {
            attack_interval2_ = 0;
            if (attack_mode_ == kAttackModeMelee) {
                ObjectManager::Instantiate<MeleeAttack>(position_.x, position_.y - 70.0f);
            }
            else if (attack_mode_ == kAttackModeSpecial)
            {
                if (special_cooldown_ == 0)
                {
                    ObjectManager::Instantiate<SpecialBullet>(position_.x, position_.y - 90.0f);
                    special_cooldown_ = 180; 
                }
            }
        }
    }
    if (mouseInput & MOUSE_INPUT_LEFT)
    {
        if (DebugOn)
        {
            ObjectManager::Instantiate<SpecialBullet>(position_.x, position_.y - 90.0f);
        }
    }
    if (mouseInput&&MOUSE_INPUT_LEFT) 
    {
        if (spell_gauge_ >= max_spell_gauge_) {
            spell_gauge_ = 0;
            SoundManager::GetInstance()->PlaySE("Resource/SE/se_button1.mp3");
            
            if (kSelectedCharacterType == 1)
            {
                SoundManager::GetInstance()->PlaySE("Resource/SE/se_button1.mp3");
                ObjectManager::Instantiate<MasterSpark>(position_.x, position_.y);
            } else if (kSelectedCharacterType == 2) {
                SoundManager::GetInstance()->PlaySE("Resource/SE/se_barrier_hit.mp3聖魔況Emp3");
                ObjectManager::Instantiate<RainbowWaveManager>(position_.x, position_.y);
            } else if (kSelectedCharacterType == 3) {
                SoundManager::GetInstance()->PlaySE("Resource/SE/se_button1.mp3");
                ObjectManager::Instantiate<SpellCardBullet>(position_.x, position_.y - 90.0f);
            }
            
            GameScene* gs = dynamic_cast<GameScene*>(Master::sceneManager->GetCurrentScene());
            if (gs != nullptr) {
                gs->TriggerCutin();
            }
        }
    }
}

void Player::AddXp(int amount) {
    xp_ += amount;
    int oldGauge = spell_gauge_;
    spell_gauge_ += amount;
    if (spell_gauge_ >= max_spell_gauge_) {
        spell_gauge_ = max_spell_gauge_;
        if (oldGauge < max_spell_gauge_) {
            SoundManager::GetInstance()->PlaySE("Resource/SE/se_button1.mp3");
        }
    }

    while (xp_ >= xp_needed_) {
        xp_ -= xp_needed_;
        level_++;
        SoundManager::GetInstance()->PlaySE("Resource/SE/se_button1.mp3");
        xp_needed_ = level_ * 5;

        hp_ = max_hp_;
        level_up_timer_ = 120;
    }
}

void Player::OnEnter(Collider* collider_, Collider* check) {}
void Player::OnTrigger(Collider* collider_, Collider* check) 
{
    if (check != nullptr && check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == kTag2dEnemy) {
            Character* enemy = dynamic_cast<Character*>(check->GetParentObject());
            if (enemy != nullptr) {
                TakeDamage(1);
            }
        }
    }
}
void Player::OnExit(Collider* collider_, Collider* check) {}
void Player::RunBarrierAttack() {}
