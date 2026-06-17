#include "SphereCollider.h"
#include "CapsuleCollider.h"

SphereCollider::SphereCollider(Object2D* parent, VECTOR center, float radius)
	: Collider(parent)
{
	mvPosition = center;
	mvPosition2 = center;
	mfRadius = radius;
}

SphereCollider::~SphereCollider()
{
}

void SphereCollider::Update(Collider* check)
{
	if (check != nullptr)
	{
		CapsuleCollider* capsule = dynamic_cast<CapsuleCollider*>(check);
		if (capsule != nullptr)
		{
			bool isHit = HitCheck_Sphere_Capsule(
				this->mvPosition,
				this->mfRadius,
				capsule->mvPosition,
				capsule->mvPosition2,
				capsule->mfRadius
			);
			HitCheck(check, isHit);
		}

		SphereCollider* sphere = dynamic_cast<SphereCollider*>(check);
		if (sphere != nullptr)
		{
			bool isHit = HitCheck_Sphere_Sphere(
				this->mvPosition,
				this->mfRadius,
				sphere->mvPosition,
				sphere->mfRadius
			);
			HitCheck(check, isHit);
		}
	}
}

void SphereCollider::Draw()
{
	DrawCircle(
		static_cast<int>(mvPosition.x),
		static_cast<int>(mvPosition.y),
		static_cast<int>(mfRadius),
		GetColor(255, 255, 255),
		FALSE
	);
}

void SphereCollider::OnEnter()
{
}

void SphereCollider::OnTrigger()
{
}

void SphereCollider::OnExit()
{
}
