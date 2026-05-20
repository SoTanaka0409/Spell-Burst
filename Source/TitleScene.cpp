#include "TitleScene.h"
#include "InputManager.h"
#include "Master.h"
#include "SceneManager.h"
#include <DxLib.h>

void TitleScene::Initialize() {
    // 初期化処理（画像の読み込みなど）
}

void TitleScene::Update() {
    // 基底クラスのUpdate
    Scene::Update();

    // Zキーまたはエンターキーが押された瞬間だけゲーム画面へ遷移
    if (InputManager::CheckDownKey(KEY_INPUT_RETURN) || InputManager::CheckDownKey(KEY_INPUT_Z)) {
        Master::sceneManager->SetNextScene(SceneManager::SCENE_TYPE::SCENE_GAME);
        Master::sceneManager->ChangeSceneIfNeeded();
    }
}

void TitleScene::Draw() {
    Scene::Draw();
    DrawString(100, 100, "TITLE SCENE (Press ENTER to Start)", GetColor(255, 255, 255));
}

void TitleScene::Finalize() {
}
