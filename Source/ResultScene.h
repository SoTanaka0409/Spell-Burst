#pragma once
#include "Scene.h"

class ResultScene : public Scene {
public:
    static bool s_isVictory;

    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Finalize() override;
};
