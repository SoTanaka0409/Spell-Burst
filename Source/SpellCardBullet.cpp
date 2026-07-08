#include "SpellCardBullet.h"
#include "ObjectManager.h"
#include "CapsuleCollider.h"
#include "Player.h"
#include "Master.h"
#include "SceneManager.h"
#include "Scene.h"
#include "EnemyBullet.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include "Utility.h"
#include "PlayerSpellParticle.h"

SpellCardBullet::SpellCardBullet(float x, float y)
    : Projectile(Vector2(x, y), Vector2(0, -1), 6.0f, 1)
{
    SetTag(kTag2dPlayerBullet);
    life_timer_ = 0;
    
    collider_ = new CapsuleCollider(this, position_, position_, 15.0f);
}

SpellCardBullet::~SpellCardBullet() {
}

void SpellCardBullet::Update() {
    position_ += dir * (speed_ * Utility::TimeScale);

    if (collider_) {
        collider_->position_ = position_;
        collider_->position2 = position_;
    }

    life_timer_++;

    if (IsOutOfBounds()) {
        Kill();
    }
}

void SpellCardBullet::Draw() {
    if (!is_active_) return;

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
    int r = 15 + static_cast<int>(sin(life_timer_ * 0.2f) * 5.0f);
    DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), r, GetColor(255, 100, 255), TRUE);
    DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), r - 5, GetColor(255, 255, 255), TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SpellCardBullet::OnTrigger(Collider* collider_, Collider* check) {
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
            Explode();
            Kill();
        }
    }
}

void SpellCardBullet::Explode() {
    // PlayerSpellParticle is an effect for spell card hit
    for (int i = 0; i < 8; i++) {
        float angle = i * 3.14159265f / 4.0f;
        Vector2 dir(cos(angle), sin(angle));
        ObjectManager::Instantiate<PlayerSpellParticle>(position_, dir, 3.0f);
    }
}


