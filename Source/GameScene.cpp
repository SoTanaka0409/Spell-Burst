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

GameScene::GameScene() 
    : mpEnemyManager(nullptr)
{
}

GameScene::~GameScene() {
    if (mpEnemyManager != nullptr) {
        delete mpEnemyManager;
        mpEnemyManager = nullptr;
    }
}

void GameScene::Initialize() {
    DebugLog("GameScene::Initialize() called!\n");
    srand(static_cast<unsigned int>(GetNowCount()));

    // Create EnemyManager
    mpEnemyManager = new EnemyManager();
    mpEnemyManager->Initialize();

    // Create player (automatically registered to current scene's ObjectManager)
    new Player();

    // Create initial test enemies through EnemyManager (horizontal scrolling)
    mpEnemyManager->SpawnEnemy(1330.0f, 150.0f);
    mpEnemyManager->SpawnEnemy(1330.0f, 350.0f);
    mpEnemyManager->SpawnEnemy(1330.0f, 550.0f);
}

void GameScene::Update() {
    Scene::Update();

    // Update EnemyManager (spawns enemies dynamically)
    if (mpEnemyManager != nullptr) {
        mpEnemyManager->Update();
    }

    if (InputManager::CheckDownKey(KEY_INPUT_RETURN) || InputManager::CheckDownKey(KEY_INPUT_Z)) {
        Master::sceneManager->SetNextScene(SceneManager::SCENE_RESULT);
    }
}

void GameScene::Draw() {
    // Draw Stage Background (Underwater ocean world)
    static int s_bgGraphHandle = -1;
    if (s_bgGraphHandle == -1) {
        s_bgGraphHandle = LoadGraph("Resource/background.png");
    }
    if (s_bgGraphHandle != -1) {
        DrawExtendGraph(0, 0, 1280, 720, s_bgGraphHandle, FALSE);
    }

    // Draw game objects
    Scene::Draw();

    // HUD Panel
    Player* player = dynamic_cast<Player*>(GetObjectManager()->GetObject2DByTag(Object2D::Tag2D_Player));
    if (player != nullptr) {
        // Draw elegant semi-transparent background box for HUD (taller to fit Level/XP)
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
        DrawBox(10, 10, 320, 195, GetColor(0, 15, 30), TRUE); // Ocean dark theme
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        DrawBox(10, 10, 320, 195, GetColor(0, 128, 255), FALSE); // border

        // Player HP
        DrawFormatString(20, 20, GetColor(100, 255, 100), "PLAYER HP: %d / %d", player->GetHp(), player->GetMaxHp());

        // Attack Mode HUD
        DrawString(20, 45, "ATTACK MODE [Q / 1-3 to switch]:", GetColor(255, 255, 255));
        
        Player::AttackMode mode = player->GetAttackMode();
        unsigned int colorSelected = GetColor(255, 215, 0); // Gold
        unsigned int colorUnselected = GetColor(120, 180, 200); // Aqua gray

        DrawFormatString(35, 70, (mode == Player::AttackMode_Bullet) ? colorSelected : colorUnselected, 
            "[1] Bullet %s", (mode == Player::AttackMode_Bullet) ? "<SELECTED>" : "");
        DrawFormatString(35, 92, (mode == Player::AttackMode_Melee) ? colorSelected : colorUnselected, 
            "[2] Melee (Knife) %s", (mode == Player::AttackMode_Melee) ? "<SELECTED>" : "");

        int cd = player->GetSpecialCooldown();
        if (cd > 0) {
            DrawFormatString(35, 114, (mode == Player::AttackMode_Special) ? colorSelected : colorUnselected,
                "[3] Special [CD: %.1fs]", cd / 60.0f);
        } else {
            DrawFormatString(35, 114, (mode == Player::AttackMode_Special) ? colorSelected : colorUnselected,
                "[3] Special [READY] %s", (mode == Player::AttackMode_Special) ? "<SELECTED>" : "");
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
        DrawBox(1050, 10, 1270, 50, GetColor(0, 15, 30), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        DrawBox(1050, 10, 1270, 50, GetColor(0, 128, 255), FALSE);

        if (mpEnemyManager->GetDefeatedCount() >= 10) {
            DrawString(1060, 20, "BOSS BATTLE!", GetColor(255, 50, 50));
        } else {
            DrawFormatString(1060, 20, GetColor(255, 255, 255), "DEFEATED: %d / 10", mpEnemyManager->GetDefeatedCount());
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
        int barWidth = 600;
        int barHeight = 20;
        int barX = (1280 - barWidth) / 2;
        int barY = 35;

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
        DrawString(barX, barY - 20, "BOSS: FISHMAN KING", GetColor(255, 215, 0));
        DrawFormatString(barX + barWidth - 80, barY - 20, GetColor(255, 255, 255), "%d / %d", boss->GetHp(), boss->GetMaxHp());
    }

    // Small debug stats on bottom right
    DrawFormatString(1100, 680, GetColor(200, 200, 200), "Objects: %d", (int)GetObjectManager()->GetObjectCount());
    DrawFormatString(1100, 660, GetColor(200, 200, 200), "FPS: 60");
}

void GameScene::Finalize() {
    DebugLog("GameScene::Finalize() called!\n");
    GetObjectManager()->DeleteAll2D();
}
