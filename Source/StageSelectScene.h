#pragma once
#include "Scene.h"

// ステージ選択画面クラス
class StageSelectScene : public Scene {
public:
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Finalize() override;
};
