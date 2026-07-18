#include "Enemy.h"
#include "ObjectManager.h"
#include "CapsuleCollider.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include "Bullet.h"
#include "EnemyBullet.h"
#include "Player.h"
#include "Master.h"
#include "SceneManager.h"
#include "Utility.h"
#include "BulletFactory.h"
#include "EffectManager.h"
#include "ResourceManager.h"
#include "GameScene.h"
#include "EnemyManager.h"
#include "SoundManager.h"
#include <cmath>
#include <cstdlib>

void Enemy::SelectNewTarget()
{
	target_x_ = 100.0f + static_cast<float>(rand() % 1080);
	target_y_ = 80.0f + static_cast<float>(rand() % 180);
}

Enemy::Enemy(float x, float y, int enemyType)
	: Character(Vector2(x, y), 3, 3.0f)
{
	SetTag(kTag2dEnemy);
	this->enemy_type_ = enemyType;
	attack_timer_ = 0;

	if (enemy_type_ == 1)
	{
		speed_ = 3.0f;
		max_hp_ = 3;
	}
	else if (enemy_type_ == 2)
	{
		speed_ = 2.0f;
		max_hp_ = 5;
	}
	else if (enemy_type_ == 3)
	{
		speed_ = 1.5f;
		max_hp_ = 8;
	}
	else if (enemy_type_ == 4)
	{
		speed_ = 2.5f;
		max_hp_ = 20;
		SelectNewTarget();
	}
	hp_ = max_hp_;

	if (collider_) delete collider_;
	float colRadius = (enemy_type_ == 4) ? 45.0f : 35.0f;
	collider_ = new CapsuleCollider(this, position_, position_, colRadius);
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	Character::Update();

	if (stun_timer_ > 0) return;

	if (enemy_type_ == 4)
	{
		Vector2 target(target_x_, target_y_);
		float dist = position_.DistanceTo(target);

		if (dist < 15.0f)
		{
			SelectNewTarget();
		}
		else
		{
			position_ += (target - position_).Normalized() * (speed_ * Utility::time_scale_);
		}
	}
	else
	{
		position_.y += speed_ * Utility::time_scale_;
	}

	UpdateAttackPattern();

	if (position_.y > Utility::kScreenHeight + 50.0f)
	{
		Character::Kill();
	}
}

void Enemy::Kill()
{
	Character::Kill();
}

void Enemy::OnDeath()
{
	Character::OnDeath();

	SoundManager::GetInstance()->PlaySE("Resource/SE/se_destroy_glass01.mp3");
	Player* player = dynamic_cast<Player*>(
		Master::sceneManager->GetCurrentScene()->GetObjectManager()->GetObject2DByTag(Object2D::kTag2dPlayer).get()
		);
	if (player != nullptr)
	{
		player->AddXp(1);
	}
	GameScene* gs = dynamic_cast<GameScene*>(Master::sceneManager->GetCurrentScene());
	if (gs != nullptr && gs->GetEnemyManager() != nullptr)
	{
		gs->GetEnemyManager()->AddDefeatedCount();
	}
}

void Enemy::OnTrigger(Collider* collider, Collider* check)
{
}

void Enemy::Draw()
{
	if (!is_active_) return;

	if (stun_timer_ > 0)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 45, GetColor(0, 200, 255), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	DrawEnemySprite();
	DrawHpBar();
}

void Enemy::UpdateAttackPattern()
{
	if (enemy_type_ == 2 || enemy_type_ == 3 || enemy_type_ == 4)
	{
		attack_timer_++;
		int interval = (enemy_type_ == 4) ? 120 : 150;
		if (attack_timer_ >= interval)
		{
			attack_timer_ = 0;
			Player* player = dynamic_cast<Player*>(Master::sceneManager->GetCurrentScene()->GetObjectManager()->GetObject2DByTag(kTag2dPlayer).get());
			Vector2 targetPos(position_.x, position_.y + 100.0f);
			if (player != nullptr)
			{
				targetPos = Vector2(player->GetX(), player->GetY());
			}
			Vector2 dir = (targetPos - position_).Normalized();
			if (dir.MagnitudeSq() == 0.0f)
			{
				dir = Vector2(0.0f, 1.0f);
			}

			if (enemy_type_ == 2)
			{
				ObjectManager::Instantiate<EnemyBullet>(position_, dir, 4.0f, false, false);
			}
			else if (enemy_type_ == 3)
			{
				ObjectManager::Instantiate<EnemyBullet>(position_, dir, 3.5f, false, true);
			}
			else if (enemy_type_ == 4)
			{
				static float current_angle = 0.0f;
				current_angle += 0.2f;
				for (int i = 0; i < 4; i++)
				{
					float bullet_angle = current_angle + (i * 2.0f * 3.14159265f) / 16;
					ObjectManager::Instantiate<EnemyBullet>(position_, Vector2::FromAngle(bullet_angle), 2.0f);
				}
				float baseAngle = Vector2(1, 0).AngleTo(targetPos - position_);
				for (int i = -1; i <= 1; i++)
				{
					float angle = baseAngle + (i * 8.0f * 3.14159265f / 180.0f);
					ObjectManager::Instantiate<EnemyBullet>(position_, Vector2::FromAngle(angle), 3.5f);
				}
			}
		}
	}
}

void Enemy::DrawEnemySprite()
{
	int enemyGraphHandle = ResourceManager::GetInstance()->GetGraph("Resource/enemy.png");

	if (enemyGraphHandle != -1)
	{
		if (enemy_type_ == 1) SetDrawBright(255, 255, 255);
		else if (enemy_type_ == 2) SetDrawBright(255, 200, 100);
		else if (enemy_type_ == 3) SetDrawBright(100, 100, 255);
		else if (enemy_type_ == 4) SetDrawBright(255, 50, 50);

		float drawSize = (enemy_type_ == 4) ? 45.0f : 35.0f;
		DrawExtendGraph(
			static_cast<int>(position_.x - drawSize),
			static_cast<int>(position_.y - drawSize),
			static_cast<int>(position_.x + drawSize),
			static_cast<int>(position_.y + drawSize),
			enemyGraphHandle,
			TRUE
		);

		SetDrawBright(255, 255, 255);
	}
	else
	{
		unsigned int color_ = GetColor(255, 100, 100);
		if (enemy_type_ == 2) color_ = GetColor(255, 200, 100);
		else if (enemy_type_ == 3) color_ = GetColor(100, 100, 255);
		else if (enemy_type_ == 4) color_ = GetColor(255, 50, 50);

		int drawRadius = (enemy_type_ == 4) ? 45 : 35;
		DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), drawRadius, color_, TRUE);
	}
}

void Enemy::DrawHpBar()
{
	int hpOffset = (enemy_type_ == 4) ? 65 : 55;
	DrawFormatString(static_cast<int>(position_.x) - 15, static_cast<int>(position_.y) - hpOffset, GetColor(255, 255, 255), "HP:%d", hp_);
}
