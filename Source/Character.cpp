#include "Character.h"
#include "ObjectManager.h"
#include "CapsuleCollider.h"
#include <algorithm>

Character::Character(Vector2 pos, int max_hp_, float speed_)
    : Object2D(pos)
    , hp_(max_hp_)
    , max_hp_(max_hp_)
    , speed_(speed_)
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
    // スタン時間の減少
    if (stun_timer_ > 0)
    {
        stun_timer_--;
    }

    // コライダーの座標追従
    if (collider_)
    {
        collider_->position_ = position_;
        collider_->position2 = position_;
    }
}

void Character::Draw()
{
    // 基底クラスは描画しない
}

void Character::OnTrigger(Collider* collider_, Collider* check)
{
    // デフォルト実装：派生先でオーバーライド
}

void Character::Heal(int amount)
{
    // std::clampを使って回復後のHPが0?最大HPの間に収まるように制限
    hp_ = std::clamp(hp_ + amount, 0, max_hp_);
}

void Character::TakeDamage(int damage)
{
    // std::clampを使ってダメージ後のHPが0?最大HPの間に収まるように制限
    hp_ = std::clamp(hp_ - damage, 0, max_hp_);
    if (hp_ == 0)
    {
        Kill();
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
