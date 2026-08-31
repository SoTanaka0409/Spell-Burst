#include "SpellCardBullet.h"
#include "ObjectManager.h"
#include "CapsuleCollider.h"
#include "Player.h"
#include "Master.h"
#include "SceneManager.h"
#include "Scene.h"
#include "EnemyBullet.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include "Utility.h"
#include "PlayerSpellParticle.h"

/// @brief SpellCardBullet を生成する
/// @param x x の値
/// @param y y の値
SpellCardBullet::SpellCardBullet(float x, float y)
	: Projectile(Vector2(x, y), Vector2(0, -1), 6.0f, 1)
{
	SetTag(kTag2dPlayerBullet);
	life_timer_ = 0;

	collider_ = new CapsuleCollider(this, position_, position_, 15.0f);
	state_ = 0;
	burst_count_ = 0;
	burst_timer_ = 0;
}

/// @brief 破棄処理を行う
SpellCardBullet::~SpellCardBullet()
{
}

/// @brief 毎フレームの更新処理を行う
void SpellCardBullet::Update()
{
	if (!is_active_) return;

	life_timer_++;

	if (state_ == 0)
	{
		position_ += dir_ * (speed_ * Utility::time_scale_);

		if (collider_)
		{
			collider_->position_ = position_;
			collider_->position2_ = position_;
		}

		if (position_.y <= Utility::kScreenHeight / 2.0f)
		{
			state_ = 1;
		}

		if (IsOutOfBounds())
		{
			Kill();
		}
	}
	else if (state_ == 1)
	{
		burst_timer_++;
		if (burst_timer_ >= 60)
		{
			burst_timer_ = 0;
			Explode();
			burst_count_++;

			if (burst_count_ >= 5)
			{
				Kill();
			}
		}
	}
}

/// @brief 描画処理を行う
void SpellCardBullet::Draw()
{
	if (!is_active_) return;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	int r = 15 + static_cast<int>(sin(life_timer_ * 0.2f) * 5.0f);
	DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), r, GetColor(255, 100, 255), TRUE);
	DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), r - 5, GetColor(255, 255, 255), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

/// @brief 接触中の処理を行う
/// @param collider collider の値
/// @param check check の値
void SpellCardBullet::OnTrigger(Collider* collider, Collider* check)
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
			if (state_ == 0)
			{
				Character* enemy = dynamic_cast<Character*>(check->GetParentObject());
				if (enemy != nullptr)
				{
					enemy->TakeDamage(damage_);
				}

				state_ = 1;
			}
		}
	}
}

/// @brief Explode を実行する
void SpellCardBullet::Explode()
{
	for (int i = 0; i < 16; i++)
	{
		float angle = i * 2.0f * 3.14159265f / 16.0f;
		Vector2 d(cos(angle), sin(angle));
		ObjectManager::Instantiate<PlayerSpellParticle>(position_, d, 6.0f);
	}
}
