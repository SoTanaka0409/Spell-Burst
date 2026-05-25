#include "PlayerHomingBullet.h"
#include "CapsuleCollider.h"
#include "Enemy.h"
#include "DxLib.h"
#include "Utility.h"
#include "ObjectManager.h"
#include "Master.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Boss.h"
#include <cmath>
#include <vector>

PlayerHomingBullet::PlayerHomingBullet(float x, float y, float dx, float dy, float speed)
    : Object2D(VGet(x, y, 0.0f))
    , mpCollider(nullptr)
{
    SetTag(Tag2D_PlayerBullet);
    m_x = x;
    m_y = y;
    m_dx = dx;
    m_dy = dy;
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
                float dx = e->GetPosition().x - m_x;
                float dy = e->GetPosition().y - m_y;
                float distSq = dx * dx + dy * dy;
                if (nearestDistSq < 0 || distSq < nearestDistSq) {
                    nearestDistSq = distSq;
                    target = e;
                }
            } else {
                Boss* b = dynamic_cast<Boss*>(obj);
                if (b && b->IsActive() && !b->IsDeleteFlag()) {
                    float dx = b->GetPosition().x - m_x;
                    float dy = b->GetPosition().y - m_y;
                    float distSq = dx * dx + dy * dy;
                    if (nearestDistSq < 0 || distSq < nearestDistSq) {
                        nearestDistSq = distSq;
                        target = b;
                    }
                }
            }
        }

        if (target) {
            float tx = target->GetPosition().x - m_x;
            float ty = target->GetPosition().y - m_y;
            float targetAngle = std::atan2(ty, tx);
            float currentAngle = std::atan2(m_dy, m_dx);

            float diff = targetAngle - currentAngle;
            while (diff <= -3.14159265f) diff += 2.0f * 3.14159265f;
            while (diff > 3.14159265f) diff -= 2.0f * 3.14159265f;

            float turnSpeed = 0.08f;
            if (diff > turnSpeed) currentAngle += turnSpeed;
            else if (diff < -turnSpeed) currentAngle -= turnSpeed;
            else currentAngle = targetAngle;

            m_dx = std::cos(currentAngle);
            m_dy = std::sin(currentAngle);
        }
    }

    m_x += m_dx * m_speed * Utility::TimeScale;
    m_y += m_dy * m_speed * Utility::TimeScale;
    mvPosition = VGet(m_x, m_y, 0.0f);

    if (mpCollider) {
        mpCollider->mvPosition = mvPosition;
        mpCollider->mvPosition2 = mvPosition;
    }

    if (m_x < -50.0f || m_x > Utility::SCREEN_WIDTH + 50.0f || m_y < -50.0f || m_y > Utility::SCREEN_HEIGHT + 50.0f) {
        Kill();
    }
}

void PlayerHomingBullet::Draw() {
    if (!m_isActive) return;

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
    DrawCircle(static_cast<int>(m_x), static_cast<int>(m_y), 15, GetColor(0, 255, 100), TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    DrawCircle(static_cast<int>(m_x), static_cast<int>(m_y), 8, GetColor(150, 255, 200), TRUE);
    DrawCircle(static_cast<int>(m_x), static_cast<int>(m_y), 4, GetColor(255, 255, 255), TRUE);
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
