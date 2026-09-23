#pragma once
#include "Scene.h"

// Scene for volume configuration
class ConfigScene : public Scene
{
public:
    ConfigScene();
    ~ConfigScene() override;

    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Finalize() override;

private:
    int bg_graph_;
    float bg_scroll_x_;
    int ui_button_graph_;
    int font_handle_;
    
    // UI drawing helper
    void DrawVolumeUI(int x, int y, const char* label, int volume);
};
