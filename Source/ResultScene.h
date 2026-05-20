#pragma once
#include "Scene.h"

// リザルト（結果）画面クラス
class ResultScene : public Scene {
public:
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Finalize() override;
};
