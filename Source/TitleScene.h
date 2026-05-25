#pragma once
#include "Scene.h"

#include <vector>
#include <DxLib.h>

// タイトル画面クラス
class TitleScene : public Scene {
public:

    TitleScene();
    ~TitleScene();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Finalize()override;

private:
    int m_bgGraph;
    float m_bgScrollX;
    int m_uiButtonGraph;
};
