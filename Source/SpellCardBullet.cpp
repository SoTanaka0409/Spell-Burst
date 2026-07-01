#include "SpellCardBullet.h"
#include "CapsuleCollider.h"
#include "Player.h"
#include "Master.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ObjectManager.h"
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
    SetTag(Tag2D_PlayerBullet);
    m_lifeTimer = 0;
    
    mpCollider = new CapsuleCollider(this, mvPosition, mvPosition, 15.0f);
}

SpellCardBullet::~SpellCardBullet() {
}

void SpellCardBullet::Update() {
    mvPosition += m_dir * (m_speed * Utility::TimeScale);

    if (mpCollider) {
        mpCollider->mvPosition = mvPosition;
        mpCollider->mvPosition2 = mvPosition;
    }

    m_lifeTimer++;

    if (IsOutOfBounds()) {
        Kill();
    }
}

void SpellCardBullet::Draw() {
    if (!m_isActive) return;

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
    int r = 15 + static_cast<int>(sin(m_lifeTimer * 0.2f) * 5.0f);
    DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), r, GetColor(255, 100, 255), TRUE);
    DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), r - 5, GetColor(255, 255, 255), TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SpellCardBullet::OnTrigger(Collider* collider, Collider* check) {
    if(check!=nullptr&&check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == tag2D_BarierEne)
        {
            Kill();
            return;
		}
	}
    if (check != nullptr && check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == Tag2D_Enemy) {
            Character* enemy = dynamic_cast<Character*>(check->GetParentObject());
            if (enemy != nullptr) {
                enemy->TakeDamage(m_damage);
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
        new PlayerSpellParticle(mvPosition, dir, 3.0f);
    }
}