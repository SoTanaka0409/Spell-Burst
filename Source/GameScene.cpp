#include "GameScene.h"
#include "ObjectManager.h"
#include "InputManager.h"
#include "Master.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyManager.h"
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
    Scene::Draw();

    DrawString(100, 100, "GAME SCENE (Press ENTER to Result)", GetColor(255, 255, 255));

    // Draw debug information
    DrawFormatString(100, 130, GetColor(255, 255, 0), "Object Count: %d", (int)GetObjectManager()->GetObjectCount());
    
    // Draw Player HP if player is active
    Player* player = dynamic_cast<Player*>(GetObjectManager()->GetObject2DByTag(Object2D::Tag2D_Player));
    if (player != nullptr) {
        DrawFormatString(100, 160, GetColor(100, 255, 100), "Player HP: %d / %d", player->GetHp(), player->GetMaxHp());
    }

    int yOffset = 190;
    for (auto obj : GetObjectManager()->GetObjectList()) {
        VECTOR pos = obj->GetPosition();
        DrawFormatString(100, yOffset, GetColor(0, 255, 255), "Object at (%.1f, %.1f) - DrawFlag: %d", pos.x, pos.y, obj->IsDrawFlag() ? 1 : 0);
        yOffset += 20;
    }
}

void GameScene::Finalize() {
    DebugLog("GameScene::Finalize() called!\n");
    GetObjectManager()->DeleteAll2D();
}
