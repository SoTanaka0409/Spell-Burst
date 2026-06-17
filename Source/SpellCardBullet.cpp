#include "SpellCardBullet.h"
#include "CapsuleCollider.h"
#include "Enemy.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include "PlayerSpellParticle.h"
#include <cmath>
#include "Utility.h"
#include "SoundManager.h"

SpellCardBullet::SpellCardBullet(float x, float y)
    : Object2D(Vector2(x, y))
    , mpCollider(nullptr)
{
    SetTag(Tag2D_PlayerBullet);
    mvPosition.x = x;
    mvPosition.y = y;
    m_speed = 8.0f;
    m_isActive = true;
    m_damage = 10;
    m_lifeTimer = 60;

    mpCollider = new CapsuleCollider(this, mvPosition, mvPosition, 40.0f);
}

SpellCardBullet::~SpellCardBullet() {
    if (mpCollider) {
        delete mpCollider;
        mpCollider = nullptr;
    }
}

void SpellCardBullet::Update() {
    if (!m_isActive) return;

    mvPosition.y -= m_speed * Utility::TimeScale;
    mvPosition = Vector2(mvPosition.x, mvPosition.y);

    if (mpCollider) {
        mpCollider->mvPosition = mvPosition;
        mpCollider->mvPosition2 = mvPosition;
    }

    m_lifeTimer--;
    if (m_lifeTimer <= 0) {
        Explode();
    }
}

void SpellCardBullet::Draw() {
    if (!m_isActive) return;

    unsigned int colorOuter = GetColor(255, 100, 255);
    unsigned int colorInner = GetColor(255, 200, 255);

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
    DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 45, colorOuter, TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 25, colorInner, TRUE);
}

void SpellCardBullet::Explode() {
    if (!m_isActive) return;
    
    const float PI = 3.14159265f;
    
    // 5層に広がる多重の同心円（桜パターン）となる弾幕の移動方向ベクトルを計算する
    for (int ring = 1; ring <= 5; ring++) {
        float speed = 3.0f + ring * 1.5f;
        float baseAngle = ring * (PI / 8.0f);
        for (int i = 0; i < 16; i++) {
            float angle = baseAngle + (i * 2.0f * PI / 16.0f);
            SoundManager::GetInstance()->PlaySE("Resource/SE/氷魔法1.mp3");
            new PlayerSpellParticle(mvPosition, Vector2::FromAngle(angle), speed);
        }
    }

    m_isActive = false;
    SetDeleteFlag(true);
    if (mpCollider) {
        mpCollider->SetDeleteFlag(true);
    }
}

void SpellCardBullet::OnTrigger(Collider* collider, Collider* check) {
    if (!m_isActive) return;
    if (check != nullptr && check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == Tag2D_Enemy) {
            Enemy* enemy = dynamic_cast<Enemy*>(check->GetParentObject());
            if (enemy != nullptr && enemy->IsActive() && !enemy->IsDeleteFlag()) {
                enemy->TakeDamage(m_damage);
                Explode();
            }
        } else if (check->GetParentObject()->GetTag() == Tag2D_EnemyBullet) {
            check->GetParentObject()->SetDeleteFlag(true);
        }
    }
}