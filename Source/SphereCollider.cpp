#include "SphereCollider.h"
#include "ObjectManager.h"
#include "CapsuleCollider.h"

SphereCollider::SphereCollider(Object2D* parent, Vector2 center, float radius)
	: Collider(parent)
{
	position_ = center;
	position2_ = center;
	this->radius_ = radius_;
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

void SphereCollider::OnEnter()
{
}

void SphereCollider::OnTrigger()
{
}

void SphereCollider::OnExit()
{
}

