#include "SphereCollider.h"
#include "CapsuleCollider.h"

SphereCollider::SphereCollider(Object2D* parent, Vector2 center, float radius)
	: Collider(parent)
{
	position = center;
	position2 = center;
	radius = radius;
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
				this->position,
				this->radius,
				capsule->position,
				capsule->position2,
				capsule->radius
			);
			HitCheck(check, isHit);
		}

		SphereCollider* sphere = dynamic_cast<SphereCollider*>(check);
		if (sphere != nullptr)
		{
			bool isHit = HitCheck_Sphere_Sphere(
				this->position,
				this->radius,
				sphere->position,
				sphere->radius
			);
			HitCheck(check, isHit);
		}
	}
}

void SphereCollider::Draw()
{
	DrawCircle(
		static_cast<int>(position.x),
		static_cast<int>(position.y),
		static_cast<int>(radius),
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
