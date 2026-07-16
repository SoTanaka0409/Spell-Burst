#include "Bullet.h"
#include "ObjectManager.h"
#include "CapsuleCollider.h"
#include "Character.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include "Utility.h"

Bullet::Bullet(float x, float y, int damage) 
    : Projectile(Vector2(x, y), Vector2(0, -1), 20.0f, damage_)
{
    SetTag(kTag2dPlayerBullet);
    received_damage_ = 0;
    max_received_damage_ = 20; // ダメージを受けてから3回で技を�EぁE
    // Create a circular collider_ with radius_ 10 (previously 5)
    collider_ = new CapsuleCollider(this, position_, position_, 10.0f);
}

Bullet::~Bullet()
{
}

// 毎フレーム呼ばれる更新処琁E
// 弾を上方向に移動させ、画面外に出たら削除フラグを立てまぁE
void Bullet::Update() 
{
    position_ += dir_ * (speed_ * Utility::time_scale_);

    Projectile::Update();

    if (IsOutOfBounds())
    {
        Kill();
    }
}

void Bullet::OnTrigger(Collider* collider, Collider* check)
{
    if (check != nullptr && check->GetParentObject() != nullptr)
    {
        if(check->GetParentObject()->GetTag() == kTag2dBarrierEnemy)
        {
            Kill();
            return;
        }
    }
    if (check != nullptr && check->GetParentObject() != nullptr) 
    {
        if (check->GetParentObject()->GetTag() == kTag2dEnemy)
        {
            Character* enemy = dynamic_cast<Character*>(check->GetParentObject());
            if (enemy != nullptr)
            {
                enemy->TakeDamage(damage_);
            }
            Kill();
        }
    }
}

// 描画処琁E
// 弾の画像を描画しまぁE
void Bullet::Draw()
{
    if (!is_active_) return;
    DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 10, GetColor(255, 255, 255), TRUE);
}
