#include "ExplosionParticle.h"
#include "Utility.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include <cmath>

ExplosionParticle::ExplosionParticle(float x, float y, float speed, float angle, int color, int lifeTime, float size)
    : Object2D(Vector2(x, y))
{
    vx = std::cos(angle) * speed;
    vy = std::sin(angle) * speed;
    lifeTime = lifeTime;
    maxLife = lifeTime;
    color = color;
    size = size;
}

ExplosionParticle::~ExplosionParticle() {
}

void ExplosionParticle::Update() {
    position.x += vx * Utility::TimeScale;
    position.y += vy * Utility::TimeScale;
    
    vx *= 0.95f;
    vy *= 0.95f;

    lifeTime--;
    if (lifeTime <= 0) {
        SetDeleteFlag(true);
    }
}

void ExplosionParticle::Draw() {
    int alpha = static_cast<int>(255.0f * (static_cast<float>(lifeTime) / maxLife));
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
    
    float currentSize = size * (static_cast<float>(lifeTime) / maxLife) + 1.0f;
    
    DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(currentSize), color, TRUE);
    DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(currentSize * 0.5f), GetColor(255, 255, 255), TRUE);
    
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
