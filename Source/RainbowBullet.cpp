#include "RainbowBullet.h"
#include "CapsuleCollider.h"
#include "Player.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include "Utility.h"
#include <cmath>

RainbowBullet::RainbowBullet(float x, float y)
    : Projectile(Vector2(x, y), Vector2(0, -1), 5.0f, 1)
{
    SetTag(Tag2D_PlayerBullet);
    m_colorHue = 0;
    mpCollider = new CapsuleCollider(this, mvPosition, mvPosition, 12.0f);
}

RainbowBullet::~RainbowBullet() {
}

void RainbowBullet::Update() {
    mvPosition += m_dir * (m_speed * Utility::TimeScale);

    m_colorHue += 5;
    if (m_colorHue >= 360) m_colorHue -= 360;

    Projectile::Update();

    if (IsOutOfBounds()) {
        Kill();
    }
}

void RainbowBullet::Draw() {
    if (!m_isActive) return;

    float rad = m_colorHue * 3.14159265f / 180.0f;
    int r = static_cast<int>(sin(rad) * 127 + 128);
    int g = static_cast<int>(sin(rad + 2.0f * 3.14159265f / 3.0f) * 127 + 128);
    int b = static_cast<int>(sin(rad + 4.0f * 3.14159265f / 3.0f) * 127 + 128);
    
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
    DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 12, GetColor(r, g, b), TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 8, GetColor(255, 255, 255), TRUE);
}

void RainbowBullet::OnTrigger(Collider* collider, Collider* check) {
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
            Kill();
        }
    }
}