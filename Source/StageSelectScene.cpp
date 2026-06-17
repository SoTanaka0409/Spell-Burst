#include "StageSelectScene.h"
#include "InputManager.h"
#include "Master.h"
#include "GameScene.h"
#include "Player.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "Utility.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include <cstring>

void StageSelectScene::Initialize()
{
    m_phase = 0;
    m_uiButtonGraph = ResourceManager::GetInstance()->GetGraph("Resource/ui_button.png");
    m_WaitCount = 0;
    SoundManager::GetInstance()->PlayBGM("Resource/bgm_select.mp3");
}

void StageSelectScene::Update() 
{
    m_WaitCount++;
    if (m_WaitCount < 60)
    {
        return;
    }
    static int prevMouseInput = 0;
    int currentMouseInput = GetMouseInput();
    bool isLeftClicked = (currentMouseInput & MOUSE_INPUT_LEFT) != 0 && (prevMouseInput & MOUSE_INPUT_LEFT) == 0;
    prevMouseInput = currentMouseInput;

    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);
    
    // Back button
    if (isLeftClicked && mouseX >= 20 && mouseX <= 120 && mouseY >= 20 && mouseY <= 60) {
        SoundManager::GetInstance()->PlaySE("Resource/SE/決定ボタンを押す42.mp3");
        if (m_phase == 1) {
            m_phase = 0;
        } else {
            Master::sceneManager->SetNextScene(SceneManager::SCENE_TITLE);
        }
        return;
    }
    
    int cx = Utility::SCREEN_WIDTH / 2;
    int cy = Utility::SCREEN_HEIGHT / 2;
    
    if (m_phase == 0) {
        int gap = 200;
        int charW = 120;
        int charH = 120;
        int charY = cy - 50;
        int char1X = cx - gap - charW / 2;
        int char2X = cx - charW / 2;
        int char3X = cx + gap - charW / 2;
        
        if (isLeftClicked) {
            if (mouseX >= char1X && mouseX <= char1X + charW && mouseY >= charY && mouseY <= charY + charH) {
                SoundManager::GetInstance()->PlaySE("Resource/SE/決定ボタンを押す42.mp3");
                Player::s_selectedCharacterType = 1;
                m_phase = 1;
            } else if (mouseX >= char2X && mouseX <= char2X + charW && mouseY >= charY && mouseY <= charY + charH) {
                SoundManager::GetInstance()->PlaySE("Resource/SE/決定ボタンを押す42.mp3");
                Player::s_selectedCharacterType = 2;
                m_phase = 1;
            } else if (mouseX >= char3X && mouseX <= char3X + charW && mouseY >= charY && mouseY <= charY + charH) {
                SoundManager::GetInstance()->PlaySE("Resource/SE/決定ボタンを押す42.mp3");
                Player::s_selectedCharacterType = 3;
                m_phase = 1;
            }
        }
    } else if (m_phase == 1) {
        int btnW = 300;
        int btnH = 80;
        int btnX = cx - btnW / 2;
        int btnY1 = cy - 100;
        int btnY2 = btnY1 + 100;
        int btnY3 = btnY2 + 100;
        
        if (isLeftClicked) {
            if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= btnY1 && mouseY <= btnY1 + btnH) {
                SoundManager::GetInstance()->PlaySE("Resource/SE/決定ボタンを押す42.mp3");
                GameScene::s_currentStage = 1;
                Master::sceneManager->SetNextScene(SceneManager::SCENE_GAME);
            } else if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= btnY2 && mouseY <= btnY2 + btnH) {
                SoundManager::GetInstance()->PlaySE("Resource/SE/決定ボタンを押す42.mp3");
                GameScene::s_currentStage = 2;
                Master::sceneManager->SetNextScene(SceneManager::SCENE_GAME);
            } else if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= btnY3 && mouseY <= btnY3 + btnH) {
                SoundManager::GetInstance()->PlaySE("Resource/SE/決定ボタンを押す42.mp3");
                GameScene::s_currentStage = 3;
                Master::sceneManager->SetNextScene(SceneManager::SCENE_GAME);
            }
            m_WaitCount = 0;
        }
    }
}

