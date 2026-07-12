#include "PlayerSpellParticle.h"
#include "ObjectManager.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include "Utility.h"
#include <cmath>
#include "Character.h"
#include "CapsuleCollider.h"

PlayerSpellParticle::PlayerSpellParticle(Vector2 pos, Vector2 dir, float speed_)
    : Object2D(pos)
{
    SetTag(kTag2dPlayerBullet);
    this->position_ = pos;
    this->dir = dir.Normalized();
    this->speed_ = speed_;
    this->is_active_ = true;
    this->life_timer_ = 180;
    this->damage_ = 5;
    this->collider_ = new CapsuleCollider(this, this->position_, this->position_, 15.0f);
}

PlayerSpellParticle::~PlayerSpellParticle() {
    if (collider_) {
        delete collider_;
        collider_ = nullptr;
    }
}

void PlayerSpellParticle::Kill() {
    is_active_ = false;
    SetDeleteFlag(true);
}

void PlayerSpellParticle::Update() {
    if (!is_active_) return;

    life_timer_--;
    if (life_timer_ <= 0) {
        is_active_ = false;
        SetDeleteFlag(true);
        return;
    }

    position_ += dir * (speed_ * Utility::TimeScale);

    if (position_.x < -50.0f || position_.x > Utility::SCREEN_WIDTH + 50.0f || position_.y < -50.0f || position_.y > Utility::SCREEN_HEIGHT + 50.0f) {
        is_active_ = false;
        SetDeleteFlag(true);
        return;
    }

    if (collider_) {
        collider_->position_ = position_;
        collider_->position2 = position_;
    }
}

void PlayerSpellParticle::Draw() {
    if (!is_active_) return;

    int alpha = (life_timer_ * 255) / 180;
    if (alpha > 255) alpha = 255;
    SetDrawBlendMode(DX_BLENDMODE_ADD, alpha);
    
    DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 15, GetColor(150, 255, 255), TRUE);
    DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 8, GetColor(255, 255, 255), TRUE);

    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void PlayerSpellParticle::OnTrigger(Collider* collider_, Collider* check) {
    if (check != nullptr && check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == kTag2dEnemy) {
            Character* enemy = dynamic_cast<Character*>(check->GetParentObject());
            if (enemy != nullptr) {
                enemy->TakeDamage(damage_);
            }
            Kill(); // 敵に当たったら消える
        } else if (check->GetParentObject()->GetTag() == kTag2dEnemyBullet) {
            check->GetParentObject()->SetDeleteFlag(true);
        }
    }
}
