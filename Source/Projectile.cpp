#include "Projectile.h"
#include "ObjectManager.h"
#include "CapsuleCollider.h"
#include "Utility.h"

Projectile::Projectile(Vector2 pos, Vector2 dir, float speed_, int damage_)
    : Object2D(pos)
    , dir(dir)
    , speed_(speed_)
    , damage_(damage_)
    , is_active_(true)
    , collider_(nullptr)
{
    position_ = pos;
}

Projectile::~Projectile()
{
    if (collider_)
    {
        delete collider_;
        collider_ = nullptr;
    }
}

void Projectile::Update()
{
    if (collider_)
    {
        collider_->position_ = position_;
        collider_->position2 = position_;
    }
}

void Projectile::Draw()
{
    // 基底クラスは描画しない
}

void Projectile::OnTrigger(Collider* collider_, Collider* check)
{
    // デフォルト実装：派生クラスでオーバーライド
}

void Projectile::Kill()
{
    is_active_ = false;
    SetDeleteFlag(true);
    if (collider_)
    {
        collider_->SetDeleteFlag(true);
    }
}

bool Projectile::IsOutOfBounds(float margin) const
{
    if (position_.x < -margin || position_.x > Utility::SCREEN_WIDTH + margin ||
        position_.y < -margin || position_.y > Utility::SCREEN_HEIGHT + margin)
        {
        return true;
    }
    return false;
}
