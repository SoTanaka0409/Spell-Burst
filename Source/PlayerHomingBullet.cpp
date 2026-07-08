#include "PlayerHomingBullet.h"
#include "ObjectManager.h"
#include "CapsuleCollider.h"
#include "Enemy.h"
#include "Boss.h"
#include "Master.h"
#include "SceneManager.h"
#include "Scene.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include <cmath>
#include "utility.h"

PlayerHomingBullet::PlayerHomingBullet(Vector2 pos, Vector2 dir, float speed_)
    : Projectile(pos, dir.Normalized(), speed_, 5) // 笘・帥縺ｮ繝繝｡繝ｼ繧ｸ繧・縺ｫ蠅怜刈
{
    SetTag(kTag2dPlayerBullet);
    life_timer_ = 60 * 3;
    
    collider_ = new CapsuleCollider(this, position_, position_, 15.0f);
}

PlayerHomingBullet::~PlayerHomingBullet() {
}

void PlayerHomingBullet::Update() {
    life_timer_--;
    if (life_timer_ <= 0) {
        Kill();
        return;
    }

    Object2D* targetEnemy = nullptr;
    float minDistSq = 9999999.0f;

    auto enemies = Master::sceneManager->GetCurrentScene()->GetObjectManager()->GetObject2DListByTag(kTag2dEnemy);
    for (auto& obj : enemies) {
        Character* e = dynamic_cast<Character*>(obj.get());
        if (e && !e->IsDeleteFlag() && e->GetY() > 0) {
            float distSq = e->GetPosition().DistanceSqTo(position_);
            if (distSq < minDistSq && distSq < 400.0f * 400.0f) {
                minDistSq = distSq;
                targetEnemy = e;
            }
        }
    }

    if (targetEnemy) {
        float currentAngle = Vector2(0, 0).AngleTo(dir);
        float targetAngle = position_.AngleTo(targetEnemy->GetPosition());
        float diff = targetAngle - currentAngle;
        while (diff > 3.14159265f) diff -= 2.0f * 3.14159265f;
        while (diff < -3.14159265f) diff += 2.0f * 3.14159265f;
        float turnSpeed = 0.1f * Utility::TimeScale;
        if (diff > turnSpeed) currentAngle += turnSpeed;
        else if (diff < -turnSpeed) currentAngle -= turnSpeed;
        else currentAngle = targetAngle;
        dir = Vector2::FromAngle(currentAngle);
    }

    position_ += dir * (speed_ * Utility::TimeScale);

    Projectile::Update();

    if (IsOutOfBounds()) {
        Kill();
    }
}

void PlayerHomingBullet::Draw() {
    if (!is_active_) return;
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
    DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 15, GetColor(0, 255, 128), TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 8, GetColor(100, 255, 200), TRUE);
}

void PlayerHomingBullet::OnTrigger(Collider* collider_, Collider* check) {
    if(check!=nullptr&&check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == kTag2dBarrierEnemy)
        {
            Kill();
            return;
		}
	}

    if (check != nullptr && check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == kTag2dEnemy) {
            // 笘・雰縺ｫ繝繝｡繝ｼ繧ｸ繧剃ｸ弱∴繧句・逅・ｒ霑ｽ蜉
            Character* enemy = dynamic_cast<Character*>(check->GetParentObject());
            if (enemy != nullptr) {
                enemy->TakeDamage(damage_);
            }
            Kill();
        }
    }
}
