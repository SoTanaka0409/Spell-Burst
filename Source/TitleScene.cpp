#include "TitleScene.h"
#include "InputManager.h"
#include "Master.h"
#include <DxLib.h>

TitleScene::TitleScene()
{

}
TitleScene::~TitleScene()
{

}
void TitleScene::Initialize()
{

}

void TitleScene::Update()
{
    if (InputManager::CheckDownKey(KEY_INPUT_RETURN) || InputManager::CheckDownKey(KEY_INPUT_Z)) {
        Master::sceneManager->SetNextScene(SceneManager::SCENE_GAME);
    }
    Scene::Update();
}

void TitleScene::Draw() {
    Scene::Draw();
    DrawString(100, 100, "TITLE SCENE (Press ENTER to Start)", GetColor(255, 255, 255));
}

void TitleScene::Finalize() {
}
