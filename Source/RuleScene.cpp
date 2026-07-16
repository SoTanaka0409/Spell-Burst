#include "RuleScene.h"
#include "ObjectManager.h"
#include "InputManager.h"
#include "Master.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "Utility.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include <algorithm>

void RuleScene::Initialize()
{
    rule_graphs_[0] = ResourceManager::GetInstance()->GetGraph("Resource/rule1.png");
    rule_graphs_[1] = ResourceManager::GetInstance()->GetGraph("Resource/rule2.png");
    rule_graphs_[2] = ResourceManager::GetInstance()->GetGraph("Resource/rule3.png");
    rule_graphs_[3] = ResourceManager::GetInstance()->GetGraph("Resource/rule4.png");
    rule_graphs_[4] = -1; // ・ｽ・ｽ・ｽ・ｽ・ｽI・ｽﾈス・ｽ・ｽ・ｽC・ｽh・ｽﾇ会ｿｽ・ｽﾉ費ｿｽ・ｽ・ｽ・ｽﾄゑｿｽ・ｽ轤ｩ・ｽ・ｽ・ｽﾟ枠・ｽ・ｽm・ｽﾛゑｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ
    rule_graphs_[5] = -1;
    current_slide_ = 0;
    SoundManager::GetInstance()->PlayBGM("Resource/BGM/MusMus-BGM-146.mp3");
}

void RuleScene::Update()
{
    static int prevMouseInput = 0;
    int currentMouseInput = GetMouseInput();
    bool isLeftClicked = (currentMouseInput & MOUSE_INPUT_LEFT) != 0 && (prevMouseInput & MOUSE_INPUT_LEFT) == 0;
    prevMouseInput = currentMouseInput;

    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);
    
    if (isLeftClicked)
    {
        // ・ｽv・ｽ・ｽ・ｽC・ｽ・ｽ・ｽ[・ｽ・ｽ・ｽ^・ｽC・ｽg・ｽ・ｽ・ｽﾖ戻る操・ｽ・ｽ・ｽs・ｽ・ｽ・ｽ・ｽ・ｽﾛの遷・ｽﾚ擾ｿｽ・ｽ・ｽ
        if (mouseX >= 600 && mouseX <= 700 && mouseY >= 840 && mouseY <= 890)
        {
            SoundManager::GetInstance()->PlaySE("Resource/se_click.wav");
            Master::sceneManager->SetNextScene(SceneManager::kSceneTitle);
            return;
        }
        
        // ・ｽ・ｽ・ｽﾌペ・ｽ[・ｽW・ｽﾖ進・ｽﾞ擾ｿｽ・ｽ・ｽ・ｽi・ｽﾅ終・ｽy・ｽ[・ｽW・ｽﾌ場合・ｽﾍタ・ｽC・ｽg・ｽ・ｽ・ｽﾖ戻ゑｿｽj
        if (mouseX >= 900 && mouseX <= 1000 && mouseY >= 840 && mouseY <= 890)
        {
            SoundManager::GetInstance()->PlaySE("Resource/se_click.wav");
            if (current_slide_ < 5)
            {
                current_slide_++;
            } else
            {
                Master::sceneManager->SetNextScene(SceneManager::kSceneTitle);
                return;
            }
        }
        
        // ・ｽO・ｽﾌペ・ｽ[・ｽW・ｽﾖ戻る処・ｽ・ｽ・ｽi・ｽﾅ擾ｿｽ・ｽﾌペ・ｽ[・ｽW・ｽﾅは厄ｿｽ・ｽ・ｽ・ｽj
        if (mouseX >= 750 && mouseX <= 850 && mouseY >= 840 && mouseY <= 890)
        {
            SoundManager::GetInstance()->PlaySE("Resource/se_click.wav");
            if (current_slide_ > 0)
            {
                current_slide_--;
            }
        }
    }
}

