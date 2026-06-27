#include "Projectile.h"
#include "CapsuleCollider.h"
#include "Utility.h"

Projectile::Projectile(Vector2 pos, Vector2 dir, float speed, int damage)
    : Object2D(pos)
    , dir(dir)
    , speed(speed)
    , damage(damage)
    , isActive(true)
    , collider(nullptr)
{
    position = pos;
}

Projectile::~Projectile() {
    if (collider) {
        delete collider;
        collider = nullptr;
    }
}

void Projectile::Update() {
    if (collider) {
        collider->position = position;
        collider->position2 = position;
    }
}

void Projectile::Draw() {
    // 基底クラスは描画しない
}

void Projectile::OnTrigger(Collider* collider, Collider* check) {
    // デフォルト実装：派生クラスでオーバーライド
}

void Projectile::Kill() {
    isActive = false;
    SetDeleteFlag(true);
    if (collider) {
        collider->SetDeleteFlag(true);
    }
}

bool Projectile::IsOutOfBounds(float margin) const {
    if (position.x < -margin || position.x > Utility::SCREEN_WIDTH + margin ||
        position.y < -margin || position.y > Utility::SCREEN_HEIGHT + margin) {
        return true;
    }
    return false;
}