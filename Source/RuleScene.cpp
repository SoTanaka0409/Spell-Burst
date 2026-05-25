#include "RuleScene.h"
#include "InputManager.h"
#include "Master.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "Utility.h"
#include <DxLib.h>
#include <algorithm>

void RuleScene::Initialize() {
    m_ruleGraphs[0] = ResourceManager::GetInstance()->GetGraph("Resource/rule1.png");
    m_ruleGraphs[1] = ResourceManager::GetInstance()->GetGraph("Resource/rule2.png");
    m_ruleGraphs[2] = ResourceManager::GetInstance()->GetGraph("Resource/rule3.png");
    m_ruleGraphs[3] = ResourceManager::GetInstance()->GetGraph("Resource/rule4.png");
    m_ruleGraphs[4] = -1; // Or load new images if available
    m_ruleGraphs[5] = -1;
    m_currentSlide = 0;
    SoundManager::GetInstance()->PlayBGM("Resource/BGM/MusMus-BGM-146.mp3");
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
        if (mouseX >= 20 && mouseX <= 120 && mouseY >= 530 && mouseY <= 580) {
            SoundManager::GetInstance()->PlaySE("Resource/se_click.wav");
            Master::sceneManager->SetNextScene(SceneManager::SCENE_TITLE);
            return;
        }
        
        // Next Button
        if (mouseX >= 650 && mouseX <= 750 && mouseY >= 530 && mouseY <= 580) {
            SoundManager::GetInstance()->PlaySE("Resource/se_click.wav");
            if (m_currentSlide < 5) {
                m_currentSlide++;
            } else {
                Master::sceneManager->SetNextScene(SceneManager::SCENE_TITLE);
                return;
            }
        }
        
        // Prev Button
        if (mouseX >= 150 && mouseX <= 250 && mouseY >= 530 && mouseY <= 580) {
            SoundManager::GetInstance()->PlaySE("Resource/se_click.wav");
            if (m_currentSlide > 0) {
                m_currentSlide--;
            }
        }
    }
}

void RuleScene::Draw() {
    DrawBox(0, 0, Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT, GetColor(0, 0, 0), TRUE);
    
    if (m_currentSlide >= 0 && m_currentSlide < 6 && m_ruleGraphs[m_currentSlide] != -1) {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
        int imgW = 1, imgH = 1;
        GetGraphSize(m_ruleGraphs[m_currentSlide], &imgW, &imgH);
        
        if (imgW > 0 && imgH > 0) {
            float maxWidth = 760.0f;
            float maxHeight = 400.0f; // Keep it between Y=120 and Y=520
            float scaleX = maxWidth / imgW;
            float scaleY = maxHeight / imgH;
            float scale = ((scaleX < scaleY) ? scaleX : scaleY) * 0.95f;
            
            int drawW = (int)(imgW * scale);
            int drawH = (int)(imgH * scale);
            int drawX = (Utility::SCREEN_WIDTH - drawW) / 2;
            int drawY = 120 + (400 - drawH) / 2;
            
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
        "4. UIの説明",
        "5. バリアの使い方",
        "6. ボスを倒すとHPが回復！"
    };
    const char* descs1[] = {
        "タイトル画面からGAME STARTを押し、個性豊かなシェフを選ぼう。",
        "自分にあった難易度を選ぼう。NORMAL, HARD, VERY HARDがあるぞ。",
        "敵を倒して経験値を稼ごう！本作はウェーブ制で、",
        "左上は自分のHPやレベル、",
        "バリア展開中に敵の弾を受けると力が溜まり、",
        "ボスを倒すとHPが3回復するぞ！"
    };
    const char* descs2[] = {
        "",
        "",
        "一定数倒すとボスが出現するぞ！",
        "下のゲージは必殺技のチャージ量だ！",
        "最後に溜め攻撃として放出するぞ！うまく活用しよう！",
        "最後まであきらめずに戦い抜こう！"
    };
    
    DrawBox(20, 20, 800, 130, GetColor(20, 20, 40), TRUE);
    DrawBox(20, 20, 800, 130, GetColor(255, 255, 255), FALSE);
    
    if (m_currentSlide >= 0 && m_currentSlide < 6) {
        DrawStringToHandle(40, 30, titles[m_currentSlide], GetColor(255, 255, 0), titleFont);
        DrawStringToHandle(40, 65, descs1[m_currentSlide], GetColor(255, 255, 255), font24);
        DrawStringToHandle(40, 90, descs2[m_currentSlide], GetColor(255, 255, 255), font24);
    }
    
    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);
    
    // Draw Back button
    bool hoverBack = (mouseX >= 20 && mouseX <= 120 && mouseY >= 530 && mouseY <= 580);
    DrawBox(20, 530, 120, 580, hoverBack ? GetColor(100, 100, 100) : GetColor(50, 50, 50), TRUE);
    DrawBox(20, 530, 120, 580, GetColor(255, 255, 255), FALSE);
    DrawStringToHandle(40, 545, "BACK", GetColor(255, 255, 255), font24);
    
    // Draw Prev button
    if (m_currentSlide > 0) {
        bool hoverPrev = (mouseX >= 150 && mouseX <= 250 && mouseY >= 530 && mouseY <= 580);
        DrawBox(150, 530, 250, 580, hoverPrev ? GetColor(100, 100, 100) : GetColor(50, 50, 50), TRUE);
        DrawBox(150, 530, 250, 580, GetColor(255, 255, 255), FALSE);
        DrawStringToHandle(170, 545, "PREV", GetColor(255, 255, 255), font24);
    }
    
    // Draw Next button
    bool hoverNext = (mouseX >= 650 && mouseX <= 750 && mouseY >= 530 && mouseY <= 580);
    DrawBox(650, 530, 750, 580, hoverNext ? GetColor(100, 150, 100) : GetColor(50, 100, 50), TRUE);
    DrawBox(650, 530, 750, 580, GetColor(255, 255, 255), FALSE);
    if (m_currentSlide < 5) {
        DrawStringToHandle(675, 545, "NEXT", GetColor(255, 255, 255), font24);
    } else {
        DrawStringToHandle(675, 545, "DONE", GetColor(255, 255, 255), font24);
    }
    
    Scene::Draw();
}

void RuleScene::Finalize() {
}
