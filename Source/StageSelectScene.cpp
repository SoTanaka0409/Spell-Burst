#include "StageSelectScene.h"
#include "InputManager.h"
#include "Master.h"
#include <DxLib.h>

void StageSelectScene::Initialize()
{
}

void StageSelectScene::Update() {
    if (InputManager::CheckDownKey(KEY_INPUT_RETURN) || InputManager::CheckDownKey(KEY_INPUT_Z)) {
        Master::sceneManager->SetNextScene(SceneManager::SCENE_GAME);
    }
}

void StageSelectScene::Draw() {
    Scene::Draw();
    DrawString(100, 100, "STAGE SELECT SCENE (Press ENTER to Game)", GetColor(255, 255, 255));
}

void StageSelectScene::Finalize() {
}
