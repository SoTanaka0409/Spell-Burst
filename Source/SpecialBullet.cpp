#include "SpecialBullet.h"
#include "ObjectManager.h"
#include "CapsuleCollider.h"
#include "Enemy.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include "Utility.h"

/// @brief SpecialBullet を生成する
/// @param x x の値
/// @param y y の値
SpecialBullet::SpecialBullet(float x, float y)
    : Projectile(Vector2(x, y), Vector2(0, -1), 12.0f, 5)
{
    SetTag(kTag2dPlayerBullet); // プレイヤー側の攻撃として判定するためのタグを設定する
    collider_ = new CapsuleCollider(this, position_, position_, 90.0f);
}

/// @brief 破棄処理を行う
SpecialBullet::~SpecialBullet()
{
}

/// @brief 毎フレームの更新処理を行う
void SpecialBullet::Update()
{
    position_ += dir_ * (speed_ * Utility::time_scale_);

    Projectile::Update();

    if (position_.y < -120.0f)
    {
        Projectile::Kill(); // 画面外に出たら削除する
    }
}

/// @brief 描画処理を行う
void SpecialBullet::Draw()
{
    if (!is_active_) return;

    unsigned int colorGold = GetColor(255, 215, 0);
    unsigned int colorOrange = GetColor(255, 140, 0);
    unsigned int colorWhite = GetColor(255, 255, 255);

    DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 90, colorOrange, TRUE);
    DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 75, colorGold, TRUE);
    DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 45, colorWhite, TRUE);

    DrawLine(static_cast<int>(position_.x - 90), static_cast<int>(position_.y), static_cast<int>(position_.x + 90), static_cast<int>(position_.y), colorGold);
    DrawLine(static_cast<int>(position_.x), static_cast<int>(position_.y - 90), static_cast<int>(position_.x), static_cast<int>(position_.y + 90), colorGold);
}

/// @brief 削除対象にする
void SpecialBullet::Kill()
{
}

/// @brief 接触中の処理を行う
/// @param collider collider の値
/// @param check check の値
void SpecialBullet::OnTrigger(Collider* collider, Collider* check)
{
    if (check != nullptr && check->GetParentObject() != nullptr)
    {
        if (check->GetParentObject()->GetTag() == kTag2dEnemy)
        {
            Character* enemy = dynamic_cast<Character*>(check->GetParentObject());
            if (enemy != nullptr)
            {
                enemy->TakeDamage(damage_);
            }
        } else if (check->GetParentObject()->GetTag() == kTag2dEnemyBullet)
        {
            check->GetParentObject()->SetDeleteFlag(true);
        }
    }
}
