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
    rule_graphs_[4] = -1; // 画像がないページはテキスト説明のみで表示する
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
        // タイトルへ戻る
        if (mouseX >= 600 && mouseX <= 700 && mouseY >= 840 && mouseY <= 890)
        {
            SoundManager::GetInstance()->PlaySE("Resource/se_click.wav");
            Master::sceneManager->SetNextScene(SceneManager::kSceneTitle);
            return;
        }

        // 次のページへ進む。最終ページではタイトルへ戻る
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

        // 前のページへ戻る。最初のページでは何もしない
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
            float maxHeight = 650.0f; // 画像が説明欄に重ならないよう高さを制限する
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
        "1. Choose Character",
        "2. Choose Difficulty",
        "3. Defeat enemies, level up, and beat the boss!",
        "4. UI Guide",
        "5. Barrier Guide",
        "6. Boss HP has 3 phases!"
    };
    const char* descs1[] =
    {
        "After GAME START, choose one of three characters.",
        "Pick NORMAL, HARD, or VERY HARD to match your skill.",
        "Defeat waves of enemies to gain XP. A boss appears at the end.",
        "Your HP and level are shown at the upper left.",
        "Deploy the barrier to reflect enemy bullets.",
        "The boss restores HP across multiple phases."
    };
    const char* descs2[] =
    {
        "",
        "",
        "Leveling up increases attack power and unlocks stronger shots.",
        "The boss HP gauge is shown at the lower right.",
        "Use the barrier at the right moment to escape danger.",
        "Stay focused until the final phase is defeated."
    };
    const char* descs3[] =
    {
        "The currently selected character is shown slightly darker.",
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
