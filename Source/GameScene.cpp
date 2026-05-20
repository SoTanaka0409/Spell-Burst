#include "GameScene.h"
#include "ObjectManager.h"
#include "InputManager.h"
#include "Master.h"
#include <DxLib.h>

GameScene::GameScene() {
}

GameScene::~GameScene() {
}

void GameScene::Initialize() {
    // 全オブジェクトの初期化
    if (GetObjectManager() != nullptr)
    {
        GetObjectManager()->DeleteAll2D();
    }
}

void GameScene::Update() {
    // 基底クラスのUpdate（ObjectManager・ColliderManagerの更新）
    Scene::Update();

    // Zキーまたはエンターキーが押されたらリザルト画面へ遷移
    if (InputManager::CheckDownKey(KEY_INPUT_RETURN) || InputManager::CheckDownKey(KEY_INPUT_Z)) {
        Master::sceneManager->SetNextScene(SceneManager::SCENE_TYPE::SCENE_RESULT);
        Master::sceneManager->ChangeSceneIfNeeded();
    }
}

void GameScene::Draw() {
    // 背景色を設定
    SetBackgroundColor(20, 30, 60);

    // 基底クラスのDraw（ObjectManagerの描画）
    Scene::Draw();

    DrawString(100, 100, "GAME SCENE (Press ENTER to Result)", GetColor(255, 255, 255));
}

void GameScene::Finalize() {
}
