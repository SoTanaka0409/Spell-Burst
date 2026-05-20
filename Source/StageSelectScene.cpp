#include "StageSelectScene.h"
#include "InputManager.h"
#include "Master.h"
#include "SceneManager.h"
#include <DxLib.h>

void StageSelectScene::Initialize() {
    // 初期化処理（画像の読み込みなど）
}

void StageSelectScene::Update() {
    // 基底クラスのUpdate
    Scene::Update();

    // Zキーまたはエンターキーが押された瞬間にゲーム画面へ遷移
    if (InputManager::CheckDownKey(KEY_INPUT_RETURN) || InputManager::CheckDownKey(KEY_INPUT_Z)) {
        Master::sceneManager->SetNextScene(SceneManager::SCENE_TYPE::SCENE_GAME);
        Master::sceneManager->ChangeSceneIfNeeded();
    }
}

void StageSelectScene::Draw() {
    Scene::Draw();
    DrawString(100, 100, "STAGE SELECT SCENE (Press ENTER to Game)", GetColor(255, 255, 255));
}

void StageSelectScene::Finalize() {
}
