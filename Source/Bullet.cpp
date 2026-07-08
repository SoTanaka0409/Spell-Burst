#include "Bullet.h"
#include "ObjectManager.h"
#include "CapsuleCollider.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include "Utility.h"

Bullet::Bullet(float x, float y, int damage_) 
    : Projectile(Vector2(x, y), Vector2(0, -1), 20.0f, damage_)
{
    SetTag(kTag2dPlayerBullet);
    recivedDamage = 0;
    maxrecivedDamage = 20; // ダメージを受けてから3回で技を出す
    // Create a circular collider_ with radius_ 10 (previously 5)
    collider_ = new CapsuleCollider(this, position_, position_, 10.0f);
}

Bullet::~Bullet()
{
}

// 毎フレーム呼ばれる更新処理
// 弾を上方向に移動させ、画面外に出たら削除フラグを立てます
void Bullet::Update() 
{
    position_ += dir * (speed_ * Utility::TimeScale);

    Projectile::Update();

    if (IsOutOfBounds()) {
        Kill();
    }
}

void Bullet::OnTrigger(Collider* collider_, Collider* check)
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
            Kill();
        }
    }
}

// 描画処理
// 弾の画像を描画します
void Bullet::Draw()
{
    if (!is_active_) return;
    DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 10, GetColor(255, 255, 255), TRUE);
}
