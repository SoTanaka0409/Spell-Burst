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

/// @brief 初期化処理を行う
void RuleScene::Initialize()
{
    rule_graphs_[0] = ResourceManager::GetInstance()->GetGraph("IMG_RULE_01");
    rule_graphs_[1] = ResourceManager::GetInstance()->GetGraph("IMG_RULE_02");
    rule_graphs_[2] = ResourceManager::GetInstance()->GetGraph("IMG_RULE_03");
    rule_graphs_[3] = ResourceManager::GetInstance()->GetGraph("IMG_RULE_04");
    rule_graphs_[4] = -1; // 画像がないページはテキスト説明のみで表示する
    rule_graphs_[5] = -1;
    current_slide_ = 0;
    SoundManager::GetInstance()->PlayBGM("BGM_146");
}

/// @brief 毎フレームの更新処理を行う
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
            SoundManager::GetInstance()->PlaySE("SE_UI_CLICK");
            Master::sceneManager->SetNextScene(SceneManager::kSceneTitle);
            return;
        }

        // 次のページへ進む。最終ページではタイトルへ戻る
        if (mouseX >= 900 && mouseX <= 1000 && mouseY >= 840 && mouseY <= 890)
        {
            SoundManager::GetInstance()->PlaySE("SE_UI_CLICK");
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
            SoundManager::GetInstance()->PlaySE("SE_UI_CLICK");
            if (current_slide_ > 0)
            {
                current_slide_--;
            }
        }
    }
}

/// @brief 描画処理を行う
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
        "1. キャラクター選択",
        "2. 難易度選択",
        "3. 敵を倒して成長しよう",
        "4. 画面表示の見方",
        "5. バリアの使い方",
        "6. ボス戦の流れ"
    };
    const char* descs1[] =
    {
        "ゲーム開始後、3人の中から操作キャラクターを選びます。",
        "ふつう、むずかしい、とてもむずかしいから難易度を選びます。",
        "敵を倒すと経験値が入り、一定数を倒すとボスが出現します。",
        "左上にプレイヤーの体力、レベル、チャージ量が表示されます。",
        "バリアを出すと、敵の弾を防いだり跳ね返したりできます。",
        "ボスの体力は複数段階あり、削り切るたびに次の段階へ進みます。"
    };
    const char* descs2[] =
    {
        "選択中のキャラクターは少し暗く表示されます。",
        "難しいほど敵の出現や攻撃が激しくなります。",
        "レベルが上がると攻撃が強化され、戦いやすくなります。",
        "右下にはボスの体力ゲージが表示されます。",
        "危ない場面ほど、タイミングよく使うことが大切です。",
        "最後の段階を倒すまで油断せずに戦いましょう。"
    };
    const char* descs3[] =
    {
        "",
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

/// @brief DrawNavigationButtons を実行する
/// @param mouseX mouseX の値
/// @param mouseY mouseY の値
/// @param font24 font24 の値
void RuleScene::DrawNavigationButtons(int mouseX, int mouseY, int font24)
{
    bool hoverBack = (mouseX >= 600 && mouseX <= 700 && mouseY >= 840 && mouseY <= 890);
    DrawBox(600, 840, 700, 890, hoverBack ? GetColor(100, 100, 100) : GetColor(50, 50, 50), TRUE);
    DrawBox(600, 840, 700, 890, GetColor(255, 255, 255), FALSE);
    DrawStringToHandle(620, 855, "戻る", GetColor(255, 255, 255), font24);

    if (current_slide_ > 0)
    {
        bool hoverPrev = (mouseX >= 750 && mouseX <= 850 && mouseY >= 840 && mouseY <= 890);
        DrawBox(750, 840, 850, 890, hoverPrev ? GetColor(100, 100, 100) : GetColor(50, 50, 50), TRUE);
        DrawBox(750, 840, 850, 890, GetColor(255, 255, 255), FALSE);
        DrawStringToHandle(775, 855, "前へ", GetColor(255, 255, 255), font24);
    }

    bool hoverNext = (mouseX >= 900 && mouseX <= 1000 && mouseY >= 840 && mouseY <= 890);
    DrawBox(900, 840, 1000, 890, hoverNext ? GetColor(100, 150, 100) : GetColor(50, 100, 50), TRUE);
    DrawBox(900, 840, 1000, 890, GetColor(255, 255, 255), FALSE);
    if (current_slide_ < 5)
    {
        DrawStringToHandle(925, 855, "次へ", GetColor(255, 255, 255), font24);
    } else
    {
        DrawStringToHandle(925, 855, "完了", GetColor(255, 255, 255), font24);
    }
}

/// @brief 終了処理を行う
void RuleScene::Finalize()
{
}
