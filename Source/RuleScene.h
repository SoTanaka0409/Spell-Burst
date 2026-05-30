#pragma once
#include "Scene.h"

class RuleScene : public Scene {
public:
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Finalize() override;

private:
    int m_ruleGraphs[6];
    int m_currentSlide;
};
