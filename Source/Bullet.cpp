#include "Bullet.h"
#include "ObjectManager.h"
#include "CapsuleCollider.h"
#include "Character.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include "Utility.h"

Bullet::Bullet(float x, float y, int damage)
	: Projectile(Vector2(x, y), Vector2(0, -1), 20.0f, damage)
{
	SetTag(kTag2dPlayerBullet);
	received_damage_ = 0;

	max_received_damage_ = 20;

	collider_ = new CapsuleCollider(this, position_, position_, 10.0f);
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	position_ += dir_ * (speed_ * Utility::time_scale_);

	Projectile::Update();

	if (IsOutOfBounds())
	{
		Kill();
	}
}

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

void Bullet::Draw()
{
	if (!is_active_) return;
	DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 10, GetColor(255, 255, 255), TRUE);
}
