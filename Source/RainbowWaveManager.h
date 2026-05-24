#pragma once
#include "Object2D.h"

class RainbowWaveManager : public Object2D {
private:
    int m_lifeTimer;
    int m_spawnInterval;
    int m_spawnTimer;

public:
    RainbowWaveManager(float x, float y);
    virtual ~RainbowWaveManager() override;

    virtual void Update() override;
    virtual void Draw() override;
    virtual void OnTrigger(Collider* collider, Collider* check) override;
};
