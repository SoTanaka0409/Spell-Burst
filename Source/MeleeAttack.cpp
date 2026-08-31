#include "MeleeAttack.h"
#include "ObjectManager.h"
#include "CapsuleCollider.h"
#include "Enemy.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include <algorithm>
#include <cmath>

/// @brief MeleeAttack を生成する
/// @param x x の値
/// @param y y の値
MeleeAttack::MeleeAttack(float x, float y)
	: Object2D(Vector2(x, y))
	, collider_(nullptr)
{
	SetTag(kTag2dPlayerBullet);
	position_.x = x;
	position_.y = y;

	life_time_ = 10;
	damage_ = 3;

	collider_ = new CapsuleCollider(this, position_, position_, 80.0f);
}

/// @brief 破棄処理を行う
MeleeAttack::~MeleeAttack()
{
	if (collider_)
	{
		delete collider_;
		collider_ = nullptr;
	}
}

/// @brief 毎フレームの更新処理を行う
void MeleeAttack::Update()
{
	life_time_--;
	if (life_time_ <= 0)
	{
		SetDeleteFlag(true);
		if (collider_)
		{
			collider_->SetDeleteFlag(true);
		}
	}
}

/// @brief 描画処理を行う
void MeleeAttack::Draw()
{
	unsigned int slashColor = GetColor(100, 255, 255);
	float radius_ = 80.0f;
	const double PI = 3.14159265358979323846;

	for (int i = 0; i <= 8; i++)
	{
		double angle = (PI + PI / 6.0) + (i * (2.0 * PI / 3.0)) / 8.0;
		int sx = static_cast<int>(position_.x + std::cos(angle) * radius_);
		int sy = static_cast<int>(position_.y + std::sin(angle) * radius_);
		DrawCircle(sx, sy, 8, slashColor, TRUE);

		DrawCircle(sx, sy, 4, GetColor(255, 255, 255), TRUE);
	}
}

/// @brief 削除対象にする
void MeleeAttack::Kill()
{
}

/// @brief 接触中の処理を行う
/// @param collider collider の値
/// @param check check の値
void MeleeAttack::OnTrigger(Collider* collider, Collider* check)
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
		}
	}
}
