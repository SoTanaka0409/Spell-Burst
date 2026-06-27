#include "CapsuleCollider.h"

CapsuleCollider::CapsuleCollider(Object2D* parent, Vector2 pos1, Vector2 pos2, float radius)
	: Collider(parent)
{
	position = pos1;
	position2 = pos2;
	radius = radius;
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
				this->position,
				this->position2,
				this->radius,
				capsule->position,
				capsule->position2,
				capsule->radius
			);

			HitCheck(check, isHit);
		}
	}

}

void CapsuleCollider::Draw()
{
	DrawCircle(
		static_cast<int>(position.x),
		static_cast<int>(position.y),
		static_cast<int>(radius),
		GetColor(255, 255, 255),
		FALSE
	);

	if (position.x != position2.x || position.y != position2.y) {
		DrawCircle(
			static_cast<int>(position2.x),
			static_cast<int>(position2.y),
			static_cast<int>(radius),
			GetColor(255, 255, 255),
			FALSE
		);
		DrawLine(
			static_cast<int>(position.x),
			static_cast<int>(position.y),
			static_cast<int>(position2.x),
			static_cast<int>(position2.y),
			GetColor(255, 255, 255)
		);
	}
}