void RuleScene::Draw()
{
    DrawBox(0, 0, Utility::kScreenWidth, Utility::kScreenHeight, GetColor(0, 0, 0), TRUE);
    
    if (current_slide_ >= 0 && current_slide_ < 6 && rule_graphs_[current_slide_] != -1)
    {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
        int imgW = 1, imgH = 1;
        GetGraphSize(rule_graphs_[current_slide_], &imgW, &imgH);
        
        if (imgW > 0 && imgH > 0)
        {
            float maxWidth = 1400.0f;
            float maxHeight = 650.0f; // ・ｽ・ｽ・ｽ・ｽ鞫懶ｿｽ・ｽ・ｽ・ｽ・ｽ竄ｷ・ｽ・ｽ・ｽﾈゑｿｽ謔､・ｽ`・ｽ・ｽﾌ茨ｿｽ・ｽ蛯ｫ・ｽﾟに設抵ｿｽ
            float scaleX = maxWidth / imgW;
            float scaleY = maxHeight / imgH;
            float scale = ((scaleX < scaleY) ? scaleX : scaleY) * 0.95f;
            
            int drawW = (int)(imgW * scale);
            int drawH = (int)(imgH * scale);
            int drawX = (Utility::kScreenWidth - drawW) / 2;
            int drawY = 20 + (650 - drawH) / 2;
            
            DrawExtendGraph(drawX, drawY, drawX + drawW, drawY + drawH, rule_graphs_[current_slide_], FALSE);
        }
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
    
    int titleFont = ResourceManager::GetInstance()->GetFont(32, 4);
    int font24 = ResourceManager::GetInstance()->GetFont(24, 3);
    
    const char* titles[] =
    {
        "1. ・ｽL・ｽ・ｽ・ｽ・ｽ・ｽN・ｽ^・ｽ[・ｽﾌ選・ｽ・ｽ",
        "2. ・ｽ・ｽﾕ度・ｽﾌ選・ｽ・ｽ",
        "3. ・ｽG・ｽ・ｽ|・ｽ・ｽ・ｽﾄ・ｿｽ・ｽx・ｽ・ｽ・ｽ・ｽ繧ｰ・ｽﾄボ・ｽX・ｽ・ｽ|・ｽ・ｽ・ｽ・ｽ・ｽI",
        "4. UI・ｽﾌ撰ｿｽ・ｽ",
        "5. ・ｽo・ｽ・ｽ・ｽA・ｽﾌ使・ｽ・ｽ・ｽ・ｽ",
        "6. ・ｽ{・ｽX・ｽ・ｽ|・ｽ・ｽ・ｽ・ｽHP・ｽ・ｽ・ｽ怐I"
    };
    const char* descs1[] =
    {
        "・ｽ^・ｽC・ｽg・ｽ・ｽ・ｽ・ｽﾊゑｿｽ・ｽ・ｽGAME START・ｽ・ｽ・ｽ・ｽ・ｽ・ｽA・ｽﾂ撰ｿｽ・ｽL・ｽ・ｽ・ｽﾈシ・ｽF・ｽt・ｽ・ｽI・ｽﾚゑｿｽ・ｽB",
        "・ｽ・ｽ・ｽ・ｽ・ｽﾉゑｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽﾕ度・ｽ・ｽI・ｽﾚゑｿｽ・ｽBNORMAL, HARD, VERY HARD・ｽ・ｽ・ｽ・ｽ・ｽ驍ｼ・ｽB",
        "・ｽG・ｽ・ｽ|・ｽ・ｽ・ｽﾄ経・ｽ・ｽ・ｽl・ｽ・ｽﾒゑｿｽ・ｽ・ｽ・ｽI・ｽ{・ｽ・ｽﾍウ・ｽF・ｽ[・ｽu・ｽ・ｽ・ｽﾅ、",
        "・ｽ・ｽ・ｽ・ｽﾍ趣ｿｽ・ｽ・ｽ・ｽ・ｽHP・ｽ窿鯉ｿｽx・ｽ・ｽ・ｽA",
        "・ｽo・ｽ・ｽ・ｽA・ｽW・ｽJ・ｽ・ｽ・ｽﾉ敵・ｽﾌ弾・ｽ・ｽｯゑｿｽﾆ力ゑｿｽ・ｽ・ｽ・ｽﾜゑｿｽA",
        "・ｽ{・ｽX・ｽ・ｽ|・ｽ・ｽ・ｽ・ｽHP・ｽ・ｽ3・ｽ怩・ｽ・ｽ驍ｼ・ｽI"
    };
    const char* descs2[] =
    {
        "",
        "",
        "・ｽ・ｽ關費ｿｽ|・ｽ・ｽ・ｽﾆボ・ｽX・ｽ・ｽ・ｽo・ｽ驍ｼ・ｽI",
        "・ｽK・ｽE・ｽZ・ｽﾌゲ・ｽ[・ｽW・ｽ・ｽ・ｽ\・ｽ・ｽ・ｽ・ｽ・ｽ・ｽﾄゑｿｽ・ｽ驍ｼ・ｽI",
        "・ｽﾅ鯉ｿｽﾉ具ｿｽ・ｽﾍな費ｿｽ・ｽ・ｽ・ｽﾆゑｿｽ・ｽﾄ包ｿｽ・ｽo・ｽ・ｽ・ｽ驍ｼ・ｽI・ｽ・ｽ・ｽﾜゑｿｽ・ｽg・ｽ・ｽ・ｽ・ｽ・ｽI",
        "・ｽﾅ鯉ｿｽﾜで抵ｿｽ・ｽﾟゑｿｽ・ｽﾉ戦え・ｽI"
    };
    const char* descs3[] =
    {
        "・ｽ・ｽ・ｽ・ｽ・ｽ@・ｽﾌ抵ｿｽ・ｽS・ｽﾉゑｿｽ・ｽ髀ｬ・ｽ・ｽ・ｽﾈ鯉ｿｽ・ｽ・ｽﾊゑｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ阡ｻ・ｽ・ｽﾅゑｿｽ・ｽI",
        "",
        "",
        "",
        "",
        ""
    };
    
    DrawBox(300, 700, 1300, 830, GetColor(20, 20, 40), TRUE);
    DrawBox(300, 700, 1300, 830, GetColor(255, 255, 255), FALSE);
    
    if (current_slide_ >= 0 && current_slide_ < 6)
    {
        DrawStringToHandle(320, 710, titles[current_slide_], GetColor(255, 255, 0), titleFont);
        DrawStringToHandle(320, 755, descs1[current_slide_], GetColor(255, 255, 255), font24);
        DrawStringToHandle(320, 785, descs2[current_slide_], GetColor(255, 255, 255), font24);
        DrawStringToHandle(320, 815, descs3[current_slide_], GetColor(255, 100, 100), font24);
    }
    
    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);
    
    DrawNavigationButtons(mouseX, mouseY, font24);
    
    Scene::Draw();
}

