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
    : Projectile(pos, dir.Normalized(), speed, 5) // ★球のダメージを5に増加
{
    SetTag(Tag2D_PlayerBullet);
    m_lifeTimer = 60 * 3;
    
    mpCollider = new CapsuleCollider(this, mvPosition, mvPosition, 15.0f);
}

PlayerHomingBullet::~PlayerHomingBullet() {
}

void PlayerHomingBullet::Update() {
    m_lifeTimer--;
    if (m_lifeTimer <= 0) {
        Kill();
        return;
    }

    Object2D* targetEnemy = nullptr;
    float minDistSq = 9999999.0f;

    auto enemies = Master::sceneManager->GetCurrentScene()->GetObjectManager()->GetObject2DListByTag(Tag2D_Enemy);
    for (auto* obj : enemies) {
        Character* e = dynamic_cast<Character*>(obj);
        if (e && !e->IsDeleteFlag() && e->GetY() > 0) {
            float distSq = e->GetPosition().DistanceSqTo(mvPosition);
            if (distSq < minDistSq && distSq < 400.0f * 400.0f) {
                minDistSq = distSq;
                targetEnemy = e;
            }
        }
    }

    if (targetEnemy) {
        float currentAngle = Vector2(0, 0).AngleTo(m_dir);
        float targetAngle = mvPosition.AngleTo(targetEnemy->GetPosition());
        float diff = targetAngle - currentAngle;
        while (diff > 3.14159265f) diff -= 2.0f * 3.14159265f;
        while (diff < -3.14159265f) diff += 2.0f * 3.14159265f;
        float turnSpeed = 0.1f * Utility::TimeScale;
        if (diff > turnSpeed) currentAngle += turnSpeed;
        else if (diff < -turnSpeed) currentAngle -= turnSpeed;
        else currentAngle = targetAngle;
        m_dir = Vector2::FromAngle(currentAngle);
    }

    mvPosition += m_dir * (m_speed * Utility::TimeScale);

    Projectile::Update();

    if (IsOutOfBounds()) {
        Kill();
    }
}

void PlayerHomingBullet::Draw() {
    if (!m_isActive) return;
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
    DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 15, GetColor(0, 255, 128), TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 8, GetColor(100, 255, 200), TRUE);
}

void PlayerHomingBullet::OnTrigger(Collider* collider, Collider* check) {
    if(check!=nullptr&&check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == tag2D_BarierEne)
        {
            Kill();
            return;
		}
	}

    if (check != nullptr && check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == Tag2D_Enemy) {
            // ★敵にダメージを与える処理を追加
            Character* enemy = dynamic_cast<Character*>(check->GetParentObject());
            if (enemy != nullptr) {
                enemy->TakeDamage(m_damage);
            }
            Kill();
        }
    }
}