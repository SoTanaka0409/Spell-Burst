#pragma once
#include "Scene.h"

// ゲームのルールや操作方法をスライド形式で説明するシーン
class RuleScene : public Scene
{
public:
    void Initialize() override;

    void Update() override;

    void Draw() override;

    void Finalize() override;

private:
    void DrawRuleText(int titleFont, int font24);

    void DrawNavigationButtons(int mouseX, int mouseY, int font24);

    int rule_graphs_[6]; // 各ページのルール画像ハンドル
    int current_slide_;  // 現在表示中のページ番号
};