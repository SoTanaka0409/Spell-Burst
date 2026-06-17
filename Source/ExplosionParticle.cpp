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
    m_vx = std::cos(angle) * speed;
    m_vy = std::sin(angle) * speed;
    m_lifeTime = lifeTime;
    m_maxLife = lifeTime;
    m_color = color;
    m_size = size;
}

ExplosionParticle::~ExplosionParticle() {
}

void ExplosionParticle::Update() {
    mvPosition.x += m_vx * Utility::TimeScale;
    mvPosition.y += m_vy * Utility::TimeScale;
    
    m_vx *= 0.95f;
    m_vy *= 0.95f;

    m_lifeTime--;
    if (m_lifeTime <= 0) {
        SetDeleteFlag(true);
    }
}

void ExplosionParticle::Draw() {
    int alpha = static_cast<int>(255.0f * (static_cast<float>(m_lifeTime) / m_maxLife));
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
    
    float currentSize = m_size * (static_cast<float>(m_lifeTime) / m_maxLife) + 1.0f;
    
    DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), static_cast<int>(currentSize), m_color, TRUE);
    DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), static_cast<int>(currentSize * 0.5f), GetColor(255, 255, 255), TRUE);
    
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
