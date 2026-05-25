#include "Obstacle.h"
#include "CapsuleCollider.h"
#include "Utility.h"
#include "Player.h"
#include <DxLib.h>

Obstacle::Obstacle(float x, float y)
    : Object2D(VGet(x, y, 0.0f))
    , mpCollider(nullptr)
    , m_fallSpeed(3.0f)
{
    SetTag(Tag2D_Enemy); // Treated like an enemy so bullets hit it
    mpCollider = new CapsuleCollider(this, mvPosition, mvPosition, 40.0f);
}

Obstacle::~Obstacle() {
    if (mpCollider) {
        delete mpCollider;
        mpCollider = nullptr;
    }
}

void Obstacle::Update() {
    mvPosition.y += m_fallSpeed * Utility::TimeScale;
    
    if (mpCollider) {
        mpCollider->mvPosition = mvPosition;
        mpCollider->mvPosition2 = mvPosition;
    }

    if (mvPosition.y > Utility::SCREEN_HEIGHT + 100.0f) {
        SetDeleteFlag(true);
        if (mpCollider) {
            mpCollider->SetDeleteFlag(true);
        }
    }
}

void Obstacle::Draw() {
    // Draw a grey rock/obstacle
    DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 40, GetColor(100, 100, 100), TRUE);
    DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 38, GetColor(80, 80, 80), TRUE);
}

void Obstacle::OnTrigger(Collider* collider, Collider* check) {
    if (check != nullptr && check->GetParentObject() != nullptr) {
        // If a player bullet hits the obstacle, delete the bullet (Obstacle is invincible)
        if (check->GetParentObject()->GetTag() == Tag2D_PlayerBullet) {
            check->GetParentObject()->SetDeleteFlag(true);
            check->SetDeleteFlag(true);
        }
        // If player touches it, damage player
        if (check->GetParentObject()->GetTag() == Tag2D_Player) {
            Player* p = dynamic_cast<Player*>(check->GetParentObject());
            if (p) {
                p->TakeDamage(10);
            }
        }
    }
}
