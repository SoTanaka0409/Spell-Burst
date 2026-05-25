#pragma once
#include "Scene.h"

class StageSelectScene : public Scene {
public:
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Finalize() override;
private:
    int m_phase; // 0: Character, 1: Stage
    int m_uiButtonGraph;

    int m_WaitCount;
};
