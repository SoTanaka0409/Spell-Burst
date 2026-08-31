#include "BossStateAttack.h"
#include "Boss.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include "ObjectManager.h"
#include "Enemy.h"
#include "GameScene.h"
#include "Master.h"
#include "SceneManager.h"
#include "ResultScene.h"

/// @brief 毎フレームの更新処理を行う
/// @param boss boss の値
void BossStateSimple::Update(Boss* boss)
{
	attack_timer_++;
	if (attack_timer_ >= 60)
	{
		attack_timer_ = 0;
		boss->ShootSimpleBarrage();
	}
}

/// @brief 毎フレームの更新処理を行う
/// @param boss boss の値
void BossStateBouncing::Update(Boss* boss)
{
	attack_timer_++;
	if (attack_timer_ >= 120)
	{
		attack_timer_ = 0;
		boss->ShootBouncingBarrage();
	}
}

/// @brief 毎フレームの更新処理を行う
/// @param boss boss の値
void BossStateFinal::Update(Boss* boss)
{
	invincible_cycle_timer_++;

	if (invincible_cycle_timer_ >= 300)
	{
		boss->SetInvincibleTimer(120);
		invincible_cycle_timer_ = 0;
		ObjectManager::Instantiate<Enemy>(boss->GetX() - 60.0f, boss->GetY() + 60.0f, 1);
		ObjectManager::Instantiate<Enemy>(boss->GetX() + 60.0f, boss->GetY() + 60.0f, 1);
	}

	attack_timer_++;
	if (attack_timer_ >= 100)
	{
		attack_timer_ = 0;

		bool used_spell_card = false;
		if (GameScene::current_stage_ == 3)
		{
			if ((rand() % 100) < 20)
			{
				boss->ShootSpellCardBarrage();
				used_spell_card = true;
			}
		}

		if (!used_spell_card)
		{
			if (pattern_index_ == 0)
			{
				boss->ShootRadialBarrage();
			}
			else if (pattern_index_ == 1)
			{
				boss->ShootFanBarrage();
			}
			else
			{
				boss->ShootTargetedBarrage();
			}
			pattern_index_ = (pattern_index_ + 1) % 3;
		}
	}
}

/// @brief 毎フレームの更新処理を行う
/// @param boss boss の値
void BossStateDying::Update(Boss* boss)
{
	death_timer_--;
	if (death_timer_ <= 0)
	{
		boss->Kill();
	}
}
