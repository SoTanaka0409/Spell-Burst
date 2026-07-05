#pragma once
#include "Object2D.h"

class RainbowWaveManager : public Object2D {
private:
    int life_timer_;
    int spawn_interval_;
    int spawn_timer_;

public:
    RainbowWaveManager(float x, float y);
    virtual ~RainbowWaveManager() override;

    virtual void Update() override;
    virtual void Draw() override;
    virtual void OnTrigger(Collider* collider_, Collider* check) override;
};
