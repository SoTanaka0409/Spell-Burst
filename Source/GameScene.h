#pragma once
#include "Scene.h"

// ゲーム本編画面クラス
class GameScene : public Scene {
public:
    GameScene();
    ~GameScene();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Finalize() override;
};
