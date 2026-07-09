#include "TitleScene.h"
#include "ObjectManager.h"
#include "InputManager.h"
#include "Master.h"
#include "Player.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "Utility.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include <cmath>

TitleScene::TitleScene() : bg_graph_(-1), bg_scroll_x_(0.0f), ui_button_graph_(-1)
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
    bg_graph_ = ResourceManager::GetInstance()->GetGraph("Resource/background.png");
    ui_button_graph_ = ResourceManager::GetInstance()->GetGraph("Resource/ui_button.png");
    bg_scroll_x_ = 0.0f;
    SoundManager::GetInstance()->PlayBGM("Resource/BGM/MusMus-BGM-096.3");
    Utility::LoadTimeRanking(rankings_);
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
            SoundManager::GetInstance()->PlaySE("Resource/SE/se_button1.mp3");
            Master::sceneManager->SetNextScene(SceneManager::SCENE_LEVEL);
        }
        else if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= btnY2 && mouseY <= btnY2 + btnH) {
            SoundManager::GetInstance()->PlaySE("Resource/SE/se_button1.mp3");
            Master::sceneManager->SetNextScene(SceneManager::SCENE_RULE);
        }
        else if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= btnY3 && mouseY <= btnY3 + btnH) {
            SoundManager::GetInstance()->PlaySE("Resource/SE/se_button1.mp3");
            Master::sceneManager->SetNextScene(SceneManager::SCENE_NONE);
        }
    }
    
    // �w�i�摜���ɍ������փX�N���[�������A������̂���^�C�g����ʂ���o
    bg_scroll_x_ += 1.0f * Utility::TimeScale;
    if (bg_scroll_x_ >= Utility::SCREEN_WIDTH) {
        bg_scroll_x_ -= Utility::SCREEN_WIDTH;
    }
    
    Scene::Update();
}

void TitleScene::Draw() {
    if (bg_graph_ != -1) {
        float sw = Utility::SCREEN_WIDTH;
        float sh = Utility::SCREEN_HEIGHT;
        DrawExtendGraph(static_cast<int>(-bg_scroll_x_), 0, static_cast<int>(-bg_scroll_x_ + sw), static_cast<int>(sh), bg_graph_, FALSE);
        DrawExtendGraph(static_cast<int>(-bg_scroll_x_ + sw), 0, static_cast<int>(-bg_scroll_x_ + sw * 2), static_cast<int>(sh), bg_graph_, FALSE);
    } else {
        DrawBox(0, 0, Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT, GetColor(15, 20, 30), TRUE);
    }
    Scene::Draw();
    
        int rankFont = ResourceManager::GetInstance()->GetFont(32, 2);
    DrawStringToHandle(Utility::SCREEN_WIDTH - 320, 50, "TIME ATTACK TOP 3", GetColor(200, 200, 255), rankFont);
    for (size_t i = 0; i < rankings_.size() && i < 3; ++i) {
        int totalMs = rankings_[i];
        int ms = totalMs % 1000;
        int totalSec = totalMs / 1000;
        int sec = totalSec % 60;
        int min = totalSec / 60;
        char rankStr[64];
        sprintf_s(rankStr, "%d�� %02d:%02d.%03d", (int)i+1, min, sec, ms);
        DrawStringToHandle(Utility::SCREEN_WIDTH - 300, 100 + static_cast<int>(i) * 50, rankStr, GetColor(255, 215, 0), rankFont);
    }
    
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
        if (ui_button_graph_ != -1) {
            if (hover) {
                SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
                DrawExtendGraph(x, y, x + btnW, y + btnH, ui_button_graph_, TRUE);
                SetDrawBlendMode(DX_BLENDMODE_ADD, 100);
                DrawBox(x, y, x + btnW, y + btnH, GetColor(0, 200, 255), TRUE); // �I��\��UI�ł��邱�Ƃ�������邽�ߔ����G�t�F�N�g����Z
                SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
            } else {
                SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
                DrawExtendGraph(x, y, x + btnW, y + btnH, ui_button_graph_, TRUE);
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

