#include "Character.h"
#include "ObjectManager.h"
#include "CapsuleCollider.h"
#include <algorithm>

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

Character::~Character()
{
    if (collider_)
    {
        delete collider_;
        collider_ = nullptr;
    }
}

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

void Character::Draw()
{
    // Base class does not draw anything.
}

void Character::OnTrigger(Collider* collider, Collider* check)
{
    // Default implementation for derived classes to override.
}

void Character::Heal(int amount)
{
    // Clamp HP between 0 and max HP after healing.
    hp_ = std::clamp(hp_ + amount, 0, max_hp_);
}

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

void Character::Kill()
{
    is_active_ = false;
    SetDeleteFlag(true);
    if (collider_)
    {
        collider_->SetDeleteFlag(true);
    }
}

void Character::OnDeath()
{
    Kill(); // Default behavior is to destroy itself.
}