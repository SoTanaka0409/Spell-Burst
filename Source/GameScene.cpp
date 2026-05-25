#include "SoundManager.h"
#include "GameScene.h"
#include "ObjectManager.h"
#include "InputManager.h"
#include "Master.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "Boss.h"
#include <DxLib.h>
#include "DebugLog.h"
#include <cstdlib>
#include "Utility.h"
#include "ResourceManager.h"

GameScene::GameScene() 
    : mpEnemyManager(nullptr)
    , m_cutinTimer(0)
    , m_cutinImageHandle(-1)
{
}

GameScene::~GameScene() {
    if (mpEnemyManager != nullptr) {
        delete mpEnemyManager;
        mpEnemyManager = nullptr;
    }
}

// 繧繝ｼ繝ｺ縺ｮ曻晄悄四?、逅・
// Encouragement Ξ 繧, 繝, 繝ｼ繧∵ 繝繧槭郎繝ｼ繧ｹ繝” 繝ｼ縲∝?ｮｮｪｪ?ｯｯ繧繝 繧ｧ繧ｯ繧繝
void GameScene::Initialize() {
    DebugLog("GameScene::Initialize() called!\n");
    srand(static_cast<unsigned int>(GetNowCount()));

    // Create EnemyManager
    mpEnemyManager = new EnemyManager();
    mpEnemyManager->Initialize();

    m_cutinTimer = 0;
    m_cutinImageHandle = ResourceManager::GetInstance()->GetGraph("Resource/cutin_mackerel.png");

    // Create player (automatically registered to current scene's ObjectManager)
    new Player();

    // Create initial test enemies through EnemyManager (horizontal scrolling)
    mpEnemyManager->SpawnEnemy(1330.0f, 150.0f);
    mpEnemyManager->SpawnEnemy(1330.0f, 350.0f);
    mpEnemyManager->SpawnEnemy(1330.0f, 550.0f);
}

// If you are weak, you will be disappointed.
// ESC 繧ｭ繝ｼ縺ｫ繧Physician 繝sub・繧ｺ讖溯・?ｮ｜ｦ逅・√♀繧Physician・繧ｲ繝ｼ繝荳ｭ
void GameScene::Update() {
    if (m_cutinTimer > 0) {
        m_cutinTimer--;
        return; // I'm sorry, but I'm not in agony.
    }

    Scene::Update();

    // Update EnemyManager (spawns enemies dynamically)
    if (mpEnemyManager != nullptr) {
        mpEnemyManager->Update();
    }

    if (InputManager::CheckDownKey(KEY_INPUT_RETURN)) {
        Master::sceneManager->SetNextScene(SceneManager::SCENE_RESULT);
    }
}

