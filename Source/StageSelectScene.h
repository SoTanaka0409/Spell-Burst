#pragma once
#include "BaseScene.h"

// ステージ選択画面クラス
class StageSelectScene : public BaseScene {
public:
    void Initialize() override;
    SceneType Update() override;
    void Draw() override;
};
