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
    maxLife = 120;
    lifeTimer = maxLife;
    radius = 50.0f;
    colorHue = 0;
    attackCount = 0;

    collider = new CapsuleCollider(this, Vector2(position.x, position.y), Vector2(position.x, position.y - 1200.0f), radius);
}

MasterSpark::~MasterSpark() {
}

void MasterSpark::Update() {
    lifeTimer--;
    if (lifeTimer <= 0) {
        Projectile::Kill(); // 寿命が来たら消滅
        return;
    }

    if (lifeTimer < 20) {
        radius = 50.0f * (lifeTimer / 20.0f);
        if (collider) collider->radius = radius;
    } else if (maxLife - lifeTimer < 10) {
        radius = 50.0f * ((maxLife - lifeTimer) / 10.0f);
        if (collider) collider->radius = radius;
    } else {
        radius = 50.0f;
    }

    colorHue += 15;
    if (colorHue >= 360) colorHue -= 360;

    if (collider) {
        collider->position = Vector2(position.x, position.y);
        collider->position2 = Vector2(position.x, position.y - 1200.0f);
    }
}

void MasterSpark::Draw() {
    if (!isActive) return;

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
    for (int i = 0; i < 5; ++i) {
        float rad = (colorHue + i * 72) * 3.14159265f / 180.0f;
        int r = static_cast<int>(sin(rad) * 127 + 128);
        int g = static_cast<int>(sin(rad + 2.0f * 3.14159265f / 3.0f) * 127 + 128);
        int b = static_cast<int>(sin(rad + 4.0f * 3.14159265f / 3.0f) * 127 + 128);

        float drawRadius = radius * (1.0f - i * 0.1f);
        
        // Draw using Box and Circle like the original
        DrawBox(static_cast<int>(position.x - drawRadius), static_cast<int>(position.y - 1200.0f),
                static_cast<int>(position.x + drawRadius), static_cast<int>(position.y), GetColor(r, g, b), TRUE);
        DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(drawRadius), GetColor(r, g, b), TRUE);
    }

    SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
    float innerRadius = radius * 0.4f;
    DrawBox(static_cast<int>(position.x - innerRadius), static_cast<int>(position.y - 1200.0f),
            static_cast<int>(position.x + innerRadius), static_cast<int>(position.y), GetColor(255, 255, 255), TRUE);
    DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(innerRadius), GetColor(255, 255, 255), TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void MasterSpark::Kill() {
    // 貫通レーザーなので衝突で消滅しない
}

void MasterSpark::OnTrigger(Collider* collider, Collider* check) {
    if (check != nullptr && check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == Tag2D_Enemy) {
            Character* enemy = dynamic_cast<Character*>(check->GetParentObject());
            if (enemy != nullptr && lifeTimer % 5 == 0) {
                enemy->TakeDamage(damage);
                attackCount++;
            }
        } else if (check->GetParentObject()->GetTag() == Tag2D_EnemyBullet) {
            check->GetParentObject()->SetDeleteFlag(true);
        }
    }
}

void MasterSpark::OnEnter(Collider* collider, Collider* check) {
}