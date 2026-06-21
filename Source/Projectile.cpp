#include "Projectile.h"
#include "CapsuleCollider.h"
#include "Utility.h"

Projectile::Projectile(Vector2 pos, Vector2 dir, float speed, int damage)
    : Object2D(pos)
    , m_dir(dir)
    , m_speed(speed)
    , m_damage(damage)
    , m_isActive(true)
    , mpCollider(nullptr)
{
    mvPosition = pos;
}

Projectile::~Projectile() {
    if (mpCollider) {
        delete mpCollider;
        mpCollider = nullptr;
    }
}

void Projectile::Update() {
    if (mpCollider) {
        mpCollider->mvPosition = mvPosition;
        mpCollider->mvPosition2 = mvPosition;
    }
}

void Projectile::Draw() {
    // 基底クラスは描画しない
}

void Projectile::OnTrigger(Collider* collider, Collider* check) {
    // デフォルト実装：派生クラスでオーバーライド
}

void Projectile::Kill() {
    m_isActive = false;
    SetDeleteFlag(true);
    if (mpCollider) {
        mpCollider->SetDeleteFlag(true);
    }
}

bool Projectile::IsOutOfBounds(float margin) const {
    if (mvPosition.x < -margin || mvPosition.x > Utility::SCREEN_WIDTH + margin ||
        mvPosition.y < -margin || mvPosition.y > Utility::SCREEN_HEIGHT + margin) {
        return true;
    }
    return false;
}