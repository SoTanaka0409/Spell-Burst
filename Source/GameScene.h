#pragma once
#include "Scene.h"

class EnemyManager;

// Scene class that manages the main play screen of the game
class GameScene : public Scene {
private:
    // Manager who manages enemy appearance and WAVE progress
    EnemyManager* mpEnemyManager;

    // Cut-in related
    int m_cutinTimer;
    int m_cutinImageHandle;

public:
    GameScene();
    virtual ~GameScene() override;

    // Called during scene transition, creates and initializes players and managers.
    void Initialize() override;

    // Called every frame, handles the entire game's logic (pose, object updates, hit detection)
    void Update() override;

    // Called every frame, draws the background, each object, and HUD (HP and experience points)
    void Draw() override;

    // Called when the scene ends to release the allocated memory
    void Finalize() override;

    // Activate spell card cut-in
    void TriggerCutin();
};
