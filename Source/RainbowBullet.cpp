#include "RainbowBullet.h"
#include "ObjectManager.h"
#include "CapsuleCollider.h"
#include "Player.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include "Utility.h"
#include <cmath>

RainbowBullet::RainbowBullet(float x, float y)
    : Projectile(Vector2(x, y), Vector2(0, -1), 5.0f, 1)
{
    SetTag(kTag2dPlayerBullet);
    color_hue_ = 0;
    collider_ = new CapsuleCollider(this, position_, position_, 12.0f);
}

RainbowBullet::~RainbowBullet() {
}

void RainbowBullet::Update() {
    position_ += dir * (speed_ * Utility::TimeScale);

    color_hue_ += 5;
    if (color_hue_ >= 360) color_hue_ -= 360;

    Projectile::Update();

    if (IsOutOfBounds()) {
        Kill();
    }
}

void RainbowBullet::Draw() {
    if (!is_active_) return;

    float rad = color_hue_ * 3.14159265f / 180.0f;
    int r = static_cast<int>(sin(rad) * 127 + 128);
    int g = static_cast<int>(sin(rad + 2.0f * 3.14159265f / 3.0f) * 127 + 128);
    int b = static_cast<int>(sin(rad + 4.0f * 3.14159265f / 3.0f) * 127 + 128);
    
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
    DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 12, GetColor(r, g, b), TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 8, GetColor(255, 255, 255), TRUE);
}

void RainbowBullet::OnTrigger(Collider* collider_, Collider* check) {
    if(check!=nullptr&&check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == kTag2dBarrierEnemy)
        {
            Kill();
            return;
		}
	}
    if (check != nullptr && check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == kTag2dEnemy) {
            Character* enemy = dynamic_cast<Character*>(check->GetParentObject());
            if (enemy != nullptr) {
                enemy->TakeDamage(damage_);
            }
            Kill();
        }
    }
}
