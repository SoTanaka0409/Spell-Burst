#include "PlayerSpellParticle.h"
#include "ObjectManager.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include "Utility.h"
#include <cmath>
#include "Character.h"
#include "CapsuleCollider.h"

/// @brief PlayerSpellParticle を生成する
/// @param pos pos の値
/// @param dir dir の値
/// @param speed_ speed_ の値
PlayerSpellParticle::PlayerSpellParticle(Vector2 pos, Vector2 dir, float speed_)
	: Object2D(pos)
{
	SetTag(kTag2dPlayerBullet);
	this->position_ = pos;
	this->dir = dir.Normalized();
	this->speed_ = speed_;
	this->is_active_ = true;
	this->life_timer_ = 180;
	this->damage_ = 5;
	this->collider_ = new CapsuleCollider(this, this->position_, this->position_, 15.0f);
}

/// @brief 破棄処理を行う
PlayerSpellParticle::~PlayerSpellParticle()
{
	if (collider_)
	{
		delete collider_;
		collider_ = nullptr;
	}
}

/// @brief 削除対象にする
void PlayerSpellParticle::Kill()
{
	is_active_ = false;
	SetDeleteFlag(true);
}

/// @brief 毎フレームの更新処理を行う
void PlayerSpellParticle::Update()
{
	if (!is_active_) return;

	life_timer_--;
	if (life_timer_ <= 0)
	{
		is_active_ = false;
		SetDeleteFlag(true);
		return;
	}

	position_ += dir * (speed_ * Utility::time_scale_);

	if (position_.x < -50.0f || position_.x > Utility::kScreenWidth + 50.0f || position_.y < -50.0f || position_.y > Utility::kScreenHeight + 50.0f)
	{
		is_active_ = false;
		SetDeleteFlag(true);
		return;
	}

	if (collider_)
	{
		collider_->position_ = position_;
		collider_->position2_ = position_;
	}
}

/// @brief 描画処理を行う
void PlayerSpellParticle::Draw()
{
	if (!is_active_) return;

	int alpha = (life_timer_ * 255) / 180;
	if (alpha > 255) alpha = 255;
	SetDrawBlendMode(DX_BLENDMODE_ADD, alpha);

	DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 15, GetColor(150, 255, 255), TRUE);
	DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 8, GetColor(255, 255, 255), TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

/// @brief 接触中の処理を行う
/// @param collider collider の値
/// @param check check の値
void PlayerSpellParticle::OnTrigger(Collider* collider, Collider* check)
{
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
		else if (check->GetParentObject()->GetTag() == kTag2dEnemyBullet)
		{
			check->GetParentObject()->SetDeleteFlag(true);
		}
	}
}
