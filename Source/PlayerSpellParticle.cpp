#include "PlayerSpellParticle.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include "Utility.h"
#include <cmath>

PlayerSpellParticle::PlayerSpellParticle(Vector2 pos, Vector2 dir, float speed)
    : Object2D(pos)
{
    SetTag(Tag2D_PlayerBullet);
    mvPosition = pos;
    m_dir = dir.Normalized();
    m_speed = speed;
    m_isActive = true;
    m_lifeTimer = 60;
    m_damage = 5;
}

PlayerSpellParticle::~PlayerSpellParticle() {
}

void PlayerSpellParticle::Update() {
    if (!m_isActive) return;

    m_lifeTimer--;
    if (m_lifeTimer <= 0) {
        m_isActive = false;
        SetDeleteFlag(true);
        return;
    }

    mvPosition += m_dir * (m_speed * Utility::TimeScale);

    if (mvPosition.x < -50.0f || mvPosition.x > Utility::SCREEN_WIDTH + 50.0f || mvPosition.y < -50.0f || mvPosition.y > Utility::SCREEN_HEIGHT + 50.0f) {
        m_isActive = false;
        SetDeleteFlag(true);
        return;
    }

    if (m_lifeTimer > 20) {
        float currentAngle = Vector2(0,0).AngleTo(m_dir);
        currentAngle += 0.05f;
        m_dir = Vector2::FromAngle(currentAngle);
    }
}

void PlayerSpellParticle::Draw() {
    if (!m_isActive) return;

    int alpha = (m_lifeTimer * 255) / 60;
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
    
    DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 15, GetColor(150, 255, 255), TRUE);
    DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 8, GetColor(255, 255, 255), TRUE);

    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void PlayerSpellParticle::OnTrigger(Collider* collider, Collider* check) {
}