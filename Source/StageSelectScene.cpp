#include "StageSelectScene.h"
#include "InputManager.h"
#include "Master.h"
<<<<<<< HEAD
=======
#include "GameScene.h"
#include "ResourceManager.h"
>>>>>>> main
#include <DxLib.h>

void StageSelectScene::Initialize()
{
}

void StageSelectScene::Update() {
<<<<<<< HEAD
    if (InputManager::CheckDownKey(KEY_INPUT_RETURN) || InputManager::CheckDownKey(KEY_INPUT_Z)) {
        Master::sceneManager->SetNextScene(SceneManager::SCENE_GAME);
=======
    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);
    
    if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
        if (mouseX >= 250 && mouseX <= 550 && mouseY >= 150 && mouseY <= 250) {
            GameScene::s_currentStage = 1;
            Master::sceneManager->SetNextScene(SceneManager::SCENE_GAME);
        } else if (mouseX >= 250 && mouseX <= 550 && mouseY >= 280 && mouseY <= 380) {
            GameScene::s_currentStage = 2;
            Master::sceneManager->SetNextScene(SceneManager::SCENE_GAME);
        } else if (mouseX >= 250 && mouseX <= 550 && mouseY >= 410 && mouseY <= 510) {
            GameScene::s_currentStage = 3;
            Master::sceneManager->SetNextScene(SceneManager::SCENE_GAME);
        }
>>>>>>> main
    }
}

void StageSelectScene::Draw() {
<<<<<<< HEAD
    Scene::Draw();
    DrawString(100, 100, "STAGE SELECT SCENE (Press ENTER to Game)", GetColor(255, 255, 255));
=======
    DrawBox(0, 0, 800, 600, GetColor(20, 25, 40), TRUE);
    Scene::Draw();
    
    int titleFont = ResourceManager::GetInstance()->GetFont(48, 5);
    int stageFont = ResourceManager::GetInstance()->GetFont(32, 4);
    
    DrawStringToHandle(180, 50, "- SELECT STAGE LEVEL -", GetColor(255, 255, 255), titleFont);
    
    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);
    
    // Stage 1 (NORMAL) - Green
    bool hover1 = (mouseX >= 250 && mouseX <= 550 && mouseY >= 150 && mouseY <= 250);
    int c1 = hover1 ? GetColor(150, 255, 150) : GetColor(50, 150, 50);
    DrawBox(250, 150, 550, 250, c1, TRUE);
    DrawBox(250, 150, 550, 250, GetColor(255, 255, 255), FALSE); // Border
    DrawStringToHandle(270, 185, "STAGE 1 : NORMAL", GetColor(0, 0, 0), stageFont);
    
    // Stage 2 (HARD) - Orange
    bool hover2 = (mouseX >= 250 && mouseX <= 550 && mouseY >= 280 && mouseY <= 380);
    int c2 = hover2 ? GetColor(255, 200, 100) : GetColor(200, 100, 20);
    DrawBox(250, 280, 550, 380, c2, TRUE);
    DrawBox(250, 280, 550, 380, GetColor(255, 255, 255), FALSE); // Border
    DrawStringToHandle(270, 315, "STAGE 2 : HARD", GetColor(0, 0, 0), stageFont);
    
    // Stage 3 (VERY HARD) - Red
    bool hover3 = (mouseX >= 250 && mouseX <= 550 && mouseY >= 410 && mouseY <= 510);
    int c3 = hover3 ? GetColor(255, 100, 100) : GetColor(180, 30, 30);
    DrawBox(250, 410, 550, 510, c3, TRUE);
    DrawBox(250, 410, 550, 510, GetColor(255, 255, 255), FALSE); // Border
    DrawStringToHandle(270, 445, "STAGE 3 : VERY HARD", GetColor(255, 255, 255), stageFont);
>>>>>>> main
}

void StageSelectScene::Finalize() {
}
