#include "HUD.h"
#include "Player.h"
#include "Boss.h"
#include "EnemyManager.h"
#include "Utility.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"

float HUD::displayHpRatio = 1.0f;
float HUD::displayXpRatio = 0.0f;
float HUD::displaySpellRatio = 0.0f;
float HUD::displayBarrierRatio = 0.0f;
float HUD::bossHpRatio = 1.0f;

void HUD::Initialize() {
    displayHpRatio = 1.0f;
    displayXpRatio = 0.0f;
    displaySpellRatio = 0.0f;
    displayBarrierRatio = 0.0f;
    bossHpRatio = 1.0f;
}

void HUD::Update(Player* player, EnemyManager* enemyManager, Boss* boss) {
    float lerpSpeed = 0.1f * Utility::TimeScale;

    if (player != nullptr) {
        float targetHpRatio = static_cast<float>(player->GetHp()) / static_cast<float>(player->GetMaxHp());
        displayHpRatio += (targetHpRatio - displayHpRatio) * lerpSpeed;

        float targetXpRatio = (player->GetXpNeeded() > 0) ? static_cast<float>(player->GetXp()) / static_cast<float>(player->GetXpNeeded()) : 1.0f;
        displayXpRatio += (targetXpRatio - displayXpRatio) * lerpSpeed;

        float targetSpellRatio = static_cast<float>(player->GetSpellGauge()) / static_cast<float>(player->GetMaxSpellGauge());
        displaySpellRatio += (targetSpellRatio - displaySpellRatio) * lerpSpeed;
    }

    if (boss != nullptr && boss->IsActive()) {
        float targetBossHpRatio = static_cast<float>(boss->GetHp()) / static_cast<float>(boss->GetMaxHp());
        bossHpRatio += (targetBossHpRatio - bossHpRatio) * lerpSpeed;
    } else {
        bossHpRatio = 1.0f;
    }
}

void HUD::Draw(Player* player, EnemyManager* enemyManager, Boss* boss, int cutinTimer, int cutinImageHandle) {
    if (player != nullptr) {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
        DrawBox(10, 10, 350, 135, GetColor(0, 15, 30), TRUE); 
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        DrawBox(10, 10, 350, 135, GetColor(0, 128, 255), FALSE); 

        // �v���C���[�̌��ݑ̗͂𐔒l�Ŗ������邽��HP��`��
        DrawFormatString(20, 20, GetColor(100, 255, 100), "PLAYER HP: %d / %d", player->GetHp(), player->GetMaxHp());

        // ���o�I�ɒ����I�ȑ̗͔c����\�ɂ��邽�߃Q�[�W��`��
        int hpBarX = 200;
        int hpBarY = 22;
        int hpBarWidth = 140;
        DrawBox(hpBarX, hpBarY, hpBarX + hpBarWidth, hpBarY + 10, GetColor(50, 0, 0), TRUE);
        int hpFill = static_cast<int>(hpBarWidth * displayHpRatio);
        if (hpFill > 0) {
            DrawBox(hpBarX, hpBarY, hpBarX + hpFill, hpBarY + 10, GetColor(100, 255, 100), TRUE);
        }
        DrawBox(hpBarX, hpBarY, hpBarX + hpBarWidth, hpBarY + 10, GetColor(200, 255, 200), FALSE);

        

        // �����x������t�B�[�h�o�b�N���邽�߃��x���ƌo���l�g��`��
        DrawFormatString(20, 50, GetColor(255, 215, 0), "LV: %d", player->GetLevel());

        int xpBarWidth = 260;
        int xpBarX = 35;
        int xpBarY = 70;
        int xpFill = static_cast<int>(xpBarWidth * displayXpRatio);
        DrawBox(xpBarX, xpBarY, xpBarX + xpBarWidth, xpBarY + 14, GetColor(20, 40, 80), TRUE);
        if (xpFill > 0) {
            DrawBox(xpBarX, xpBarY, xpBarX + xpFill, xpBarY + 14, GetColor(80, 200, 255), TRUE);
        }
        DrawBox(xpBarX, xpBarY, xpBarX + xpBarWidth, xpBarY + 14, GetColor(0, 180, 255), FALSE);
        DrawFormatString(xpBarX + 3, xpBarY, GetColor(255, 255, 255), "XP: %d / %d", player->GetXp(), player->GetXpNeeded());

        // �X�y���J�[�h�i�K�E�Z�j�̏����󋵂���o�I�ɒʒm���邽�߂̃Q�[�W����
        DrawFormatString(20, 90, GetColor(255, 100, 200), "SPELL");
        int spellBarY = 105;
        int spellFill = static_cast<int>(xpBarWidth * displaySpellRatio);
        
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

        // ���x���A�b�v���̎��o�I�ȕ�V������߂邽�߈��t���[��������_�ŕ`��
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
            //DrawString(Utility::SCREEN_WIDTH - 220, 20, "BOSS BATTLE!", GetColor(255, 50, 50));
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

        int fillWidth = static_cast<int>(barWidth * bossHpRatio);
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
            // �J�b�g�C���o�ꎞ�̐�������o���邽�߃C�[�W���O������č����ړ�
            float t = progress / 15.0f;
            xOffset = Utility::SCREEN_WIDTH * (1.0f - t);
        } else if (progress <= 75) {
            // �v���C���[�ɃJ�b�g�C����e����F�����邽�ߒ����t�߂Ŕ����ړ���ێ�
            float t = (progress - 15) / 60.0f;
            xOffset = -30.0f * t;
        } else {
            // ���o�I����ɑ��₩�ɉ�ʊO�֑ޏꂳ���邽�߂̍��W�v�Z
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
            if (Player::selectedCharacterType == 2) spellName = "SPELL CARD: RAINBOW WAVE!!";
            else if (Player::selectedCharacterType == 3) spellName = "SPELL CARD: CHERRY BLOSSOM!!";
            DrawFormatString(static_cast<int>(xOffset) + 100, 500, GetColor(0, 255, 255), "%s", spellName);
        }
    }
}
