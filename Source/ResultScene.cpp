#include "ResultScene.h"
#include "InputManager.h"
#include "Master.h"
#include "SceneManager.h"
#include <DxLib.h>

void ResultScene::Initialize() {
    // 初期化処理（スコアの計算や結果の表示準備など）
}

void ResultScene::Update() {
    // 基底クラスのUpdate
    Scene::Update();

    // Zキーまたはエンターキーが押された瞬間にタイトル画面へ戻る
    if (InputManager::CheckDownKey(KEY_INPUT_RETURN) || InputManager::CheckDownKey(KEY_INPUT_Z)) {
        Master::sceneManager->SetNextScene(SceneManager::SCENE_TYPE::SCENE_TITLE);
        Master::sceneManager->ChangeSceneIfNeeded();
    }
}

void ResultScene::Draw() {
    Scene::Draw();
    DrawString(100, 100, "RESULT SCENE (Press ENTER to Title)", GetColor(255, 255, 255));
}

void ResultScene::Finalize() {
}
