#include "ResultScene.h"
#include "SceneManager.h"
#include "Master.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Utility.h"
#include <DxLib.h>
#include <cmath>

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
    
    // Draw nice solid background
    DrawBox(0, 0, Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT, GetColor(0, 10, 20), TRUE);

    int titleFont = ResourceManager::GetInstance()->GetFont(72, 8);
    int subFont = ResourceManager::GetInstance()->GetFont(32, 4);
    int promptFont = ResourceManager::GetInstance()->GetFont(24, 2);
    
    // Pulsing effect
    int time = GetNowCount();
    int alpha = (int)(128 + 127 * std::sin(time / 200.0f));

    if (s_isVictory) {
        // Draw huge victory text
        DrawStringToHandle(220, 150, "VICTORY!", GetColor(255, 215, 0), titleFont);
        DrawStringToHandle(120, 300, "YOU DEFEATED THE FISHMAN KING!", GetColor(255, 255, 255), subFont);
        DrawStringToHandle(150, 350, "YOU ARE THE ULTIMATE CHEF!", GetColor(100, 255, 100), subFont);
    } else {
        // Draw defeat text in red
        DrawStringToHandle(180, 150, "GAME OVER", GetColor(255, 50, 50), titleFont);
        DrawStringToHandle(100, 300, "THE DEEP OCEAN DEPTHS CONSUMED YOU.", GetColor(255, 100, 100), subFont);
    }

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
    DrawStringToHandle(200, 500, "Press ENTER / Z to return to Title", GetColor(200, 200, 200), promptFont);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void ResultScene::Finalize() {
}
