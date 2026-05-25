#include "TitleScene.h"
#include "InputManager.h"
#include "Master.h"
#include "Player.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "Utility.h"
#include <DxLib.h>
#include <cmath>

TitleScene::TitleScene() : m_bgGraph(-1), m_bgScrollX(0.0f), m_uiButtonGraph(-1)
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
    m_bgGraph = ResourceManager::GetInstance()->GetGraph("Resource/background.png");
    m_uiButtonGraph = ResourceManager::GetInstance()->GetGraph("Resource/ui_button.png");
    m_bgScrollX = 0.0f;
    SoundManager::GetInstance()->PlayBGM("Resource/BGM/MusMus-BGM-096.mp3");
}

void TitleScene::Update()
{
    static int prevMouseInput = 0;
    int currentMouseInput = GetMouseInput();
    bool isLeftClicked = (currentMouseInput & MOUSE_INPUT_LEFT) != 0 && (prevMouseInput & MOUSE_INPUT_LEFT) == 0;
    prevMouseInput = currentMouseInput;

    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);
    
    int btnW = 300;
    int btnH = 80;
    int btnX = (Utility::SCREEN_WIDTH - btnW) / 2;
    int btnY1 = Utility::SCREEN_HEIGHT / 2 - 50;
    int btnY2 = btnY1 + 100;
    int btnY3 = btnY2 + 100;
    
    if (isLeftClicked) {
        if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= btnY1 && mouseY <= btnY1 + btnH) {
            SoundManager::GetInstance()->PlaySE("Resource/se_click.wav");
            Master::sceneManager->SetNextScene(SceneManager::SCENE_LEVEL);
        }
        else if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= btnY2 && mouseY <= btnY2 + btnH) {
            SoundManager::GetInstance()->PlaySE("Resource/se_click.wav");
            Master::sceneManager->SetNextScene(SceneManager::SCENE_RULE);
        }
        else if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= btnY3 && mouseY <= btnY3 + btnH) {
            SoundManager::GetInstance()->PlaySE("Resource/se_click.wav");
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
    if (m_bgGraph != -1) {
        float sw = Utility::SCREEN_WIDTH;
        float sh = Utility::SCREEN_HEIGHT;
        DrawExtendGraph(static_cast<int>(-m_bgScrollX), 0, static_cast<int>(-m_bgScrollX + sw), static_cast<int>(sh), m_bgGraph, FALSE);
        DrawExtendGraph(static_cast<int>(-m_bgScrollX + sw), 0, static_cast<int>(-m_bgScrollX + sw * 2), static_cast<int>(sh), m_bgGraph, FALSE);
    } else {
        DrawBox(0, 0, Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT, GetColor(15, 20, 30), TRUE);
    }
    Scene::Draw();
    
    int titleFont = ResourceManager::GetInstance()->GetFont(60, 5);
    int subFont = ResourceManager::GetInstance()->GetFont(32, 4);
    
    int titleW = GetDrawStringWidthToHandle("AI SUSHI CHEF", 13, titleFont);
    DrawStringToHandle((Utility::SCREEN_WIDTH - titleW) / 2, Utility::SCREEN_HEIGHT / 4 - 30, "AI SUSHI CHEF", GetColor(255, 215, 0), titleFont);
    
    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);
    
    int btnW = 300;
    int btnH = 80;
    int btnX = (Utility::SCREEN_WIDTH - btnW) / 2;
    int btnY1 = Utility::SCREEN_HEIGHT / 2 - 50;
    int btnY2 = btnY1 + 100;
    int btnY3 = btnY2 + 100;
    
    auto drawBtn = [&](int x, int y, const char* text, bool hover) {
        if (m_uiButtonGraph != -1) {
            if (hover) {
                SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
                DrawExtendGraph(x, y, x + btnW, y + btnH, m_uiButtonGraph, TRUE);
                SetDrawBlendMode(DX_BLENDMODE_ADD, 100);
                DrawBox(x, y, x + btnW, y + btnH, GetColor(0, 200, 255), TRUE); // Glow effect
                SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
            } else {
                SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
                DrawExtendGraph(x, y, x + btnW, y + btnH, m_uiButtonGraph, TRUE);
                SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
            }
        } else {
            DrawBox(x, y, x + btnW, y + btnH, hover ? GetColor(100, 150, 100) : GetColor(50, 100, 50), TRUE);
            DrawBox(x, y, x + btnW, y + btnH, GetColor(255, 255, 255), FALSE);
        }
        
        int tw = GetDrawStringWidthToHandle(text, (int)strlen(text), subFont);
        DrawStringToHandle(x + (btnW - tw) / 2, y + (btnH - 32) / 2, text, GetColor(255, 255, 255), subFont);
    };
    
    bool hover1 = (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= btnY1 && mouseY <= btnY1 + btnH);
    drawBtn(btnX, btnY1, "GAME START", hover1);
    
    bool hover2 = (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= btnY2 && mouseY <= btnY2 + btnH);
    drawBtn(btnX, btnY2, "SETTINGS", hover2);
    
    bool hover3 = (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= btnY3 && mouseY <= btnY3 + btnH);
    drawBtn(btnX, btnY3, "EXIT", hover3);
}

void TitleScene::Finalize() {
}
