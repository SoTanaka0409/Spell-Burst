#include "ExplosionParticle.h"
#include "Utility.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include <cmath>

ExplosionParticle::ExplosionParticle(float x, float y, float speed_, float angle, int color_, int life_time_, float size_)
    : Object2D(Vector2(x, y))
{
    vx_ = std::cos(angle) * speed_;
    vy_ = std::sin(angle) * speed_;
    life_time_ = life_time_;
    max_life_ = life_time_;
    color_ = color_;
    size_ = size_;
}

ExplosionParticle::~ExplosionParticle() {
}

void ExplosionParticle::Update() {
    position_.x += vx_ * Utility::TimeScale;
    position_.y += vy_ * Utility::TimeScale;
    
    vx_ *= 0.95f;
    vy_ *= 0.95f;

    life_time_--;
    if (life_time_ <= 0) {
        SetDeleteFlag(true);
    }
}

void ExplosionParticle::Draw() {
    int alpha = static_cast<int>(255.0f * (static_cast<float>(life_time_) / max_life_));
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
    
    float currentSize = size_ * (static_cast<float>(life_time_) / max_life_) + 1.0f;
    
    DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), static_cast<int>(currentSize), color_, TRUE);
    DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), static_cast<int>(currentSize * 0.5f), GetColor(255, 255, 255), TRUE);
    
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
