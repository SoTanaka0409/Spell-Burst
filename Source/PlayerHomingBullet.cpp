#include "PlayerHomingBullet.h"
#include "ObjectManager.h"
#include "CapsuleCollider.h"
#include "Enemy.h"
#include "Boss.h"
#include "Master.h"
#include "SceneManager.h"
#include "Scene.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include <cmath>
#include "utility.h"

/// @brief PlayerHomingBullet を生成する
/// @param pos pos の値
/// @param dir_ dir_ の値
/// @param speed_ speed_ の値
PlayerHomingBullet::PlayerHomingBullet(Vector2 pos, Vector2 dir_, float speed_)
	: Projectile(pos, dir_.Normalized(), speed_, 5)
{
	SetTag(kTag2dPlayerBullet);

	life_timer_ = 60 * 3;

	collider_ = new CapsuleCollider(this, position_, position_, 15.0f);
}

/// @brief 破棄処理を行う
PlayerHomingBullet::~PlayerHomingBullet()
{
}

/// @brief 毎フレームの更新処理を行う
void PlayerHomingBullet::Update()
{
	life_timer_--;
	if (life_timer_ <= 0)
	{
		Kill();
		return;
	}

	Object2D* targetEnemy = nullptr;
	float minDistSq = 9999999.0f;

	auto enemies = Master::sceneManager->GetCurrentScene()->GetObjectManager()->GetObject2DListByTag(kTag2dEnemy);
	for (auto& obj : enemies)
	{
		Character* e = dynamic_cast<Character*>(obj.get());

		if (e && !e->IsDeleteFlag() && e->GetY() > 0)
		{
			float distSq = e->GetPosition().DistanceSqTo(position_);
			if (distSq < minDistSq && distSq < 2500.0f * 2500.0f)
			{
				minDistSq = distSq;
				targetEnemy = e;
			}
		}
	}

	if (targetEnemy)
	{
		float currentAngle = Vector2(1, 0).AngleTo(dir_);
		float targetAngle = Vector2(1, 0).AngleTo(targetEnemy->GetPosition() - position_);
		float diff = targetAngle - currentAngle;

		while (diff > 3.14159265f) diff -= 2.0f * 3.14159265f;
		while (diff < -3.14159265f) diff += 2.0f * 3.14159265f;

		float turnSpeed = 0.1f * Utility::time_scale_;
		if (diff > turnSpeed) currentAngle += turnSpeed;
		else if (diff < -turnSpeed) currentAngle -= turnSpeed;
		else currentAngle = targetAngle;

		dir_ = Vector2::FromAngle(currentAngle);
	}

	position_ += dir_ * (speed_ * Utility::time_scale_);

	Projectile::Update();

	if (IsOutOfBounds())
	{
		Kill();
	}
}

/// @brief 描画処理を行う
void PlayerHomingBullet::Draw()
{
	if (!is_active_) return;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
	DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 15, GetColor(0, 255, 128), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 8, GetColor(100, 255, 200), TRUE);
}

/// @brief 接触中の処理を行う
/// @param collider collider の値
/// @param check check の値
void PlayerHomingBullet::OnTrigger(Collider* collider, Collider* check)
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
