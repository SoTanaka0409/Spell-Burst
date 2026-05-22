#pragma once
#include "Scene.h"

// タイトル画面クラス
class TitleScene : public Scene {
public:

    TitleScene();
    ~TitleScene();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Finalize()override;
};
