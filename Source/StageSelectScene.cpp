#include "StageSelectScene.h"
#include "InputManager.h"
#include "Master.h"
#include "GameScene.h"
#include "Player.h"
#include "ResourceManager.h"
#include <DxLib.h>

void StageSelectScene::Initialize()
{
    m_phase = 0;
}

void StageSelectScene::Update() {
    static int prevMouseInput = 0;
    int currentMouseInput = GetMouseInput();
    bool isLeftClicked = (currentMouseInput & MOUSE_INPUT_LEFT) != 0 && (prevMouseInput & MOUSE_INPUT_LEFT) == 0;
    prevMouseInput = currentMouseInput;

    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);
    
    // Back button
    if (isLeftClicked && mouseX >= 20 && mouseX <= 120 && mouseY >= 20 && mouseY <= 60) {
        if (m_phase == 1) {
            m_phase = 0;
        } else {
            Master::sceneManager->SetNextScene(SceneManager::SCENE_TITLE);
        }
        return;
    }
    
    if (m_phase == 0) {
        if (isLeftClicked) {
            if (mouseX >= 150 && mouseX <= 250 && mouseY >= 250 && mouseY <= 350) {
                Player::s_selectedCharacterType = 1;
                m_phase = 1;
            } else if (mouseX >= 350 && mouseX <= 450 && mouseY >= 250 && mouseY <= 350) {
                Player::s_selectedCharacterType = 2;
                m_phase = 1;
            } else if (mouseX >= 550 && mouseX <= 650 && mouseY >= 250 && mouseY <= 350) {
                Player::s_selectedCharacterType = 3;
                m_phase = 1;
            }
        }
    } else if (m_phase == 1) {
        if (isLeftClicked) {
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
        }
    }
}

void StageSelectScene::Draw() {
    DrawBox(0, 0, 800, 600, GetColor(20, 25, 40), TRUE);
    Scene::Draw();
    
    int titleFont = ResourceManager::GetInstance()->GetFont(48, 5);
    int subFont = ResourceManager::GetInstance()->GetFont(32, 4);
    
    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);
    
    // Draw Back button
    bool hoverBack = (mouseX >= 20 && mouseX <= 120 && mouseY >= 20 && mouseY <= 60);
    DrawBox(20, 20, 120, 60, hoverBack ? GetColor(100, 100, 100) : GetColor(50, 50, 50), TRUE);
    DrawBox(20, 20, 120, 60, GetColor(255, 255, 255), FALSE);
    int font24 = ResourceManager::GetInstance()->GetFont(24, 3);
    DrawStringToHandle(35, 30, "BACK", GetColor(255, 255, 255), font24);
    
    if (m_phase == 0) {
        DrawStringToHandle(120, 150, "- SELECT YOUR CHARACTER -", GetColor(200, 200, 200), subFont);
        
        int tex1 = ResourceManager::GetInstance()->GetGraph("Resource/player.png");
        int tex2 = ResourceManager::GetInstance()->GetGraph("Resource/player2.png");
        int tex3 = ResourceManager::GetInstance()->GetGraph("Resource/player3.png");
        
        // Draw Char 1
        bool hover1 = (mouseX >= 150 && mouseX <= 250 && mouseY >= 250 && mouseY <= 350);
        int s1 = hover1 ? 60 : 45;
        if (hover1) {
            DrawBox(140, 240, 260, 360, GetColor(50, 50, 100), TRUE);
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
            DrawBox(140, 240, 260, 360, GetColor(255, 255, 100), TRUE);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        }
        DrawBox(140, 240, 260, 360, GetColor(200, 200, 255), FALSE);
        DrawExtendGraph(200 - s1, 300 - s1, 200 + s1, 300 + s1, tex1, TRUE);
        DrawStringToHandle(145, 380, "NORMAL CHEF", GetColor(200, 200, 255), subFont);
        if (hover1) DrawString(155, 410, "MASTER SPARK", GetColor(255, 255, 0));
        
        // Draw Char 2
        bool hover2 = (mouseX >= 350 && mouseX <= 450 && mouseY >= 250 && mouseY <= 350);
        int s2 = hover2 ? 60 : 45;
        if (hover2) {
            DrawBox(340, 240, 460, 360, GetColor(100, 50, 50), TRUE);
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
            DrawBox(340, 240, 460, 360, GetColor(255, 150, 150), TRUE);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        }
        DrawBox(340, 240, 460, 360, GetColor(255, 200, 200), FALSE);
        DrawExtendGraph(400 - s2, 300 - s2, 400 + s2, 300 + s2, tex2, TRUE);
        DrawStringToHandle(355, 380, "GIRL CHEF", GetColor(255, 200, 200), subFont);
        if (hover2) DrawString(355, 410, "RAINBOW WAVE", GetColor(255, 255, 0));
        
        // Draw Char 3
        bool hover3 = (mouseX >= 550 && mouseX <= 650 && mouseY >= 250 && mouseY <= 350);
        int s3 = hover3 ? 60 : 45;
        if (hover3) {
            DrawBox(540, 240, 660, 360, GetColor(50, 100, 50), TRUE);
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
            DrawBox(540, 240, 660, 360, GetColor(150, 255, 150), TRUE);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        }
        DrawBox(540, 240, 660, 360, GetColor(200, 255, 200), FALSE);
        DrawExtendGraph(600 - s3, 300 - s3, 600 + s3, 300 + s3, tex3, TRUE);
        DrawStringToHandle(560, 380, "OLD CHEF", GetColor(200, 255, 200), subFont);
        if (hover3) DrawString(545, 410, "CHERRY BLOSSOM", GetColor(255, 255, 0));
        
    } else if (m_phase == 1) {
        int stageFont = ResourceManager::GetInstance()->GetFont(32, 4);
        DrawStringToHandle(180, 50, "- SELECT STAGE LEVEL -", GetColor(255, 255, 255), titleFont);
        
        // Stage 1 (NORMAL)
        bool hover1 = (mouseX >= 250 && mouseX <= 550 && mouseY >= 150 && mouseY <= 250);
        int c1 = hover1 ? GetColor(150, 255, 150) : GetColor(50, 150, 50);
        DrawBox(250, 150, 550, 250, c1, TRUE);
        DrawBox(250, 150, 550, 250, GetColor(255, 255, 255), FALSE);
        DrawStringToHandle(270, 185, "STAGE 1 : NORMAL", GetColor(0, 0, 0), stageFont);
        
        // Stage 2 (HARD)
        bool hover2 = (mouseX >= 250 && mouseX <= 550 && mouseY >= 280 && mouseY <= 380);
        int c2 = hover2 ? GetColor(255, 200, 100) : GetColor(200, 100, 20);
        DrawBox(250, 280, 550, 380, c2, TRUE);
        DrawBox(250, 280, 550, 380, GetColor(255, 255, 255), FALSE);
        DrawStringToHandle(270, 315, "STAGE 2 : HARD", GetColor(0, 0, 0), stageFont);
        
        // Stage 3 (VERY HARD)
        bool hover3 = (mouseX >= 250 && mouseX <= 550 && mouseY >= 410 && mouseY <= 510);
        int c3 = hover3 ? GetColor(255, 100, 100) : GetColor(180, 30, 30);
        DrawBox(250, 410, 550, 510, c3, TRUE);
        DrawBox(250, 410, 550, 510, GetColor(255, 255, 255), FALSE);
        DrawStringToHandle(270, 445, "STAGE 3 : VERY HARD", GetColor(255, 255, 255), stageFont);
    }
}

void StageSelectScene::Finalize() {
}
