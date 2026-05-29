#include "HUD.h"
#include "Player.h"
#include "Boss.h"
#include "EnemyManager.h"
#include "Utility.h"
#include <DxLib.h>

float HUD::s_displayHpRatio = 1.0f;
float HUD::s_displayXpRatio = 0.0f;
float HUD::s_displaySpellRatio = 0.0f;
float HUD::s_displayBarrierRatio = 0.0f;
float HUD::s_bossHpRatio = 1.0f;

void HUD::Initialize() {
    s_displayHpRatio = 1.0f;
    s_displayXpRatio = 0.0f;
    s_displaySpellRatio = 0.0f;
    s_displayBarrierRatio = 0.0f;
    s_bossHpRatio = 1.0f;
}

void HUD::Update(Player* player, EnemyManager* enemyManager, Boss* boss) {
    float lerpSpeed = 0.1f * Utility::TimeScale;

    if (player != nullptr) {
        float targetHpRatio = static_cast<float>(player->GetHp()) / static_cast<float>(player->GetMaxHp());
        s_displayHpRatio += (targetHpRatio - s_displayHpRatio) * lerpSpeed;

        float targetXpRatio = (player->GetXpNeeded() > 0) ? static_cast<float>(player->GetXp()) / static_cast<float>(player->GetXpNeeded()) : 1.0f;
        s_displayXpRatio += (targetXpRatio - s_displayXpRatio) * lerpSpeed;

        float targetSpellRatio = static_cast<float>(player->GetSpellGauge()) / static_cast<float>(player->GetMaxSpellGauge());
        s_displaySpellRatio += (targetSpellRatio - s_displaySpellRatio) * lerpSpeed;
    }

    if (boss != nullptr && boss->IsActive()) {
        float targetBossHpRatio = static_cast<float>(boss->GetHp()) / static_cast<float>(boss->GetMaxHp());
        s_bossHpRatio += (targetBossHpRatio - s_bossHpRatio) * lerpSpeed;
    } else {
        s_bossHpRatio = 1.0f;
    }
}

