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

SpellCardBullet::SpellCardBullet(float x, float y)
    : Projectile(Vector2(x, y), Vector2(0, -1), 6.0f, 1)
{
    SetTag(Tag2D_PlayerBullet);
    lifeTimer = 0;
    
    collider = new CapsuleCollider(this, position, position, 15.0f);
}

SpellCardBullet::~SpellCardBullet() {
}

void SpellCardBullet::Update() {
    position += dir * (speed * Utility::TimeScale);

    if (collider) {
        collider->position = position;
        collider->position2 = position;
    }

    lifeTimer++;

    if (IsOutOfBounds()) {
        Kill();
    }
}

void SpellCardBullet::Draw() {
    if (!isActive) return;

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
    int r = 15 + static_cast<int>(sin(lifeTimer * 0.2f) * 5.0f);
    DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), r, GetColor(255, 100, 255), TRUE);
    DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), r - 5, GetColor(255, 255, 255), TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SpellCardBullet::OnTrigger(Collider* collider, Collider* check) {
    if(check!=nullptr&&check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == Tag2D_BarrierEnemy)
        {
            Kill();
            return;
		}
	}
    if (check != nullptr && check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == Tag2D_Enemy) {
            Character* enemy = dynamic_cast<Character*>(check->GetParentObject());
            if (enemy != nullptr) {
                enemy->TakeDamage(damage);
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
        new PlayerSpellParticle(position.x, position.y, dir, 3.0f);
    }
}