// If you are weak, you will not be able to meet the spider.
// Do you want to go to the hospital? 
void GameScene::Draw() {
    // Draw Stage Background (Underwater ocean world)
    int s_bgGraphHandle = ResourceManager::GetInstance()->GetGraph("Resource/background.png");
    if (s_bgGraphHandle != -1) {
        DrawExtendGraph(0, 0, Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT, s_bgGraphHandle, FALSE);
    }

    // Draw game objects
    Scene::Draw();

    // HUD Panel
    Player* player = dynamic_cast<Player*>(GetObjectManager()->GetObject2DByTag(Object2D::Tag2D_Player));
    if (player != nullptr) {
        // Draw elegant semi-transparent background box for HUD (taller to fit Level/XP and Spell Gauge)
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
        DrawBox(10, 10, 320, 230, GetColor(0, 15, 30), TRUE); // Ocean dark theme
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        DrawBox(10, 10, 320, 230, GetColor(0, 128, 255), FALSE); // border

        // Player HP
        DrawFormatString(20, 20, GetColor(100, 255, 100), "PLAYER HP: %d / %d", player->GetHp(), player->GetMaxHp());

        // Attack Mode HUD
        DrawString(20, 45, "ATTACK MODE [Q / 1-2 to switch]:", GetColor(255, 255, 255));
        
        Player::AttackMode mode = player->GetAttackMode();
        unsigned int colorSelected = GetColor(255, 215, 0); // Gold
        unsigned int colorUnselected = GetColor(120, 180, 200); // Aqua gray

     
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

        // === Level & XP HUD ===
        DrawFormatString(20, 140, GetColor(255, 215, 0), "LV: %d", player->GetLevel());

        // XP progress bar
        int xpBarWidth = 260;
        int xpBarX = 35;
        int xpBarY = 162;
        float xpRatio = (player->GetXpNeeded() > 0) 
            ? static_cast<float>(player->GetXp()) / static_cast<float>(player->GetXpNeeded()) 
            : 1.0f;
        int xpFill = static_cast<int>(xpBarWidth * xpRatio);
        DrawBox(xpBarX, xpBarY, xpBarX + xpBarWidth, xpBarY + 14, GetColor(20, 40, 80), TRUE);
        if (xpFill > 0) {
            DrawBox(xpBarX, xpBarY, xpBarX + xpFill, xpBarY + 14, GetColor(80, 200, 255), TRUE);
        }
        DrawBox(xpBarX, xpBarY, xpBarX + xpBarWidth, xpBarY + 14, GetColor(0, 180, 255), FALSE);
        DrawFormatString(xpBarX + 3, xpBarY, GetColor(255, 255, 255), "XP: %d / %d", player->GetXp(), player->GetXpNeeded());

        // === Spell Card Gauge ===
        DrawFormatString(20, 180, GetColor(255, 100, 200), "SPELL");
        int spellBarY = 195;
        float spellRatio = static_cast<float>(player->GetSpellGauge()) / static_cast<float>(player->GetMaxSpellGauge());
        int spellFill = static_cast<int>(xpBarWidth * spellRatio);
        
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

        // === LEVEL UP! Flash Effect (above player character) ===
        int lvTimer = player->GetLevelUpTimer();
        if (lvTimer > 0) {
            // Flicker every 10 frames for a blinking effect
            if ((lvTimer / 10) % 2 == 0) {
                int px = static_cast<int>(player->GetX());
                int py = static_cast<int>(player->GetY()) - 60;
                // Shadow text
                DrawFormatString(px - 58, py + 2, GetColor(0, 0, 0), "LEVEL UP!");
                // Main gold text
                DrawFormatString(px - 60, py, GetColor(255, 215, 0), "LEVEL UP!");
                DrawFormatString(px - 60, py + 18, GetColor(255, 255, 100), 
                    "LV.%d -> LV.%d", player->GetLevel() - 1, player->GetLevel());
            }
        }
    }

    // Defeated Enemies Score HUD (Top Right)
    if (mpEnemyManager != nullptr) {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
        DrawBox(Utility::SCREEN_WIDTH - 230, 10, Utility::SCREEN_WIDTH - 10, 50, GetColor(0, 15, 30), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        DrawBox(Utility::SCREEN_WIDTH - 230, 10, Utility::SCREEN_WIDTH - 10, 50, GetColor(0, 128, 255), FALSE);

        if (mpEnemyManager->GetDefeatedCount() >= 10) {
            DrawString(Utility::SCREEN_WIDTH - 220, 20, "BOSS BATTLE!", GetColor(255, 50, 50));
        } else {
            DrawFormatString(Utility::SCREEN_WIDTH - 220, 20, GetColor(255, 255, 255), "DEFEATED: %d / 10", mpEnemyManager->GetDefeatedCount());
        }
    }

    // Boss HP Bar (Top Center)
    Boss* boss = nullptr;
    for (auto obj : GetObjectManager()->GetObjectList()) {
        Boss* b = dynamic_cast<Boss*>(obj);
        if (b != nullptr) {
            boss = b;
            break;
        }
    }

    if (boss != nullptr && boss->IsActive()) {
        int barWidth = 400;
        int barHeight = 20;
        int barX = (Utility::SCREEN_WIDTH - barWidth) / 2;
        int barY = 50;

        // Semi-transparent panel
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
        DrawBox(barX - 10, barY - 25, barX + barWidth + 10, barY + barHeight + 5, GetColor(0, 15, 30), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        DrawBox(barX - 10, barY - 25, barX + barWidth + 10, barY + barHeight + 5, GetColor(255, 0, 0), FALSE); // red border

        // HP Fill
        float hpRatio = static_cast<float>(boss->GetHp()) / static_cast<float>(boss->GetMaxHp());
        int fillWidth = static_cast<int>(barWidth * hpRatio);
        if (fillWidth > 0) {
            DrawBox(barX, barY, barX + fillWidth, barY + barHeight, GetColor(255, 50, 50), TRUE);
        }
        DrawBox(barX, barY, barX + barWidth, barY + barHeight, GetColor(255, 255, 255), FALSE); // bar outline

        // Title and HP numeric text
        DrawFormatString(barX, barY - 20, GetColor(255, 215, 0), "BOSS: FISHMAN KING (PHASE %d)", 4 - boss->GetLives());
        DrawFormatString(barX + barWidth - 80, barY - 20, GetColor(255, 255, 255), "%d / %d", boss->GetHp(), boss->GetMaxHp());
    }

    // Small debug stats on bottom right
    DrawFormatString(1100, 680, GetColor(200, 200, 200), "Objects: %d", (int)GetObjectManager()->GetObjectCount());
    DrawFormatString(1100, 660, GetColor(200, 200, 200), "FPS: 60");

    // Draw Cut-in if active
    if (m_cutinTimer > 0) {
        int maxTimer = 90;
        int progress = maxTimer - m_cutinTimer; 
        
        // Slide from right to left smoothly
        float xOffset = Utility::SCREEN_WIDTH - (Utility::SCREEN_WIDTH * 2.0f * (progress / (float)maxTimer));
        
        if (m_cutinImageHandle != -1) {
            DrawExtendGraph(static_cast<int>(xOffset), 150, static_cast<int>(xOffset + Utility::SCREEN_WIDTH), 570, m_cutinImageHandle, TRUE);
        }

        // Darken the rest of the screen slightly
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
        DrawBox(0, 0, Utility::SCREEN_WIDTH, 150, GetColor(0, 0, 0), TRUE);
        DrawBox(0, 570, Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT, GetColor(0, 0, 0), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

        // Flashy spell card text
        if (progress > 10) {
            DrawFormatString(static_cast<int>(xOffset) + 100, 500, GetColor(0, 255, 255), "SPELL CARD: SCHOOL OF MACKEREL!!");
        }
    }
}

void GameScene::TriggerCutin() {
    m_cutinTimer = 90; // 1.5 seconds freeze
}

// Yuko Sono, ??ｮｦencounter,
// 繧繝ｼ繝ｳ?・j譖ｿ?凾縺縺ｪ縺ｫ臻ｼ縺ｰ繧?∝空逧・↓聒ｺ菫昴＠縺
void GameScene::Finalize() {
    DebugLog("GameScene::Finalize() called!\n");
    GetObjectManager()->DeleteAll2D();
}
