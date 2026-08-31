#include "Bullet.h"
#include "ObjectManager.h"
#include "CapsuleCollider.h"
#include "Character.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include "Utility.h"

/// @brief Bullet を生成する
/// @param x x の値
/// @param y y の値
/// @param damage damage の値
Bullet::Bullet(float x, float y, int damage)
	: Projectile(Vector2(x, y), Vector2(0, -1), 20.0f, damage)
{
	SetTag(kTag2dPlayerBullet);
	received_damage_ = 0;

	max_received_damage_ = 20;

	collider_ = new CapsuleCollider(this, position_, position_, 10.0f);
}

/// @brief 破棄処理を行う
Bullet::~Bullet()
{
}

/// @brief 毎フレームの更新処理を行う
void Bullet::Update()
{
	position_ += dir_ * (speed_ * Utility::time_scale_);

	Projectile::Update();

	if (IsOutOfBounds())
	{
		Kill();
	}
}

/// @brief 接触中の処理を行う
/// @param collider collider の値
/// @param check check の値
void Bullet::OnTrigger(Collider* collider, Collider* check)
{
	if (check != nullptr && check->GetParentObject() != nullptr)
	{
		if (check->GetParentObject()->GetTag() == kTag2dBarrierEnemy)
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

/// @brief 描画処理を行う
void Bullet::Draw()
{
	if (!is_active_) return;
	DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 10, GetColor(255, 255, 255), TRUE);
}
