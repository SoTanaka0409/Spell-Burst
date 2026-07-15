#include "CapsuleCollider.h"

#include "ObjectManager.h"
CapsuleCollider::CapsuleCollider(Object2D* parent, Vector2 pos1, Vector2 pos2, float radius_)
	: Collider(parent)
{
	position_ = pos1;
	position2 = pos2;
	this->radius_ = radius_;
}

CapsuleCollider::~CapsuleCollider()
{

}

void CapsuleCollider::Update(Collider* check)
{
	if (check != nullptr)
	{
		CapsuleCollider* capsule = dynamic_cast<CapsuleCollider*>(check);
		
		if (capsule != nullptr)
		{
			bool isHit = HitCheck_Capsule_Capsule(
				this->position_,
				this->position2,
				this->radius_,
				capsule->position_,
				capsule->position2,
				capsule->radius_
			);

			HitCheck(check, isHit);
		}
	}

}

void CapsuleCollider::Draw()
{
	DrawCircle(
		static_cast<int>(position_.x),
		static_cast<int>(position_.y),
		static_cast<int>(radius_),
		GetColor(255, 255, 255),
		FALSE
	);

	if (position_.x != position2.x || position_.y != position2.y)
	{
		DrawCircle(
			static_cast<int>(position2.x),
			static_cast<int>(position2.y),
			static_cast<int>(radius_),
			GetColor(255, 255, 255),
			FALSE
		);
		DrawLine(
			static_cast<int>(position_.x),
			static_cast<int>(position_.y),
			static_cast<int>(position2.x),
			static_cast<int>(position2.y),
			GetColor(255, 255, 255)
		);
	}
}



