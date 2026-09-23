#include "ConfigScene.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Utility.h"
#include "Master.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include <string>

ConfigScene::ConfigScene() : bg_graph_(-1), bg_scroll_x_(0.0f), ui_button_graph_(-1), font_handle_(-1)
{
}

ConfigScene::~ConfigScene()
{
}

void ConfigScene::Initialize()
{
    bg_graph_ = ResourceManager::GetInstance()->GetGraph("IMG_BG_TITLE");
    ui_button_graph_ = ResourceManager::GetInstance()->GetGraph("IMG_UI_BTN_BASE");
    font_handle_ = ResourceManager::GetInstance()->GetFont(32, 2);
}

void ConfigScene::Update()
{
    static int prevMouseInput = 0;
    int currentMouseInput = GetMouseInput();
    bool isLeftClicked = (currentMouseInput & MOUSE_INPUT_LEFT) != 0 && (prevMouseInput & MOUSE_INPUT_LEFT) == 0;
    prevMouseInput = currentMouseInput;

    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);

    int startY = Utility::kScreenHeight / 2 - 100;
    int spacingY = 120;
    int startX = Utility::kScreenWidth / 2;

    auto ProcessVolumeInput = [&](int y, int currentVolume, bool isBGM) -> int {
        int newVolume = currentVolume;
        int btnW = 50;
        int btnH = 50;
        
        // Minus button
        int minusX = startX;
        if (isLeftClicked && mouseX >= minusX && mouseX <= minusX + btnW && mouseY >= y && mouseY <= y + btnH)
        {
            newVolume = currentVolume - 10;
            if (newVolume < 0) newVolume = 0;
            SoundManager::GetInstance()->PlaySE("SE_UI_CLICK");
            if (!isBGM) { SoundManager::GetInstance()->PlaySE("SE_HIT1"); }
        }

        // Plus button
        int plusX = startX + 150;
        if (isLeftClicked && mouseX >= plusX && mouseX <= plusX + btnW && mouseY >= y && mouseY <= y + btnH)
        {
            newVolume = currentVolume + 10;
            if (newVolume > 100) newVolume = 100;
            SoundManager::GetInstance()->PlaySE("SE_UI_CLICK");
            if (!isBGM) { SoundManager::GetInstance()->PlaySE("SE_HIT1"); }
        }
        
        return newVolume;
    };

    // BGM
    int oldBGM = SoundManager::GetInstance()->GetBGMVolume();
    int newBGM = ProcessVolumeInput(startY, oldBGM, true);
    if (newBGM != oldBGM) SoundManager::GetInstance()->SetBGMVolume(newBGM);

    // SE
    int oldSE = SoundManager::GetInstance()->GetSEVolume();
    int newSE = ProcessVolumeInput(startY + spacingY, oldSE, false);
    if (newSE != oldSE) SoundManager::GetInstance()->SetSEVolume(newSE);

    // Back Button
    int backBtnW = 200;
    int backBtnH = 60;
    int backBtnX = (Utility::kScreenWidth - backBtnW) / 2;
    int backBtnY = startY + spacingY * 2;

    if (isLeftClicked && mouseX >= backBtnX && mouseX <= backBtnX + backBtnW && mouseY >= backBtnY && mouseY <= backBtnY + backBtnH)
    {
        SoundManager::GetInstance()->PlaySE("SE_UI_CLICK");
        Master::sceneManager->SetNextScene(SceneManager::kSceneTitle);
    }

    bg_scroll_x_ += 1.0f * Utility::time_scale_;
    if (bg_scroll_x_ >= Utility::kScreenWidth)
    {
        bg_scroll_x_ -= Utility::kScreenWidth;
    }

    Scene::Update();
}

void ConfigScene::DrawVolumeUI(int x, int y, const char* label, int volume)
{
    DrawStringToHandle(x - 200, y + 10, label, GetColor(255, 255, 255), font_handle_);
    
    int btnW = 50;
    int btnH = 50;
    
    DrawBox(x, y, x + btnW, y + btnH, GetColor(100, 100, 100), TRUE);
    DrawBox(x, y, x + btnW, y + btnH, GetColor(255, 255, 255), FALSE);
    DrawStringToHandle(x + 15, y + 10, "-", GetColor(255, 255, 255), font_handle_);

    std::string volStr = std::to_string(volume);
    DrawStringToHandle(x + 75, y + 10, volStr.c_str(), GetColor(255, 255, 255), font_handle_);

    int plusX = x + 150;
    DrawBox(plusX, y, plusX + btnW, y + btnH, GetColor(100, 100, 100), TRUE);
    DrawBox(plusX, y, plusX + btnW, y + btnH, GetColor(255, 255, 255), FALSE);
    DrawStringToHandle(plusX + 10, y + 10, "+", GetColor(255, 255, 255), font_handle_);
}

void ConfigScene::Draw()
{
    DrawGraph(static_cast<int>(-bg_scroll_x_), 0, bg_graph_, FALSE);
    DrawGraph(static_cast<int>(-bg_scroll_x_) + Utility::kScreenWidth, 0, bg_graph_, FALSE);

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
    DrawBox(0, 0, Utility::kScreenWidth, Utility::kScreenHeight, GetColor(0, 0, 0), TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    DrawStringToHandle(Utility::kScreenWidth / 2 - 100, 50, "設定 (SETTINGS)", GetColor(255, 255, 255), font_handle_);

    int startY = Utility::kScreenHeight / 2 - 100;
    int spacingY = 120;
    int startX = Utility::kScreenWidth / 2;

    DrawVolumeUI(startX, startY, "BGM 音量", SoundManager::GetInstance()->GetBGMVolume());
    DrawVolumeUI(startX, startY + spacingY, "SE 音量", SoundManager::GetInstance()->GetSEVolume());

    int backBtnW = 200;
    int backBtnH = 60;
    int backBtnX = (Utility::kScreenWidth - backBtnW) / 2;
    int backBtnY = startY + spacingY * 2;
    DrawBox(backBtnX, backBtnY, backBtnX + backBtnW, backBtnY + backBtnH, GetColor(100, 100, 100), TRUE);
    DrawBox(backBtnX, backBtnY, backBtnX + backBtnW, backBtnY + backBtnH, GetColor(255, 255, 255), FALSE);
    DrawStringToHandle(backBtnX + 60, backBtnY + 15, "戻る", GetColor(255, 255, 255), font_handle_);
}

void ConfigScene::Finalize()
{
}
