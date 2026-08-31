#include "Obstacle.h"
#include "ObjectManager.h"
#include "CapsuleCollider.h"
#include "Utility.h"
#include "EffectManager.h"
#include "Player.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "MasterSpark.h"
#include "SpecialBullet.h"
#include "SpellCardBullet.h"
#include "RainbowBullet.h"
#include "ExplosionParticle.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"

/// @brief Obstacle を生成する
/// @param x x の値
/// @param y y の値
Obstacle::Obstacle(float x, float y)
	: Object2D(Vector2(x, y))
	, collider_(nullptr)
	, fall_speed_(3.0f)
{
	SetTag(kTag2dEnemy);
	collider_ = new CapsuleCollider(this, position_, position_, 40.0f);
}

/// @brief 破棄処理を行う
Obstacle::~Obstacle()
{
	if (collider_)
	{
		delete collider_;
		collider_ = nullptr;
	}
}

/// @brief 毎フレームの更新処理を行う
void Obstacle::Update()
{
	position_.y += fall_speed_ * Utility::time_scale_;

	if (collider_)
	{
		collider_->position_ = position_;
		collider_->position2_ = position_;
	}

	if (position_.y > Utility::kScreenHeight + 100.0f)
	{
		SetDeleteFlag(true);
		if (collider_)
		{
			collider_->SetDeleteFlag(true);
		}
	}
}

/// @brief 描画処理を行う
void Obstacle::Draw()
{
	int graph = ResourceManager::GetInstance()->GetGraph("IMG_OBJ_ROCK");
	if (graph != -1)
	{
		DrawExtendGraph(
			static_cast<int>(position_.x - 45.0f),
			static_cast<int>(position_.y - 45.0f),
			static_cast<int>(position_.x + 45.0f),
			static_cast<int>(position_.y + 45.0f),
			graph, TRUE
		);
	}
	else
	{
		DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 40, GetColor(100, 100, 100), TRUE);
		DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 38, GetColor(80, 80, 80), TRUE);
	}
}

/// @brief 接触中の処理を行う
/// @param collider collider の値
/// @param check check の値
void Obstacle::OnTrigger(Collider* collider, Collider* check)
{
	if (check != nullptr && check->GetParentObject() != nullptr)
	{
		Object2D* parent = check->GetParentObject();
		if (parent->GetTag() == kTag2dPlayerBullet)
		{
			bool isSpecial = false;
			if (dynamic_cast<MasterSpark*>(parent) != nullptr ||
				dynamic_cast<RainbowBullet*>(parent) != nullptr ||
				dynamic_cast<SpellCardBullet*>(parent) != nullptr ||
				dynamic_cast<SpecialBullet*>(parent) != nullptr)
			{
				isSpecial = true;
			}

			if (isSpecial)
			{
				this->SetDeleteFlag(true);
				if (collider_) collider_->SetDeleteFlag(true);
				SoundManager::GetInstance()->PlaySE("SE_GLASS_DESTROY");
				EffectManager::SpawnExplosion(position_, 5, GetColor(150, 150, 150), 10.0f, 2.0f);
			}
			else
			{
				parent->SetDeleteFlag(true);
				check->SetDeleteFlag(true);
			}
		}
	}
}

/// @brief 接触開始時の処理を行う
/// @param collider collider の値
/// @param check check の値
void Obstacle::OnEnter(Collider* collider, Collider* check)
{
	if (check != nullptr && check->GetParentObject() != nullptr)
	{
		Object2D* parent = check->GetParentObject();

		if (parent->GetTag() == kTag2dPlayer)
		{
			Player* p = dynamic_cast<Player*>(parent);
			if (p)
			{
				p->TakeDamage(2);
			}
		}
	}
}
