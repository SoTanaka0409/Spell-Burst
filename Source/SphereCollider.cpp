#include "SphereCollider.h"
#include "ObjectManager.h"
#include "CapsuleCollider.h"

/// @brief SphereCollider を生成する
/// @param parent parent の値
/// @param center center の値
/// @param radius radius の値
SphereCollider::SphereCollider(Object2D* parent, Vector2 center, float radius)
	: Collider(parent)
{
	position_ = center;
	position2_ = center;
	this->radius_ = radius;
}

/// @brief 破棄処理を行う
SphereCollider::~SphereCollider()
{
}

/// @brief 毎フレームの更新処理を行う
/// @param check check の値
void SphereCollider::Update(Collider* check)
{
	if (check != nullptr)
	{
		CapsuleCollider* capsule = dynamic_cast<CapsuleCollider*>(check);
		if (capsule != nullptr)
		{
			bool isHit = HitCheck_Sphere_Capsule(
				this->position_,
				this->radius_,
				capsule->position_,
				capsule->position2_,
				capsule->radius_
			);
			HitCheck(check, isHit);
		}

		SphereCollider* sphere = dynamic_cast<SphereCollider*>(check);
		if (sphere != nullptr)
		{
			bool isHit = HitCheck_Sphere_Sphere(
				this->position_,
				this->radius_,
				sphere->position_,
				sphere->radius_
			);
			HitCheck(check, isHit);
		}
	}
}

/// @brief 描画処理を行う
void SphereCollider::Draw()
{
	DrawCircle(
		static_cast<int>(position_.x),
		static_cast<int>(position_.y),
		static_cast<int>(radius_),
		GetColor(255, 255, 255),
		FALSE
	);
}

/// @brief 接触開始時の処理を行う
void SphereCollider::OnEnter()
{
}

/// @brief 接触中の処理を行う
void SphereCollider::OnTrigger()
{
}

/// @brief 接触終了時の処理を行う
void SphereCollider::OnExit()
{
}
