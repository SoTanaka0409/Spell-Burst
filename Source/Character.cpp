#include "Character.h"
#include "ObjectManager.h"
#include "CapsuleCollider.h"
#include <algorithm>

/// @brief Character を生成する
/// @param pos pos の値
/// @param maxHp maxHp の値
/// @param speed speed の値
Character::Character(Vector2 pos, int maxHp, float speed)
    : Object2D(pos)
    , hp_(maxHp)
    , max_hp_(maxHp)
    , speed_(speed)
    , is_active_(true)
    , stun_timer_(0)
    , collider_(nullptr)
{
}

/// @brief 破棄処理を行う
Character::~Character()
{
    if (collider_)
    {
        delete collider_;
        collider_ = nullptr;
    }
}

/// @brief 毎フレームの更新処理を行う
void Character::Update()
{
    // Decrease stun time.
    if (stun_timer_ > 0)
    {
        stun_timer_--;
    }

    // Keep the collider aligned with the current position.
    if (collider_)
    {
        collider_->position_ = position_;
        collider_->position2_ = position_;
    }
}

/// @brief 描画処理を行う
void Character::Draw()
{
    // Base class does not draw anything.
}

/// @brief 接触中の処理を行う
/// @param collider collider の値
/// @param check check の値
void Character::OnTrigger(Collider* collider, Collider* check)
{
    // Default implementation for derived classes to override.
}

/// @brief 回復処理を行う
/// @param amount amount の値
void Character::Heal(int amount)
{
    // Clamp HP between 0 and max HP after healing.
    hp_ = std::clamp(hp_ + amount, 0, max_hp_);
}

/// @brief ダメージ処理を行う
/// @param damage damage の値
void Character::TakeDamage(int damage)
{
    if (!is_active_) return;

    // Clamp HP between 0 and max HP after damage.
    hp_ = std::clamp(hp_ - damage, 0, max_hp_);
    if (hp_ == 0)
    {
        OnDeath();
    }
}

/// @brief 削除対象にする
void Character::Kill()
{
    is_active_ = false;
    SetDeleteFlag(true);
    if (collider_)
    {
        collider_->SetDeleteFlag(true);
    }
}

/// @brief 死亡時の処理を行う
void Character::OnDeath()
{
    Kill(); // Default behavior is to destroy itself.
}