void StageSelectScene::Draw() {
    DrawBox(0, 0, Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT, GetColor(20, 25, 40), TRUE);
    Scene::Draw();
    
    int titleFont = ResourceManager::GetInstance()->GetFont(48, 5);
    int subFont = ResourceManager::GetInstance()->GetFont(32, 4);
    int font24 = ResourceManager::GetInstance()->GetFont(24, 3);
    
    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);
    
    auto drawBtn = [&](int x, int y, int w, int h, const char* text, bool hover, int color) {
        if (m_uiButtonGraph != -1) {
            if (hover) {
                SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
                DrawExtendGraph(x, y, x + w, y + h, m_uiButtonGraph, TRUE);
                SetDrawBlendMode(DX_BLENDMODE_ADD, 100);
                DrawBox(x, y, x + w, y + h, color, TRUE);
                SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
            } else {
                SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
                DrawExtendGraph(x, y, x + w, y + h, m_uiButtonGraph, TRUE);
                SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
            }
        } else {
            DrawBox(x, y, x + w, y + h, hover ? color : GetColor(50, 50, 50), TRUE);
            DrawBox(x, y, x + w, y + h, GetColor(255, 255, 255), FALSE);
        }
        
        if (text) {
            int tw = GetDrawStringWidthToHandle(text, (int)strlen(text), font24);
            DrawStringToHandle(x + (w - tw) / 2, y + (h - 24) / 2, text, GetColor(255, 255, 255), font24);
        }
    };
    
    // 誤操作を防ぐため、画面左上に明確な「戻る」ボタンを配置してホバー判定
    bool hoverBack = (mouseX >= 20 && mouseX <= 120 && mouseY >= 20 && mouseY <= 60);
    drawBtn(20, 20, 100, 40, "BACK", hoverBack, GetColor(150, 150, 150));
    
    int cx = Utility::SCREEN_WIDTH / 2;
    int cy = Utility::SCREEN_HEIGHT / 2;
    
    if (m_phase == 0) {
        const char* titleTxt = "- SELECT YOUR CHARACTER -";
        int tw = GetDrawStringWidthToHandle(titleTxt, (int)strlen(titleTxt), subFont);
        DrawStringToHandle((Utility::SCREEN_WIDTH - tw) / 2, cy - 150, titleTxt, GetColor(200, 200, 200), subFont);
        
        int tex1 = ResourceManager::GetInstance()->GetGraph("Resource/player.png");
        int tex2 = ResourceManager::GetInstance()->GetGraph("Resource/player2.png");
        int tex3 = ResourceManager::GetInstance()->GetGraph("Resource/player3.png");
        
        int gap = 200;
        int charW = 120;
        int charH = 120;
        int charY = cy - 50;
        int char1X = cx - gap - charW / 2;
        int char2X = cx - charW / 2;
        int char3X = cx + gap - charW / 2;
        
        // プレイヤー1（ノーマルシェフ）の選択状態およびホバー演出を描画
        bool hover1 = (mouseX >= char1X && mouseX <= char1X + charW && mouseY >= charY && mouseY <= charY + charH);
        drawBtn(char1X, charY, charW, charH, nullptr, hover1, GetColor(100, 100, 255));
        int s1 = hover1 ? 55 : 45;
        DrawExtendGraph(char1X + charW/2 - s1, charY + charH/2 - s1, char1X + charW/2 + s1, charY + charH/2 + s1, tex1, TRUE);
        int cw1 = GetDrawStringWidthToHandle("NORMAL CHEF", 11, font24);
        DrawStringToHandle(char1X + (charW - cw1) / 2, charY + charH + 10, "NORMAL CHEF", GetColor(200, 200, 255), font24);
        if (hover1) DrawStringToHandle(char1X - 10, charY + charH + 40, "MASTER SPARK", GetColor(255, 255, 0), font24);
        
        // プレイヤー2（ガールシェフ）の選択状態およびホバー演出を描画
        bool hover2 = (mouseX >= char2X && mouseX <= char2X + charW && mouseY >= charY && mouseY <= charY + charH);
        drawBtn(char2X, charY, charW, charH, nullptr, hover2, GetColor(255, 100, 100));
        int s2 = hover2 ? 55 : 45;
        DrawExtendGraph(char2X + charW/2 - s2, charY + charH/2 - s2, char2X + charW/2 + s2, charY + charH/2 + s2, tex2, TRUE);
        int cw2 = GetDrawStringWidthToHandle("GIRL CHEF", 9, font24);
        DrawStringToHandle(char2X + (charW - cw2) / 2, charY + charH + 10, "GIRL CHEF", GetColor(255, 200, 200), font24);
        if (hover2) DrawStringToHandle(char2X - 10, charY + charH + 40, "RAINBOW WAVE", GetColor(255, 255, 0), font24);
        
        // プレイヤー3（オールドシェフ）の選択状態およびホバー演出を描画
        bool hover3 = (mouseX >= char3X && mouseX <= char3X + charW && mouseY >= charY && mouseY <= charY + charH);
        drawBtn(char3X, charY, charW, charH, nullptr, hover3, GetColor(100, 255, 100));
        int s3 = hover3 ? 55 : 45;
        DrawExtendGraph(char3X + charW/2 - s3, charY + charH/2 - s3, char3X + charW/2 + s3, charY + charH/2 + s3, tex3, TRUE);
        int cw3 = GetDrawStringWidthToHandle("OLD CHEF", 8, font24);
        DrawStringToHandle(char3X + (charW - cw3) / 2, charY + charH + 10, "OLD CHEF", GetColor(200, 255, 200), font24);
        if (hover3) DrawStringToHandle(char3X - 20, charY + charH + 40, "CHERRY BLOSSOM", GetColor(255, 255, 0), font24);
        
    } else if (m_phase == 1) {
        const char* titleTxt = "- SELECT STAGE LEVEL -";
        int tw = GetDrawStringWidthToHandle(titleTxt, (int)strlen(titleTxt), titleFont);
        DrawStringToHandle((Utility::SCREEN_WIDTH - tw) / 2, cy - 200, titleTxt, GetColor(255, 255, 255), titleFont);
        
        int btnW = 300;
        int btnH = 80;
        int btnX = cx - btnW / 2;
        int btnY1 = cy - 100;
        int btnY2 = btnY1 + 100;
        int btnY3 = btnY2 + 100;
        
        bool hover1 = (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= btnY1 && mouseY <= btnY1 + btnH);
        drawBtn(btnX, btnY1, btnW, btnH, "STAGE 1 : NORMAL", hover1, GetColor(150, 255, 150));
        
        bool hover2 = (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= btnY2 && mouseY <= btnY2 + btnH);
        drawBtn(btnX, btnY2, btnW, btnH, "STAGE 2 : HARD", hover2, GetColor(255, 200, 100));
        
        bool hover3 = (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= btnY3 && mouseY <= btnY3 + btnH);
        drawBtn(btnX, btnY3, btnW, btnH, "STAGE 3 : VERY HARD", hover3, GetColor(255, 100, 100));
    }
}

void StageSelectScene::Finalize() {
}
