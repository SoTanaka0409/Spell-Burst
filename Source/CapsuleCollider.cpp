#include "CapsuleCollider.h"
#include "ObjectManager.h"

/// @brief CapsuleCollider を生成する
/// @param parent parent の値
/// @param pos1 pos1 の値
/// @param pos2 pos2 の値
/// @param radius radius の値
CapsuleCollider::CapsuleCollider(Object2D* parent, Vector2 pos1, Vector2 pos2, float radius)
	: Collider(parent)
{
	position_ = pos1;
	position2_ = pos2;
	this->radius_ = radius;
}

/// @brief 破棄処理を行う
CapsuleCollider::~CapsuleCollider()
{
}

/// @brief 毎フレームの更新処理を行う
/// @param check check の値
void CapsuleCollider::Update(Collider* check)
{
	if (check != nullptr)
	{
		CapsuleCollider* capsule = dynamic_cast<CapsuleCollider*>(check);

		if (capsule != nullptr)
		{
			bool isHit = HitCheck_Capsule_Capsule(
				this->position_,
				this->position2_,
				this->radius_,
				capsule->position_,
				capsule->position2_,
				capsule->radius_
			);

			HitCheck(check, isHit);
		}
	}
}

/// @brief 描画処理を行う
void CapsuleCollider::Draw()
{
	DrawCircle(
		static_cast<int>(position_.x),
		static_cast<int>(position_.y),
		static_cast<int>(radius_),
		GetColor(255, 255, 255),
		FALSE
	);

	if (position_.x != position2_.x || position_.y != position2_.y)
	{
		DrawCircle(
			static_cast<int>(position2_.x),
			static_cast<int>(position2_.y),
			static_cast<int>(radius_),
			GetColor(255, 255, 255),
			FALSE
		);
		DrawLine(
			static_cast<int>(position_.x),
			static_cast<int>(position_.y),
			static_cast<int>(position2_.x),
			static_cast<int>(position2_.y),
			GetColor(255, 255, 255)
		);
	}
}
