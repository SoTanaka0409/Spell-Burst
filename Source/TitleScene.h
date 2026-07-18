#pragma once
#include "Scene.h"
#include <vector>

// タイトル画面とランキング表示を管理するシーン
class TitleScene : public Scene
{
public:
    TitleScene();
    ~TitleScene();

    void Initialize() override;

    void Update() override;

    void Draw() override;

    void Finalize() override;

private:
    void DrawRankings();

    void DrawTitleLogo();

    void DrawButtons(int mouseX, int mouseY);

private:
    int bg_graph_;              // 背景画像ハンドル
    float bg_scroll_x_;         // 背景スクロール位置
    int ui_button_graph_;       // ボタン画像ハンドル
    std::vector<int> rankings_; // 読み込んだランキング記録
};