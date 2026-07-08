#include "PlayerSpellParticle.h"
#include "ObjectManager.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include "Utility.h"
#include <cmath>

PlayerSpellParticle::PlayerSpellParticle(Vector2 pos, Vector2 dir, float speed_)
    : Object2D(pos)
{
    SetTag(kTag2dPlayerBullet);
    position_ = pos;
    dir = dir.Normalized();
    speed_ = speed_;
    is_active_ = true;
    life_timer_ = 60;
    damage_ = 5;
}

PlayerSpellParticle::~PlayerSpellParticle() {
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

    if (life_timer_ > 20) {
        float currentAngle = Vector2(0,0).AngleTo(dir);
        currentAngle += 0.05f;
        dir = Vector2::FromAngle(currentAngle);
    }
}

void PlayerSpellParticle::Draw() {
    if (!is_active_) return;

    int alpha = (life_timer_ * 255) / 60;
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
    
    DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 15, GetColor(150, 255, 255), TRUE);
    DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 8, GetColor(255, 255, 255), TRUE);

    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void PlayerSpellParticle::OnTrigger(Collider* collider_, Collider* check) {
}
