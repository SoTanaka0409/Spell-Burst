#pragma once
#include "Scene.h"

class StageSelectScene : public Scene
{
public:
    /*
     */
    void Initialize() override;
    /*
     */
    void Update() override;
    /*
     */
    void Draw() override;
    /*
     */
    void Finalize() override;

private:
    void UpdateCharacterSelect(int mouseX, int mouseY, bool isLeftClicked, int cx, int cy);
    void UpdateStageSelect(int mouseX, int mouseY, bool isLeftClicked, int cx, int cy);

    void DrawCharacterSelect(int cx, int cy, int mouseX, int mouseY, int font24, int subFont);
    void DrawStageSelect(int cx, int cy, int mouseX, int mouseY, int font24, int titleFont);
    /*
     */
    void DrawButton(int x, int y, int w, int h, const char* text, bool hover, int color, int font24);

    int phase_;
    int ui_button_graph_;
    int wait_count_;
};
