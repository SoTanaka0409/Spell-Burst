#pragma once
#include "Scene.h"

// Game main scene class
class GameScene : public Scene {
public:
    GameScene();
    virtual ~GameScene() override;
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Finalize() override;
};
