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
    , mpCollider(nullptr)
{
    SetTag(obj); 
    m_deployInterval = 300.0f;
    m_activeDuration = 180.0f;
    m_timer = 0.0f;
    m_radius = radius;
    m_isDeployed = false;
    m_hitCount = 0;
}

Barrier::~Barrier() {
    if (mpCollider) {
        delete mpCollider;
        mpCollider = nullptr;
    }
}

void Barrier::Update() {
    m_timer += 1.0f * Utility::TimeScale;

    if (!m_isDeployed) {
        if (m_timer >= m_deployInterval) {
            m_isDeployed = true;
            SoundManager::GetInstance()->PlaySE("Resource/se_barrier.wav");
            m_timer = 0.0f;
            mpCollider = new CapsuleCollider(this, mvPosition, mvPosition, m_radius);
        }
    } else {
        if (m_timer >= m_activeDuration) {
            m_isDeployed = false;
            m_timer = 0.0f;
           
            if (mpCollider)
            {
                mpCollider->mvPosition = mvPosition;
                mpCollider->mvPosition2 = mvPosition;
            }
            if (mpCollider) {
                mpCollider->SetDeleteFlag(true);
                mpCollider = nullptr;
            }
        }
    }

    if (mpCollider) {
        mpCollider->mvPosition = mvPosition;
        mpCollider->mvPosition2 = mvPosition;
    }
}

void Barrier::Draw() {
    if (m_isDeployed) {
        int alpha = 150 + static_cast<int>(std::sin(GetNowCount() * 0.005f) * 50);
        SetDrawBlendMode(DX_BLENDMODE_ADD, alpha);
        
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), static_cast<int>(m_radius), GetColor(0, 50, 150), TRUE);
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), static_cast<int>(m_radius), GetColor(255, 255, 255), FALSE);
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), static_cast<int>(m_radius) - 1, GetColor(0, 255, 255), FALSE);
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), static_cast<int>(m_radius) + 1, GetColor(0, 255, 255), FALSE);
        
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
}

void Barrier::OnTrigger(Collider* collider, Collider* check) {
    if (!m_isDeployed) return;

    if (check != nullptr && check->GetParentObject() != nullptr) {
        auto tag = check->GetParentObject()->GetTag();
        if (this->GetTag() == tag2D_BarierPla && tag == Tag2D_EnemyBullet)
        {
            check->GetParentObject()->SetDeleteFlag(true);
            m_hitCount++;
            if (m_hitCount >= 30) {
                m_hitCount = 0;
                SoundManager::GetInstance()->PlaySE("Resource/SE/?K???X???????1.mp3");
                float baseSpeed = 10.0f;
                for (int dir = 0; dir < 4; ++dir) {
                    float baseAngle = dir * (3.14159265f / 2.0f);
                    for (int i = 0; i < 10; ++i) {
                        float spread = (i - 4.5f) * 0.1f; 
                        float angle = baseAngle + spread;
                        
                        Vector2 dir = Vector2::FromAngle(angle);
                        new PlayerHomingBullet(mvPosition + dir * 30.0f, dir, baseSpeed);
                    }
                }
            }
        }
        else if (GetTag() == tag2D_BarierEne && tag == Tag2D_PlayerBullet) {
            check->GetParentObject()->SetDeleteFlag(true);
        }
       
    }
}
