#include "MasterSpark.h"
#include "ObjectManager.h"
#include "CapsuleCollider.h"
#include "Enemy.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include "Utility.h"
#include "Master.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Player.h"
#include <cmath>
#include <cstdlib>

/// @brief MasterSpark を生成する
/// @param x x の値
/// @param y y の値
MasterSpark::MasterSpark(float x, float y)
	: Projectile(Vector2(x, y), Vector2(0, -1), 0.0f, 1)
{
	SetTag(kTag2dPlayerBullet);
	max_life_ = 120;
	life_timer_ = max_life_;
	radius_ = 120.0f;
	color_hue_ = 0;
	attack_count_ = 0;

	collider_ = new CapsuleCollider(this, Vector2(position_.x, position_.y), Vector2(position_.x, position_.y - 1200.0f), radius_);
}

/// @brief 破棄処理を行う
MasterSpark::~MasterSpark()
{
}

/// @brief 毎フレームの更新処理を行う
void MasterSpark::Update()
{
	life_timer_--;
	if (life_timer_ <= 0)
	{
		Projectile::Kill();
		return;
	}

	Player* player = dynamic_cast<Player*>(
		Master::sceneManager->GetCurrentScene()->GetObjectManager()->GetObject2DByTag(kTag2dPlayer).get()
		);
	if (player != nullptr)
	{
		position_.x = player->GetX();
		position_.y = player->GetY() - 45.0f;
	}

	float target_radius = 120.0f;
	if (life_timer_ < 20)
	{
		radius_ = target_radius * (life_timer_ / 20.0f);
	}
	else if (max_life_ - life_timer_ < 10)
	{
		radius_ = target_radius * ((max_life_ - life_timer_) / 10.0f);
	}
	else
	{
		radius_ = target_radius;
	}

	radius_ += (rand() % 20 - 10) * 0.5f;

	color_hue_ += 15;
	if (color_hue_ >= 360) color_hue_ -= 360;

	if (collider_)
	{
		collider_->position_ = Vector2(position_.x, position_.y);
		collider_->position2_ = Vector2(position_.x, position_.y - 1200.0f);
		collider_->radius_ = radius_;
	}
}

/// @brief 描画処理を行う
void MasterSpark::Draw()
{
	if (!is_active_) return;
	DrawParticles();
}

/// @brief DrawParticles を実行する
void MasterSpark::DrawParticles()
{
	SetDrawBlendMode(DX_BLENDMODE_ADD, 180);

	for (int i = 0; i < 7; ++i)
	{
		float rad = (color_hue_ + i * 50) * 3.14159265f / 180.0f;
		int r = static_cast<int>(sin(rad) * 127 + 128);
		int g = static_cast<int>(sin(rad + 2.0f * 3.14159265f / 3.0f) * 127 + 128);
		int b = static_cast<int>(sin(rad + 4.0f * 3.14159265f / 3.0f) * 127 + 128);

		float drawRadius = radius_ * (1.0f - i * 0.12f) + (rand() % 15);
		float offset_x = (rand() % 10 - 5) * 0.5f;

		DrawBox(static_cast<int>(position_.x - drawRadius + offset_x), static_cast<int>(position_.y - 1200.0f),
			static_cast<int>(position_.x + drawRadius + offset_x), static_cast<int>(position_.y), GetColor(r, g, b), TRUE);
		DrawCircle(static_cast<int>(position_.x + offset_x), static_cast<int>(position_.y), static_cast<int>(drawRadius), GetColor(r, g, b), TRUE);
	}

	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	float innerRadius = radius_ * 0.4f + (rand() % 10);
	DrawBox(static_cast<int>(position_.x - innerRadius), static_cast<int>(position_.y - 1200.0f),
		static_cast<int>(position_.x + innerRadius), static_cast<int>(position_.y), GetColor(255, 255, 255), TRUE);
	DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), static_cast<int>(innerRadius), GetColor(255, 255, 255), TRUE);

	float coreRadius = radius_ * 0.15f;
	DrawBox(static_cast<int>(position_.x - coreRadius), static_cast<int>(position_.y - 1200.0f),
		static_cast<int>(position_.x + coreRadius), static_cast<int>(position_.y), GetColor(200, 255, 255), TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

/// @brief 削除対象にする
void MasterSpark::Kill()
{
}

/// @brief 接触中の処理を行う
/// @param collider collider の値
/// @param check check の値
void MasterSpark::OnTrigger(Collider* collider, Collider* check)
{
	if (check != nullptr && check->GetParentObject() != nullptr)
	{
		if (check->GetParentObject()->GetTag() == kTag2dEnemy)
		{
			Character* enemy = dynamic_cast<Character*>(check->GetParentObject());

			if (enemy != nullptr && life_timer_ % 3 == 0)
			{
				enemy->TakeDamage(damage_);
				attack_count_++;
			}
		}
		else if (check->GetParentObject()->GetTag() == kTag2dEnemyBullet)
		{
			check->GetParentObject()->SetDeleteFlag(true);
		}
	}
}

/// @brief 接触開始時の処理を行う
/// @param collider collider の値
/// @param check check の値
void MasterSpark::OnEnter(Collider* collider, Collider* check)
{
}