void HUD::Draw(Player* player, EnemyManager* enemyManager, Boss* boss, int cutinTimer, int cutinImageHandle) {
    if (player != nullptr) {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
        DrawBox(10, 10, 320, 230, GetColor(0, 15, 30), TRUE); 
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        DrawBox(10, 10, 320, 230, GetColor(0, 128, 255), FALSE); 

        // Player HP
        DrawFormatString(20, 20, GetColor(100, 255, 100), "PLAYER HP: %d / %d", player->GetHp(), player->GetMaxHp());

        // Player HP Bar (New!)
        int hpBarX = 160;
        int hpBarY = 22;
        int hpBarWidth = 140;
        DrawBox(hpBarX, hpBarY, hpBarX + hpBarWidth, hpBarY + 10, GetColor(50, 0, 0), TRUE);
        int hpFill = static_cast<int>(hpBarWidth * s_displayHpRatio);
        if (hpFill > 0) {
            DrawBox(hpBarX, hpBarY, hpBarX + hpFill, hpBarY + 10, GetColor(100, 255, 100), TRUE);
        }
        DrawBox(hpBarX, hpBarY, hpBarX + hpBarWidth, hpBarY + 10, GetColor(200, 255, 200), FALSE);

        // Attack Mode HUD
        DrawString(20, 45, "ATTACK MODE [Q / 1-2 to switch]:", GetColor(255, 255, 255));
        
        Player::AttackMode mode = player->GetAttackMode();
        unsigned int colorSelected = GetColor(255, 215, 0); 
        unsigned int colorUnselected = GetColor(120, 180, 200); 

        DrawFormatString(35, 92, (mode == Player::AttackMode_Melee) ? colorSelected : colorUnselected, 
            "[1] Melee (Knife) %s", (mode == Player::AttackMode_Melee) ? "<SELECTED>" : "");

        int cd = player->GetSpecialCooldown();
        if (cd > 0) {
            DrawFormatString(35, 114, (mode == Player::AttackMode_Special) ? colorSelected : colorUnselected,
                "[2] Special [CD: %.1fs]", cd / 60.0f);
        } else {
            DrawFormatString(35, 114, (mode == Player::AttackMode_Special) ? colorSelected : colorUnselected,
                "[2] Special [READY] %s", (mode == Player::AttackMode_Special) ? "<SELECTED>" : "");
        }

        // Level & XP HUD
        DrawFormatString(20, 140, GetColor(255, 215, 0), "LV: %d", player->GetLevel());

        int xpBarWidth = 260;
        int xpBarX = 35;
        int xpBarY = 162;
        int xpFill = static_cast<int>(xpBarWidth * s_displayXpRatio);
        DrawBox(xpBarX, xpBarY, xpBarX + xpBarWidth, xpBarY + 14, GetColor(20, 40, 80), TRUE);
        if (xpFill > 0) {
            DrawBox(xpBarX, xpBarY, xpBarX + xpFill, xpBarY + 14, GetColor(80, 200, 255), TRUE);
        }
        DrawBox(xpBarX, xpBarY, xpBarX + xpBarWidth, xpBarY + 14, GetColor(0, 180, 255), FALSE);
        DrawFormatString(xpBarX + 3, xpBarY, GetColor(255, 255, 255), "XP: %d / %d", player->GetXp(), player->GetXpNeeded());

        // Spell Card Gauge
        DrawFormatString(20, 180, GetColor(255, 100, 200), "SPELL");
        int spellBarY = 195;
        int spellFill = static_cast<int>(xpBarWidth * s_displaySpellRatio);
        
        DrawBox(xpBarX, spellBarY, xpBarX + xpBarWidth, spellBarY + 14, GetColor(50, 0, 50), TRUE);
        if (spellFill > 0) {
            DrawBox(xpBarX, spellBarY, xpBarX + spellFill, spellBarY + 14, GetColor(255, 100, 200), TRUE);
        }
        DrawBox(xpBarX, spellBarY, xpBarX + xpBarWidth, spellBarY + 14, GetColor(255, 150, 220), FALSE);
        
        if (player->GetSpellGauge() >= player->GetMaxSpellGauge()) {
            if ((GetNowCount() / 150) % 2 == 0) {
                DrawFormatString(xpBarX + 3, spellBarY, GetColor(255, 255, 255), "READY!! (PRESS X)");
            } else {
                DrawFormatString(xpBarX + 3, spellBarY, GetColor(255, 255, 0), "READY!! (PRESS X)");
            }
        } else {
            DrawFormatString(xpBarX + 3, spellBarY, GetColor(255, 255, 255), "CHARGE: %d / %d", player->GetSpellGauge(), player->GetMaxSpellGauge());
        }

        // LEVEL UP! Flash Effect
        int lvTimer = player->GetLevelUpTimer();
        if (lvTimer > 0) {
            if ((lvTimer / 10) % 2 == 0) {
                int px = static_cast<int>(player->GetX());
                int py = static_cast<int>(player->GetY()) - 60;
                DrawFormatString(px - 58, py + 2, GetColor(0, 0, 0), "LEVEL UP!");
                DrawFormatString(px - 60, py, GetColor(255, 215, 0), "LEVEL UP!");
                DrawFormatString(px - 60, py + 18, GetColor(255, 255, 100), 
                    "LV.%d -> LV.%d", player->GetLevel() - 1, player->GetLevel());
            }
        }
    }

    if (enemyManager != nullptr) {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
        DrawBox(Utility::SCREEN_WIDTH - 230, 10, Utility::SCREEN_WIDTH - 10, 50, GetColor(0, 15, 30), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        DrawBox(Utility::SCREEN_WIDTH - 230, 10, Utility::SCREEN_WIDTH - 10, 50, GetColor(0, 128, 255), FALSE);

        if (enemyManager->GetDefeatedCount() >= 10) {
            DrawString(Utility::SCREEN_WIDTH - 220, 20, "BOSS BATTLE!", GetColor(255, 50, 50));
        } else {
            DrawFormatString(Utility::SCREEN_WIDTH - 220, 20, GetColor(255, 255, 255), "DEFEATED: %d / 10", enemyManager->GetDefeatedCount());
        }
    }

    if (boss != nullptr && boss->IsActive()) {
        int barWidth = 400;
        int barHeight = 20;
        int barX = (Utility::SCREEN_WIDTH - barWidth) / 2;
        int barY = 50;

        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
        DrawBox(barX - 10, barY - 25, barX + barWidth + 10, barY + barHeight + 5, GetColor(0, 15, 30), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        DrawBox(barX - 10, barY - 25, barX + barWidth + 10, barY + barHeight + 5, GetColor(255, 0, 0), FALSE);

        int fillWidth = static_cast<int>(barWidth * s_bossHpRatio);
        if (fillWidth > 0) {
            DrawBox(barX, barY, barX + fillWidth, barY + barHeight, GetColor(255, 50, 50), TRUE);
        }
        DrawBox(barX, barY, barX + barWidth, barY + barHeight, GetColor(255, 255, 255), FALSE);

        DrawFormatString(barX, barY - 20, GetColor(255, 215, 0), "BOSS: FISHMAN KING (PHASE %d)", 4 - boss->GetLives());
        DrawFormatString(barX + barWidth - 80, barY - 20, GetColor(255, 255, 255), "%d / %d", boss->GetHp(), boss->GetMaxHp());
    }

    if (cutinTimer > 0) {
        int maxTimer = 90;
        int progress = maxTimer - cutinTimer; 
        
        float xOffset = 0;
        if (progress < 15) {
            // Slide in quickly
            float t = progress / 15.0f;
            xOffset = Utility::SCREEN_WIDTH * (1.0f - t);
        } else if (progress <= 75) {
            // Hold and slightly drift
            float t = (progress - 15) / 60.0f;
            xOffset = -30.0f * t;
        } else {
            // Slide out quickly
            float t = (progress - 75) / 15.0f;
            xOffset = -30.0f - (Utility::SCREEN_WIDTH * t);
        }
        
        if (cutinImageHandle != -1) {
            DrawExtendGraph(static_cast<int>(xOffset), 150, static_cast<int>(xOffset + Utility::SCREEN_WIDTH), 570, cutinImageHandle, TRUE);
        }

        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
        DrawBox(0, 0, Utility::SCREEN_WIDTH, 150, GetColor(0, 0, 0), TRUE);
        DrawBox(0, 570, Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT, GetColor(0, 0, 0), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

        if (progress > 10) {
            const char* spellName = "SPELL CARD: MASTER SPARK!!";
            if (Player::s_selectedCharacterType == 2) spellName = "SPELL CARD: RAINBOW WAVE!!";
            else if (Player::s_selectedCharacterType == 3) spellName = "SPELL CARD: CHERRY BLOSSOM!!";
            DrawFormatString(static_cast<int>(xOffset) + 100, 500, GetColor(0, 255, 255), "%s", spellName);
        }
    }
}
