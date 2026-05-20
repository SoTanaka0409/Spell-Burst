#include "GameScene.h"
#include "ObjectManager.h"
#include "InputManager.h"
#include "Master.h"
#include "Player.h"
#include "Enemy.h"
#include <DxLib.h>
#include "DebugLog.h"

GameScene::GameScene() {
}

GameScene::~GameScene() {
}

void GameScene::Initialize() {
    DebugLog("GameScene::Initialize() called!\n");
    // Create player (automatically registered to current scene's ObjectManager)
    new Player();

    // Create test enemies
    new Enemy(640.0f, 100.0f);
    new Enemy(440.0f, 150.0f);
    new Enemy(840.0f, 200.0f);
}

void GameScene::Update() {
    Scene::Update();

    if (InputManager::CheckDownKey(KEY_INPUT_RETURN) || InputManager::CheckDownKey(KEY_INPUT_Z)) {
        Master::sceneManager->SetNextScene(SceneManager::SCENE_RESULT);
    }
}

void GameScene::Draw() {
    Scene::Draw();

    DrawString(100, 100, "GAME SCENE (Press ENTER to Result)", GetColor(255, 255, 255));

    // Draw debug information
    DrawFormatString(100, 130, GetColor(255, 255, 0), "Object Count: %d", (int)GetObjectManager()->GetObjectCount());
    int yOffset = 160;
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
