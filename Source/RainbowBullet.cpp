#include "RainbowBullet.h"
#include "CapsuleCollider.h"
#include "Enemy.h"
#include "Boss.h"
#include "Utility.h"
#include <DxLib.h>
#include <cmath>

RainbowBullet::RainbowBullet(float x, float y)
    : Object2D(VGet(x, y, 0.0f))
    , mpCollider(nullptr)
    , m_speed(15.0f)
    , m_damage(20)
{
    SetTag(Tag2D_PlayerBullet);
    mpCollider = new CapsuleCollider(this, mvPosition, mvPosition, 15.0f);
    
    // Generate an initial hue based on X position and current time for a rainbow effect
    m_colorHue = (static_cast<int>(x) * 2 + GetNowCount() / 5) % 360;
}

RainbowBullet::~RainbowBullet() {
    if (mpCollider) {
        delete mpCollider;
        mpCollider = nullptr;
    }
}

void RainbowBullet::Update() {
    mvPosition.y -= m_speed * Utility::TimeScale;
    mvPosition = VGet(mvPosition.x, mvPosition.y, 0.0f);

    if (mpCollider) {
        mpCollider->mvPosition = mvPosition;
        mpCollider->mvPosition2 = mvPosition;
    }

    if (mvPosition.y < -50.0f) {
        SetDeleteFlag(true);
        if (mpCollider) {
            mpCollider->SetDeleteFlag(true);
        }
    }
    
    // Animate color
    m_colorHue = (m_colorHue + 10) % 360;
}

void RainbowBullet::Draw() {
    int colorR = static_cast<int>(std::sin(m_colorHue * 3.14159f / 180.0f) * 127 + 128);
    int colorG = static_cast<int>(std::sin((m_colorHue + 120) * 3.14159f / 180.0f) * 127 + 128);
    int colorB = static_cast<int>(std::sin((m_colorHue + 240) * 3.14159f / 180.0f) * 127 + 128);
    
    unsigned int colorOuter = GetColor(colorR, colorG, colorB);
    unsigned int colorInner = GetColor(255, 255, 255);

    SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
    DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 20, colorOuter, TRUE);
    SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
    DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 10, colorInner, TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void RainbowBullet::OnTrigger(Collider* collider, Collider* check) {
    if (check != nullptr && check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == Tag2D_Enemy) {
            Object2D* obj = check->GetParentObject();
            Boss* boss = dynamic_cast<Boss*>(obj);
            bool hit = false;
            if (boss != nullptr && boss->IsActive() && !boss->IsDeleteFlag()) {
                boss->TakeDamage(m_damage);
                hit = true;
            } else {
                Enemy* enemy = dynamic_cast<Enemy*>(obj);
                if (enemy != nullptr && enemy->IsActive() && !enemy->IsDeleteFlag()) {
                    enemy->TakeDamage(m_damage);
                    hit = true;
                }
            }
            
            if (hit) {
                SetDeleteFlag(true);
                if (mpCollider) {
                    mpCollider->SetDeleteFlag(true);
                }
            }
        }
    }
}
