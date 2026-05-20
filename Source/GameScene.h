#pragma once
#include "Scene.h"

class EnemyManager;

// Game main scene class
class GameScene : public Scene {
private:
    EnemyManager* mpEnemyManager;

public:
    GameScene();
    virtual ~GameScene() override;
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Finalize() override;
};
