#include "TitleScene.h"
#include "InputManager.h"
#include "TitleScene.h"
#include "InputManager.h"
#include "Master.h"
#include "Player.h"
#include "ResourceManager.h"
#include "Utility.h"
#include <DxLib.h>
#include <cmath>

TitleScene::TitleScene() : m_bgGraph(-1), m_bgScrollX(0.0f)
{

}
TitleScene::~TitleScene()
{

}
void TitleScene::Initialize()
{
    m_bgGraph = ResourceManager::GetInstance()->GetGraph("Resource/background.png");
    m_bgScrollX = 0.0f;
}

void TitleScene::Update()
{
    static int prevMouseInput = 0;
    int currentMouseInput = GetMouseInput();
    bool isLeftClicked = (currentMouseInput & MOUSE_INPUT_LEFT) != 0 && (prevMouseInput & MOUSE_INPUT_LEFT) == 0;
    prevMouseInput = currentMouseInput;

    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);
    
    if (isLeftClicked) {
        // Button 1: GAME START
        if (mouseX >= 250 && mouseX <= 550 && mouseY >= 250 && mouseY <= 330) {
            Master::sceneManager->SetNextScene(SceneManager::SCENE_LEVEL);
        }
        // Button 2: SETTINGS (RULE)
        else if (mouseX >= 250 && mouseX <= 550 && mouseY >= 350 && mouseY <= 430) {
            Master::sceneManager->SetNextScene(SceneManager::SCENE_RULE);
        }
        // Button 3: EXIT
        else if (mouseX >= 250 && mouseX <= 550 && mouseY >= 450 && mouseY <= 530) {
            Master::sceneManager->SetNextScene(SceneManager::SCENE_NONE);
        }
    }
    
    // Update Background scroll
    m_bgScrollX += 1.0f * Utility::TimeScale;
    if (m_bgScrollX >= Utility::SCREEN_WIDTH) {
        m_bgScrollX -= Utility::SCREEN_WIDTH;
    }
    
    Scene::Update();
}

void TitleScene::Draw() {
    // 1. Draw scrolling background
    if (m_bgGraph != -1) {
        float sw = Utility::SCREEN_WIDTH;
        float sh = Utility::SCREEN_HEIGHT;
        DrawExtendGraph(static_cast<int>(-m_bgScrollX), 0, static_cast<int>(-m_bgScrollX + sw), static_cast<int>(sh), m_bgGraph, FALSE);
        DrawExtendGraph(static_cast<int>(-m_bgScrollX + sw), 0, static_cast<int>(-m_bgScrollX + sw * 2), static_cast<int>(sh), m_bgGraph, FALSE);
    } else {
        DrawBox(0, 0, 800, 600, GetColor(15, 20, 30), TRUE); // Deep sea color fallback
    }
    Scene::Draw();
    
    // 2. Draw Title Text
    int titleFont = ResourceManager::GetInstance()->GetFont(60, 5);
    int subFont = ResourceManager::GetInstance()->GetFont(32, 4);
    
    DrawStringToHandle(120, 80, "AI SUSHI CHEF", GetColor(255, 215, 0), titleFont);
    
    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);
    
    // Button 1: GAME START
    bool hover1 = (mouseX >= 250 && mouseX <= 550 && mouseY >= 250 && mouseY <= 330);
    DrawBox(250, 250, 550, 330, hover1 ? GetColor(100, 150, 100) : GetColor(50, 100, 50), TRUE);
    DrawBox(250, 250, 550, 330, GetColor(255, 255, 255), FALSE);
    DrawStringToHandle(300, 275, "GAME START", GetColor(255, 255, 255), subFont);
    
    // Button 2: SETTINGS
    bool hover2 = (mouseX >= 250 && mouseX <= 550 && mouseY >= 350 && mouseY <= 430);
    DrawBox(250, 350, 550, 430, hover2 ? GetColor(100, 100, 150) : GetColor(50, 50, 100), TRUE);
    DrawBox(250, 350, 550, 430, GetColor(255, 255, 255), FALSE);
    DrawStringToHandle(320, 375, "SETTINGS", GetColor(255, 255, 255), subFont);
    
    // Button 3: EXIT
    bool hover3 = (mouseX >= 250 && mouseX <= 550 && mouseY >= 450 && mouseY <= 530);
    DrawBox(250, 450, 550, 530, hover3 ? GetColor(150, 100, 100) : GetColor(100, 50, 50), TRUE);
    DrawBox(250, 450, 550, 530, GetColor(255, 255, 255), FALSE);
    DrawStringToHandle(350, 475, "EXIT", GetColor(255, 255, 255), subFont);
}

void TitleScene::Finalize() {
}
