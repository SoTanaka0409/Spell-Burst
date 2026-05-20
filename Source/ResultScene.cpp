#include "ResultScene.h"
#include "InputManager.h"
#include "Master.h"
#include <DxLib.h>

bool ResultScene::s_isVictory = false;

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
    
    // Draw nice solid blue/black background
    DrawBox(0, 0, 1280, 720, GetColor(0, 10, 20), TRUE);

    if (s_isVictory) {
        // Draw huge victory text with gold border
        DrawFormatString(320, 240, GetColor(255, 215, 0), "=================================");
        DrawFormatString(440, 290, GetColor(255, 255, 255), "VICTORY! YOU DEFEATED THE FISHMAN KING!");
        DrawFormatString(480, 340, GetColor(100, 255, 100), "YOU ARE THE ULTIMATE SUSHI CHEF APPRENTICE!");
        DrawFormatString(320, 390, GetColor(255, 215, 0), "=================================");
    } else {
        // Draw defeat text in red
        DrawFormatString(320, 240, GetColor(255, 50, 50), "=================================");
        DrawFormatString(520, 290, GetColor(255, 100, 100), "GAME OVER...");
        DrawFormatString(440, 340, GetColor(255, 255, 255), "THE DEEP OCEAN DEPTHS CONSUMED YOU.");
        DrawFormatString(320, 390, GetColor(255, 50, 50), "=================================");
    }

    DrawString(470, 500, "Press ENTER / Z to return to Title", GetColor(200, 200, 200));
}

void ResultScene::Finalize() {
}
