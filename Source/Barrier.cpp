#include "Barrier.h"
#include "CapsuleCollider.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include "Utility.h"
#include "PlayerHomingBullet.h"
#include "SoundManager.h"
#include <cmath>

Barrier::Barrier(float x, float y, float radius, Object2D::Tag2D obj)
    : Object2D(Vector2(x, y))
    , collider(nullptr)
{
    SetTag(obj); 
    deployInterval = 300.0f;
    activeDuration = 180.0f;
    timer = 0.0f;
    radius = radius;
    isDeployed = false;
    hitCount = 0;
}

Barrier::~Barrier() {
    if (collider) {
        delete collider;
        collider = nullptr;
    }
}

void Barrier::Update() {
    timer += 1.0f * Utility::TimeScale;

    if (!isDeployed) {
        if (timer >= deployInterval) {
            isDeployed = true;
            SoundManager::GetInstance()->PlaySE("Resource/se_barrier.wav");
            timer = 0.0f;
            collider = new CapsuleCollider(this, position, position, radius);
        }
    } else {
        if (timer >= activeDuration) {
            isDeployed = false;
            timer = 0.0f;
           
            if (collider)
            {
                collider->position = position;
                collider->position2 = position;
            }
            if (collider) {
                collider->SetDeleteFlag(true);
                collider = nullptr;
            }
        }
    }

    if (collider) {
        collider->position = position;
        collider->position2 = position;
    }
}

void Barrier::Draw() {
    if (isDeployed) {
        int alpha = 150 + static_cast<int>(std::sin(GetNowCount() * 0.005f) * 50);
        SetDrawBlendMode(DX_BLENDMODE_ADD, alpha);
        
        DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(radius), GetColor(0, 50, 150), TRUE);
        DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(radius), GetColor(255, 255, 255), FALSE);
        DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(radius) - 1, GetColor(0, 255, 255), FALSE);
        DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(radius) + 1, GetColor(0, 255, 255), FALSE);
        
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
}

void Barrier::OnTrigger(Collider* collider, Collider* check) {
    if (!isDeployed) return;

    if (check != nullptr && check->GetParentObject() != nullptr) {
        auto tag = check->GetParentObject()->GetTag();
        if (this->GetTag() == Tag2D_BarrierPlayer && tag == Tag2D_EnemyBullet)
        {
            check->GetParentObject()->SetDeleteFlag(true);
            hitCount++;
            if (hitCount >= 30) {
                hitCount = 0;
                SoundManager::GetInstance()->PlaySE("Resource/SE/?K???X???????1.3");
                float baseSpeed = 10.0f;
                for (int dir = 0; dir < 4; ++dir) {
                    float baseAngle = dir * (3.14159265f / 2.0f);
                    for (int i = 0; i < 10; ++i) {
                        float spread = (i - 4.5f) * 0.1f; 
                        float angle = baseAngle + spread;
                        
                        Vector2 dir = Vector2::FromAngle(angle);
                        new PlayerHomingBullet(position + dir * 30.0f, dir, baseSpeed);
                    }
                }
            }
        }
        else if (GetTag() == Tag2D_BarrierEnemy && tag == Tag2D_PlayerBullet) {
            check->GetParentObject()->SetDeleteFlag(true);
        }
       
    }
}
