#include "PlayerHomingBullet.h"
#include "CapsuleCollider.h"
#include "Enemy.h"
#include "Boss.h"
#include "Master.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ObjectManager.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include <cmath>
#include "utility.h"

PlayerHomingBullet::PlayerHomingBullet(Vector2 pos, Vector2 dir, float speed)
    : Projectile(pos, dir.Normalized(), speed, 2)
{
    SetTag(Tag2D_PlayerBullet);
    lifeTimer = 60 * 3;
    
    collider = new CapsuleCollider(this, position, position, 15.0f);
}

PlayerHomingBullet::~PlayerHomingBullet() {
}

void PlayerHomingBullet::Update() {
    lifeTimer--;
    if (lifeTimer <= 0) {
        Kill();
        return;
    }

    Object2D* targetEnemy = nullptr;
    float minDistSq = 9999999.0f;

    auto enemies = Master::sceneManager->GetCurrentScene()->GetObjectManager()->GetObject2DListByTag(Tag2D_Enemy);
    for (auto* obj : enemies) {
        Character* e = dynamic_cast<Character*>(obj);
        if (e && !e->IsDeleteFlag() && e->GetY() > 0) {
            float distSq = e->GetPosition().DistanceSqTo(position);
            if (distSq < minDistSq && distSq < 400.0f * 400.0f) {
                minDistSq = distSq;
                targetEnemy = e;
            }
        }
    }

    if (targetEnemy) {
        float currentAngle = Vector2(0, 0).AngleTo(dir);
        float targetAngle = position.AngleTo(targetEnemy->GetPosition());
        float diff = targetAngle - currentAngle;
        while (diff > 3.14159265f) diff -= 2.0f * 3.14159265f;
        while (diff < -3.14159265f) diff += 2.0f * 3.14159265f;
        float turnSpeed = 0.1f * Utility::TimeScale;
        if (diff > turnSpeed) currentAngle += turnSpeed;
        else if (diff < -turnSpeed) currentAngle -= turnSpeed;
        else currentAngle = targetAngle;
        dir = Vector2::FromAngle(currentAngle);
    }

    position += dir * (speed * Utility::TimeScale);

    Projectile::Update();

    if (IsOutOfBounds()) {
        Kill();
    }
}

void PlayerHomingBullet::Draw() {
    if (!isActive) return;
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
    DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), 15, GetColor(0, 255, 128), TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), 8, GetColor(100, 255, 200), TRUE);
}

void PlayerHomingBullet::OnTrigger(Collider* collider, Collider* check) {
    if(check!=nullptr&&check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == Tag2D_BarrierEnemy)
        {
            Kill();
            return;
		}
	}

    if (check != nullptr && check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == Tag2D_Enemy) {
            Kill();
        }
    }
}