#include "CapsuleCollider.h"

CapsuleCollider::CapsuleCollider(Object2D* parent, VECTOR pos1, VECTOR pos2, float radius)
	: Collider(parent)
{
	mvPosition = pos1;
	mvPosition2 = pos2;
	mfRadius = radius;
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
				this->mvPosition,
				this->mvPosition2,
				this->mfRadius,
				capsule->mvPosition,
				capsule->mvPosition2,
				capsule->mfRadius
			);

			HitCheck(check, isHit);
		}
	}

}

void CapsuleCollider::Draw()
{
	DrawCircle(
		static_cast<int>(mvPosition.x),
		static_cast<int>(mvPosition.y),
		static_cast<int>(mfRadius),
		GetColor(255, 255, 255),
		FALSE
	);

	if (mvPosition.x != mvPosition2.x || mvPosition.y != mvPosition2.y) {
		DrawCircle(
			static_cast<int>(mvPosition2.x),
			static_cast<int>(mvPosition2.y),
			static_cast<int>(mfRadius),
			GetColor(255, 255, 255),
			FALSE
		);
		DrawLine(
			static_cast<int>(mvPosition.x),
			static_cast<int>(mvPosition.y),
			static_cast<int>(mvPosition2.x),
			static_cast<int>(mvPosition2.y),
			GetColor(255, 255, 255)
		);
	}
}


