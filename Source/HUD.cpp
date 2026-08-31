#include "HUD.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Boss.h"
#include "EnemyManager.h"
#include "Utility.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"

float HUD::display_hp_ratio_ = 1.0f;
float HUD::display_xp_ratio_ = 0.0f;
float HUD::display_spell_ratio_ = 0.0f;
float HUD::display_barrier_ratio_ = 0.0f;
float HUD::boss_hp_ratio_ = 1.0f;

/// @brief 初期化処理を行う
void HUD::Initialize()
{
	display_hp_ratio_ = 1.0f;
	display_xp_ratio_ = 0.0f;
	display_spell_ratio_ = 0.0f;
	display_barrier_ratio_ = 0.0f;
	boss_hp_ratio_ = 1.0f;
}

/// @brief 毎フレームの更新処理を行う
/// @param player player の値
/// @param enemyManager enemyManager の値
/// @param boss boss の値
void HUD::Update(Player* player, EnemyManager* enemyManager, Boss* boss)
{
	float lerpSpeed = 0.1f * Utility::time_scale_;

	if (player != nullptr)
	{
		float targetHpRatio = static_cast<float>(player->GetHp()) / static_cast<float>(player->GetMaxHp());
		display_hp_ratio_ += (targetHpRatio - display_hp_ratio_) * lerpSpeed;

		float targetXpRatio = (player->GetXpNeeded() > 0) ? static_cast<float>(player->GetXp()) / static_cast<float>(player->GetXpNeeded()) : 1.0f;
		display_xp_ratio_ += (targetXpRatio - display_xp_ratio_) * lerpSpeed;

		float targetSpellRatio = static_cast<float>(player->GetSpellGauge()) / static_cast<float>(player->GetMaxSpellGauge());
		display_spell_ratio_ += (targetSpellRatio - display_spell_ratio_) * lerpSpeed;
	}

	if (boss != nullptr && boss->IsActive())
	{
		float targetBossHpRatio = static_cast<float>(boss->GetHp()) / static_cast<float>(boss->GetMaxHp());
		boss_hp_ratio_ += (targetBossHpRatio - boss_hp_ratio_) * lerpSpeed;
	}
	else
	{
		boss_hp_ratio_ = 1.0f;
	}
}

/// @brief 描画処理を行う
/// @param player player の値
/// @param enemyManager enemyManager の値
/// @param boss boss の値
/// @param cutinTimer cutinTimer の値
/// @param cutinImageHandle cutinImageHandle の値
void HUD::Draw(Player* player, EnemyManager* enemyManager, Boss* boss, int cutinTimer, int cutinImageHandle)
{
	if (player != nullptr)
	{
		DrawPlayerStatus(player);
	}

	if (enemyManager != nullptr)
	{
		DrawEnemyProgress(enemyManager);
	}

	if (boss != nullptr && boss->IsActive())
	{
		DrawBossStatus(boss);
	}

	if (cutinTimer > 0)
	{
		DrawCutin(cutinTimer, cutinImageHandle);
	}
}

/// @brief DrawPlayerStatus を実行する
/// @param player player の値
void HUD::DrawPlayerStatus(Player* player)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
	DrawBox(10, 10, 350, 135, GetColor(0, 15, 30), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawBox(10, 10, 350, 135, GetColor(0, 128, 255), FALSE);

	DrawFormatString(20, 20, GetColor(100, 255, 100), "体力：%d / %d", player->GetHp(), player->GetMaxHp());

	int hpBarX = 200;
	int hpBarY = 22;
	int hpBarWidth = 140;
	DrawBox(hpBarX, hpBarY, hpBarX + hpBarWidth, hpBarY + 10, GetColor(50, 0, 0), TRUE);
	int hpFill = static_cast<int>(hpBarWidth * display_hp_ratio_);
	if (hpFill > 0)
	{
		DrawBox(hpBarX, hpBarY, hpBarX + hpFill, hpBarY + 10, GetColor(100, 255, 100), TRUE);
	}
	DrawBox(hpBarX, hpBarY, hpBarX + hpBarWidth, hpBarY + 10, GetColor(200, 255, 200), FALSE);

	DrawFormatString(20, 50, GetColor(255, 215, 0), "レベル：%d", player->GetLevel());

	int xpBarWidth = 260;
	int xpBarX = 35;
	int xpBarY = 70;
	int xpFill = static_cast<int>(xpBarWidth * display_xp_ratio_);
	DrawBox(xpBarX, xpBarY, xpBarX + xpBarWidth, xpBarY + 14, GetColor(20, 40, 80), TRUE);
	if (xpFill > 0)
	{
		DrawBox(xpBarX, xpBarY, xpBarX + xpFill, xpBarY + 14, GetColor(80, 200, 255), TRUE);
	}
	DrawBox(xpBarX, xpBarY, xpBarX + xpBarWidth, xpBarY + 14, GetColor(0, 180, 255), FALSE);
	DrawFormatString(xpBarX + 3, xpBarY, GetColor(255, 255, 255), "経験値：%d / %d", player->GetXp(), player->GetXpNeeded());

	DrawFormatString(20, 90, GetColor(255, 100, 200), "スペル");
	int spellBarY = 105;
	int spellFill = static_cast<int>(xpBarWidth * display_spell_ratio_);

	DrawBox(xpBarX, spellBarY, xpBarX + xpBarWidth, spellBarY + 14, GetColor(50, 0, 50), TRUE);
	if (spellFill > 0)
	{
		DrawBox(xpBarX, spellBarY, xpBarX + spellFill, spellBarY + 14, GetColor(255, 100, 200), TRUE);
	}
	DrawBox(xpBarX, spellBarY, xpBarX + xpBarWidth, spellBarY + 14, GetColor(255, 150, 220), FALSE);

	if (player->GetSpellGauge() >= player->GetMaxSpellGauge())
	{
		if ((GetNowCount() / 150) % 2 == 0)
		{
			DrawFormatString(xpBarX + 3, spellBarY, GetColor(255, 255, 255), "発動可能！必殺技キー");
		}
		else
		{
			DrawFormatString(xpBarX + 3, spellBarY, GetColor(255, 255, 0), "発動可能！必殺技キー");
		}
	}
	else
	{
		DrawFormatString(xpBarX + 3, spellBarY, GetColor(255, 255, 255), "チャージ：%d / %d", player->GetSpellGauge(), player->GetMaxSpellGauge());
	}

	int lvTimer = player->GetLevelUpTimer();
	if (lvTimer > 0)
	{
		if ((lvTimer / 10) % 2 == 0)
		{
			int px = static_cast<int>(player->GetX());
			int py = static_cast<int>(player->GetY()) - 60;
			DrawFormatString(px - 58, py + 2, GetColor(0, 0, 0), "レベルアップ！");
			DrawFormatString(px - 60, py, GetColor(255, 215, 0), "レベルアップ！");
			DrawFormatString(px - 60, py + 18, GetColor(255, 255, 100),
				"レベル%d → レベル%d", player->GetLevel() - 1, player->GetLevel());
		}
	}
}

