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
    position = pos;
    dir = dir.Normalized();
    speed = speed;
    isActive = true;
    lifeTimer = 60;
    damage = 5;
}

PlayerSpellParticle::~PlayerSpellParticle() {
}

void PlayerSpellParticle::Update() {
    if (!isActive) return;

    lifeTimer--;
    if (lifeTimer <= 0) {
        isActive = false;
        SetDeleteFlag(true);
        return;
    }

    position += dir * (speed * Utility::TimeScale);

    if (position.x < -50.0f || position.x > Utility::SCREEN_WIDTH + 50.0f || position.y < -50.0f || position.y > Utility::SCREEN_HEIGHT + 50.0f) {
        isActive = false;
        SetDeleteFlag(true);
        return;
    }

    if (lifeTimer > 20) {
        float currentAngle = Vector2(0,0).AngleTo(dir);
        currentAngle += 0.05f;
        dir = Vector2::FromAngle(currentAngle);
    }
}

void PlayerSpellParticle::Draw() {
    if (!isActive) return;

    int alpha = (lifeTimer * 255) / 60;
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
    
    DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), 15, GetColor(150, 255, 255), TRUE);
    DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), 8, GetColor(255, 255, 255), TRUE);

    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void PlayerSpellParticle::OnTrigger(Collider* collider, Collider* check) {
}