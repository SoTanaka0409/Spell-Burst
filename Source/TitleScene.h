#pragma once
#include "Scene.h"

// title screen class
class TitleScene : public Scene {
public:

    TitleScene();
    ~TitleScene();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Finalize()override;
};
