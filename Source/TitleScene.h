#pragma once
#include "Scene.h"
#include <vector>

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

    int bg_graph_;
    float bg_scroll_x_;
    int ui_button_graph_;
    std::vector<int> rankings_;
};
