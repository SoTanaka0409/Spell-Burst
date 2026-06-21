#include "MasterSpark.h"
#include "CapsuleCollider.h"
#include "Enemy.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include "Utility.h"
#include <cmath>

MasterSpark::MasterSpark(float x, float y)
    : Projectile(Vector2(x, y), Vector2(0, -1), 0.0f, 1)
{
    SetTag(Tag2D_PlayerBullet);
    m_maxLife = 120;
    m_lifeTimer = m_maxLife;
    m_radius = 50.0f;
    m_colorHue = 0;
    m_AttackCount = 0;

    mpCollider = new CapsuleCollider(this, Vector2(mvPosition.x, mvPosition.y), Vector2(mvPosition.x, mvPosition.y - 1200.0f), m_radius);
}

MasterSpark::~MasterSpark() {
}

void MasterSpark::Update() {
    m_lifeTimer--;
    if (m_lifeTimer <= 0) {
        Projectile::Kill(); // 寿命が来たら消滅
        return;
    }

    if (m_lifeTimer < 20) {
        m_radius = 50.0f * (m_lifeTimer / 20.0f);
        if (mpCollider) mpCollider->mfRadius = m_radius;
    } else if (m_maxLife - m_lifeTimer < 10) {
        m_radius = 50.0f * ((m_maxLife - m_lifeTimer) / 10.0f);
        if (mpCollider) mpCollider->mfRadius = m_radius;
    } else {
        m_radius = 50.0f;
    }

    m_colorHue += 15;
    if (m_colorHue >= 360) m_colorHue -= 360;

    if (mpCollider) {
        mpCollider->mvPosition = Vector2(mvPosition.x, mvPosition.y);
        mpCollider->mvPosition2 = Vector2(mvPosition.x, mvPosition.y - 1200.0f);
    }
}

void MasterSpark::Draw() {
    if (!m_isActive) return;

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
    for (int i = 0; i < 5; ++i) {
        float rad = (m_colorHue + i * 72) * 3.14159265f / 180.0f;
        int r = static_cast<int>(sin(rad) * 127 + 128);
        int g = static_cast<int>(sin(rad + 2.0f * 3.14159265f / 3.0f) * 127 + 128);
        int b = static_cast<int>(sin(rad + 4.0f * 3.14159265f / 3.0f) * 127 + 128);

        float drawRadius = m_radius * (1.0f - i * 0.1f);
        
        // Draw using Box and Circle like the original
        DrawBox(static_cast<int>(mvPosition.x - drawRadius), static_cast<int>(mvPosition.y - 1200.0f),
                static_cast<int>(mvPosition.x + drawRadius), static_cast<int>(mvPosition.y), GetColor(r, g, b), TRUE);
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), static_cast<int>(drawRadius), GetColor(r, g, b), TRUE);
    }

    SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
    float innerRadius = m_radius * 0.4f;
    DrawBox(static_cast<int>(mvPosition.x - innerRadius), static_cast<int>(mvPosition.y - 1200.0f),
            static_cast<int>(mvPosition.x + innerRadius), static_cast<int>(mvPosition.y), GetColor(255, 255, 255), TRUE);
    DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), static_cast<int>(innerRadius), GetColor(255, 255, 255), TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void MasterSpark::Kill() {
    // 貫通レーザーなので衝突で消滅しない
}

void MasterSpark::OnTrigger(Collider* collider, Collider* check) {
    if (check != nullptr && check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == Tag2D_Enemy) {
            Character* enemy = dynamic_cast<Character*>(check->GetParentObject());
            if (enemy != nullptr && m_lifeTimer % 5 == 0) {
                enemy->TakeDamage(m_damage);
                m_AttackCount++;
            }
        } else if (check->GetParentObject()->GetTag() == Tag2D_EnemyBullet) {
            check->GetParentObject()->SetDeleteFlag(true);
        }
    }
}

void MasterSpark::OnEnter(Collider* collider, Collider* check) {
}