void RuleScene::DrawNavigationButtons(int mouseX, int mouseY, int font24)
{
    bool hoverBack = (mouseX >= 600 && mouseX <= 700 && mouseY >= 840 && mouseY <= 890);
    DrawBox(600, 840, 700, 890, hoverBack ? GetColor(100, 100, 100) : GetColor(50, 50, 50), TRUE);
    DrawBox(600, 840, 700, 890, GetColor(255, 255, 255), FALSE);
    DrawStringToHandle(615, 855, "BACK", GetColor(255, 255, 255), font24);
    
    if (current_slide_ > 0)
    {
        bool hoverPrev = (mouseX >= 750 && mouseX <= 850 && mouseY >= 840 && mouseY <= 890);
        DrawBox(750, 840, 850, 890, hoverPrev ? GetColor(100, 100, 100) : GetColor(50, 50, 50), TRUE);
        DrawBox(750, 840, 850, 890, GetColor(255, 255, 255), FALSE);
        DrawStringToHandle(770, 855, "PREV", GetColor(255, 255, 255), font24);
    }
    
    bool hoverNext = (mouseX >= 900 && mouseX <= 1000 && mouseY >= 840 && mouseY <= 890);
    DrawBox(900, 840, 1000, 890, hoverNext ? GetColor(100, 150, 100) : GetColor(50, 100, 50), TRUE);
    DrawBox(900, 840, 1000, 890, GetColor(255, 255, 255), FALSE);
    if (current_slide_ < 5)
    {
        DrawStringToHandle(920, 855, "NEXT", GetColor(255, 255, 255), font24);
    } else
    {
        DrawStringToHandle(920, 855, "DONE", GetColor(255, 255, 255), font24);
    }
}

void RuleScene::Finalize()
{
}
