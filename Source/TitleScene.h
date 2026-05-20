#pragma once
#include "Scene.h"

// タイトル画面クラス
class TitleScene : public Scene {
public:
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Finalize() override;
};
