#include "Projectile.h"
#include "ObjectManager.h"
#include "CapsuleCollider.h"
#include "Utility.h"

/// @brief Projectile を生成する
/// @param pos pos の値
/// @param dir_ dir_ の値
/// @param speed speed の値
/// @param damage damage の値
Projectile::Projectile(Vector2 pos, Vector2 dir_, float speed, int damage)
    : Object2D(pos)
    , dir_(dir_)
    , speed_(speed)
    , damage_(damage)
    , is_active_(true)
    , collider_(nullptr)
{
    position_ = pos;
}

/// @brief 破棄処理を行う
Projectile::~Projectile()
{
    if (collider_)
    {
        delete collider_;
        collider_ = nullptr;
    }
}

/// @brief 毎フレームの更新処理を行う
void Projectile::Update()
{
    if (collider_)
    {
        collider_->position_ = position_;
        collider_->position2_ = position_;
    }
}

/// @brief 描画処理を行う
void Projectile::Draw()
{
}

/// @brief 接触中の処理を行う
/// @param collider collider の値
/// @param check check の値
void Projectile::OnTrigger(Collider* collider, Collider* check)
{
}

/// @brief 削除対象にする
void Projectile::Kill()
{
    is_active_ = false;
    SetDeleteFlag(true);
    if (collider_)
    {
        collider_->SetDeleteFlag(true);
    }
}

/// @brief IsOutOfBounds を実行する
/// @param margin margin の値
/// @return bool 戻り値
bool Projectile::IsOutOfBounds(float margin) const
{
    if (position_.x < -margin || position_.x > Utility::kScreenWidth + margin ||
        position_.y < -margin || position_.y > Utility::kScreenHeight + margin)
        {
        return true;
    }
    return false;
}