/// @brief DrawEnemyProgress を実行する
/// @param enemyManager enemyManager の値
void HUD::DrawEnemyProgress(EnemyManager* enemyManager)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
	DrawBox(Utility::kScreenWidth - 230, 10, Utility::kScreenWidth - 10, 50, GetColor(0, 15, 30), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawBox(Utility::kScreenWidth - 230, 10, Utility::kScreenWidth - 10, 50, GetColor(0, 128, 255), FALSE);

	if (enemyManager->GetDefeatedCount() < 10)
	{
		DrawFormatString(Utility::kScreenWidth - 220, 20, GetColor(255, 255, 255), "撃破数：%d / 10", enemyManager->GetDefeatedCount());
	}
}

/// @brief DrawBossStatus を実行する
/// @param boss boss の値
void HUD::DrawBossStatus(Boss* boss)
{
	int barWidth = 400;
	int barHeight = 20;
	int barX = (Utility::kScreenWidth - barWidth) / 2;
	int barY = 50;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
	DrawBox(barX - 10, barY - 25, barX + barWidth + 10, barY + barHeight + 5, GetColor(0, 15, 30), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawBox(barX - 10, barY - 25, barX + barWidth + 10, barY + barHeight + 5, GetColor(255, 0, 0), FALSE);

	int fillWidth = static_cast<int>(barWidth * boss_hp_ratio_);
	if (fillWidth > 0)
	{
		DrawBox(barX, barY, barX + fillWidth, barY + barHeight, GetColor(255, 50, 50), TRUE);
	}
	DrawBox(barX, barY, barX + barWidth, barY + barHeight, GetColor(255, 255, 255), FALSE);

	DrawFormatString(barX, barY - 20, GetColor(255, 215, 0), "ボス：半魚人王（第%d段階）", 4 - boss->GetLives());
	DrawFormatString(barX + barWidth - 80, barY - 20, GetColor(255, 255, 255), "%d / %d", boss->GetHp(), boss->GetMaxHp());
}

/// @brief DrawCutin を実行する
/// @param cutinTimer cutinTimer の値
/// @param cutinImageHandle cutinImageHandle の値
void HUD::DrawCutin(int cutinTimer, int cutinImageHandle)
{
	int maxTimer = 90;
	int progress = maxTimer - cutinTimer;

	float xOffset = 0;
	if (progress < 15)
	{
		float t = progress / 15.0f;
		xOffset = Utility::kScreenWidth * (1.0f - t);
	}
	else if (progress <= 75)
	{
		float t = (progress - 15) / 60.0f;
		xOffset = -30.0f * t;
	}
	else
	{
		float t = (progress - 75) / 15.0f;
		xOffset = -30.0f - (Utility::kScreenWidth * t);
	}

	if (cutinImageHandle != -1)
	{
		DrawExtendGraph(static_cast<int>(xOffset), 150, static_cast<int>(xOffset + Utility::kScreenWidth), 570, cutinImageHandle, TRUE);
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox(0, 0, Utility::kScreenWidth, 150, GetColor(0, 0, 0), TRUE);
	DrawBox(0, 570, Utility::kScreenWidth, Utility::kScreenHeight, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if (progress > 10)
	{
		const char* spellName = "スペルカード：極太レーザー！！";
		if (Player::kSelectedCharacterType == 2) spellName = "スペルカード：虹色ウェーブ！！";
		else if (Player::kSelectedCharacterType == 3) spellName = "スペルカード：桜吹雪！！";
		DrawFormatString(static_cast<int>(xOffset) + 100, 500, GetColor(0, 255, 255), "%s", spellName);
	}
}
