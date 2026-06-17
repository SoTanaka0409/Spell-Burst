#include "PlayerHomingBullet.h"
#include "CapsuleCollider.h"
#include "Enemy.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include "Utility.h"
#include "ObjectManager.h"
#include "Master.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Boss.h"
#include <cmath>
#include <vector>

PlayerHomingBullet::PlayerHomingBullet(Vector2 pos, Vector2 dir, float speed)
    : Object2D(pos)
    , mpCollider(nullptr)
{
    SetTag(Tag2D_PlayerBullet);
    mvPosition = pos;
    m_dir = dir.Normalized();
    m_speed = speed;
    m_isActive = true;
    m_damage = 2;
    m_lifeTimer = 0;

    mpCollider = new CapsuleCollider(this, mvPosition, mvPosition, 10.0f);
}

PlayerHomingBullet::~PlayerHomingBullet() {
    if (mpCollider) {
        delete mpCollider;
        mpCollider = nullptr;
    }
}

void PlayerHomingBullet::Update() {
    if (!m_isActive) return;

    m_lifeTimer++;

    if (m_lifeTimer > 10) {
        ObjectManager* objManager = Master::sceneManager->GetCurrentScene()->GetObjectManager();
        std::vector<Object2D*> enemies = objManager->GetObject2DListByTag(Tag2D_Enemy);
        
        float nearestDistSq = -1.0f;
        Object2D* target = nullptr;

        for (auto* obj : enemies) {
            Enemy* e = dynamic_cast<Enemy*>(obj);
            if (e && e->IsActive() && !e->IsDeleteFlag()) {
                float distSq = e->GetPosition().DistanceSqTo(mvPosition);
                if (nearestDistSq < 0 || distSq < nearestDistSq) {
                    nearestDistSq = distSq;
                    target = e;
                }
            } else {
                Boss* b = dynamic_cast<Boss*>(obj);
                if (b && b->IsActive() && !b->IsDeleteFlag()) {
                    float distSq = b->GetPosition().DistanceSqTo(mvPosition);
                    if (nearestDistSq < 0 || distSq < nearestDistSq) {
                        nearestDistSq = distSq;
                        target = b;
                    }
                }
            }
        }

        if (target) {
            float currentAngle = Vector2(0, 0).AngleTo(m_dir);
            float targetAngle = mvPosition.AngleTo(target->GetPosition());

            float diff = targetAngle - currentAngle;
            while (diff <= -3.14159265f) diff += 2.0f * 3.14159265f;
            while (diff > 3.14159265f) diff -= 2.0f * 3.14159265f;

            float turnSpeed = 0.08f;
            if (diff > turnSpeed) currentAngle += turnSpeed;
            else if (diff < -turnSpeed) currentAngle -= turnSpeed;
            else currentAngle = targetAngle;

            m_dir = Vector2::FromAngle(currentAngle);
        }
    }

    mvPosition += m_dir * (m_speed * Utility::TimeScale);

    if (mpCollider) {
        mpCollider->mvPosition = mvPosition;
        mpCollider->mvPosition2 = mvPosition;
    }

    if (mvPosition.x < -50.0f || mvPosition.x > Utility::SCREEN_WIDTH + 50.0f || mvPosition.y < -50.0f || mvPosition.y > Utility::SCREEN_HEIGHT + 50.0f) {
        Kill();
    }
}

void PlayerHomingBullet::Draw() {
    if (!m_isActive) return;
    
    float seed = (mvPosition.x + mvPosition.y) * 0.01f;
    float angle1 = m_lifeTimer * (0.15f + seed * 0.01f) + seed;
    float angle2 = angle1 + 2.0f;
    float angle3 = angle1 + 4.0f;

    float r1 = 16.0f + std::sin(seed) * 4.0f;
    float r2 = 10.0f + std::cos(seed * 2.0f) * 3.0f;
    float r3 = 18.0f + std::sin(seed * 3.0f) * 5.0f;

    int x1 = static_cast<int>(mvPosition.x + std::cos(angle1) * r1);
    int y1 = static_cast<int>(mvPosition.y + std::sin(angle1) * r1);
    int x2 = static_cast<int>(mvPosition.x + std::cos(angle2) * r2);
    int y2 = static_cast<int>(mvPosition.y + std::sin(angle2) * r2);
    int x3 = static_cast<int>(mvPosition.x + std::cos(angle3) * r3);
    int y3 = static_cast<int>(mvPosition.y + std::sin(angle3) * r3);

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
    DrawTriangle(x1, y1, x2, y2, x3, y3, GetColor(0, 150, 255), TRUE);
    
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
    DrawTriangle(x1, y1, x2, y2, x3, y3, GetColor(150, 255, 255), FALSE);
    
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
    DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 3, GetColor(255, 255, 255), TRUE);

    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void PlayerHomingBullet::Kill() {
    m_isActive = false;
    SetDeleteFlag(true);
    if (mpCollider) {
        mpCollider->SetDeleteFlag(true);
    }
}

void PlayerHomingBullet::OnTrigger(Collider* collider, Collider* check) {
    if (check != nullptr && check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == Tag2D_Enemy) {
            Enemy* enemy = dynamic_cast<Enemy*>(check->GetParentObject());
            if (enemy != nullptr && enemy->IsActive() && !enemy->IsDeleteFlag()) {
                enemy->TakeDamage(m_damage);
                Kill();
            }
        }
    }
}