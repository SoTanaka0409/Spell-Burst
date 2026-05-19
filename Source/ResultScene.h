#pragma once
#include "BaseScene.h"

// リザルト（結果）画面クラス
class ResultScene : public BaseScene {
public:
    void Initialize() override;
    SceneType Update() override;
    void Draw() override;
};
