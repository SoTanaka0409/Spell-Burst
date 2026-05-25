#include "RuleScene.h"
#include "InputManager.h"
#include "Master.h"
#include "ResourceManager.h"
#include "Utility.h"
#include <DxLib.h>
#include <algorithm>

void RuleScene::Initialize() {
    m_ruleGraphs[0] = ResourceManager::GetInstance()->GetGraph("Resource/rule1.png");
    m_ruleGraphs[1] = ResourceManager::GetInstance()->GetGraph("Resource/rule2.png");
    m_ruleGraphs[2] = ResourceManager::GetInstance()->GetGraph("Resource/rule3.png");
    m_ruleGraphs[3] = ResourceManager::GetInstance()->GetGraph("Resource/rule4.png");
    m_currentSlide = 0;
}

void RuleScene::Update() {
    static int prevMouseInput = 0;
    int currentMouseInput = GetMouseInput();
    bool isLeftClicked = (currentMouseInput & MOUSE_INPUT_LEFT) != 0 && (prevMouseInput & MOUSE_INPUT_LEFT) == 0;
    prevMouseInput = currentMouseInput;

    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);
    
    if (isLeftClicked) {
        // Back Button
        if (mouseX >= 20 && mouseX <= 120 && mouseY >= 20 && mouseY <= 60) {
            Master::sceneManager->SetNextScene(SceneManager::SCENE_TITLE);
            return;
        }
        
        // Next Button
        if (mouseX >= 650 && mouseX <= 750 && mouseY >= 500 && mouseY <= 550) {
            if (m_currentSlide < 3) {
                m_currentSlide++;
            } else {
                Master::sceneManager->SetNextScene(SceneManager::SCENE_TITLE);
                return;
            }
        }
        
        // Prev Button
        if (mouseX >= 50 && mouseX <= 150 && mouseY >= 500 && mouseY <= 550) {
            if (m_currentSlide > 0) {
                m_currentSlide--;
            }
        }
    }
}

void RuleScene::Draw() {
    DrawBox(0, 0, Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT, GetColor(0, 0, 0), TRUE);
    
    if (m_currentSlide >= 0 && m_currentSlide < 4 && m_ruleGraphs[m_currentSlide] != -1) {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
        int imgW = 1, imgH = 1;
        GetGraphSize(m_ruleGraphs[m_currentSlide], &imgW, &imgH);
        
        if (imgW > 0 && imgH > 0) {
            float scaleX = (float)Utility::SCREEN_WIDTH / imgW;
            float scaleY = (float)Utility::SCREEN_HEIGHT / imgH;
            float scale = (scaleX < scaleY) ? scaleX : scaleY;
            
            int drawW = (int)(imgW * scale);
            int drawH = (int)(imgH * scale);
            int drawX = (Utility::SCREEN_WIDTH - drawW) / 2;
            int drawY = (Utility::SCREEN_HEIGHT - drawH) / 2;
            
            DrawExtendGraph(drawX, drawY, drawX + drawW, drawY + drawH, m_ruleGraphs[m_currentSlide], FALSE);
        }
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
    
    int titleFont = ResourceManager::GetInstance()->GetFont(32, 4);
    int font24 = ResourceManager::GetInstance()->GetFont(24, 3);
    
    const char* titles[] = {
        "1. キャラクターの選択",
        "2. 難易度の選択",
        "3. 敵を倒してレベルを上げてボスを倒そう！",
        "4. 必殺技やバリアをうまく使って立ち回ろう！"
    };
    const char* descs[] = {
        "タイトル画面からGAME STARTを押し、個性豊かなシェフを選ぼう。",
        "自分にあった難易度を選ぼう。NORMAL, HARD, VERY HARDがあるぞ。",
        "敵を倒して経験値を稼ぎ、最後に待ち受けるボスを撃破しよう！",
        "必殺技やバリアを駆使して、敵の激しい弾幕を生き抜こう！"
    };
    
    DrawBox(20, 80, 780, 200, GetColor(20, 20, 40), TRUE);
    DrawBox(20, 80, 780, 200, GetColor(255, 255, 255), FALSE);
    
    if (m_currentSlide >= 0 && m_currentSlide < 4) {
        DrawStringToHandle(40, 100, titles[m_currentSlide], GetColor(255, 255, 0), titleFont);
        DrawStringToHandle(40, 150, descs[m_currentSlide], GetColor(255, 255, 255), font24);
    }
    
    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);
    
    // Draw Back button
    bool hoverBack = (mouseX >= 20 && mouseX <= 120 && mouseY >= 20 && mouseY <= 60);
    DrawBox(20, 20, 120, 60, hoverBack ? GetColor(100, 100, 100) : GetColor(50, 50, 50), TRUE);
    DrawBox(20, 20, 120, 60, GetColor(255, 255, 255), FALSE);
    DrawStringToHandle(35, 30, "BACK", GetColor(255, 255, 255), font24);
    
    // Draw Prev button
    if (m_currentSlide > 0) {
        bool hoverPrev = (mouseX >= 50 && mouseX <= 150 && mouseY >= 500 && mouseY <= 550);
        DrawBox(50, 500, 150, 550, hoverPrev ? GetColor(100, 100, 100) : GetColor(50, 50, 50), TRUE);
        DrawBox(50, 500, 150, 550, GetColor(255, 255, 255), FALSE);
        DrawStringToHandle(65, 515, "PREV", GetColor(255, 255, 255), font24);
    }
    
    // Draw Next button
    bool hoverNext = (mouseX >= 650 && mouseX <= 750 && mouseY >= 500 && mouseY <= 550);
    DrawBox(650, 500, 750, 550, hoverNext ? GetColor(100, 150, 100) : GetColor(50, 100, 50), TRUE);
    DrawBox(650, 500, 750, 550, GetColor(255, 255, 255), FALSE);
    if (m_currentSlide < 3) {
        DrawStringToHandle(665, 515, "NEXT", GetColor(255, 255, 255), font24);
    } else {
        DrawStringToHandle(665, 515, "DONE", GetColor(255, 255, 255), font24);
    }
    
    Scene::Draw();
}

void RuleScene::Finalize() {
}
