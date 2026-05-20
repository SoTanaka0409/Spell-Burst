#include "ResultScene.h"
#include "InputManager.h"
#include "Master.h"
#include <DxLib.h>

void ResultScene::Initialize() {
}

void ResultScene::Update() {
    if (InputManager::CheckDownKey(KEY_INPUT_RETURN) || InputManager::CheckDownKey(KEY_INPUT_Z)) {
        Master::sceneManager->SetNextScene(SceneManager::SCENE_TITLE);
    }
    Scene::Update();
}

void ResultScene::Draw() {
    Scene::Draw();
    DrawString(100, 100, "RESULT SCENE (Press ENTER to Title)", GetColor(255, 255, 255));
}

void ResultScene::Finalize() {
}
