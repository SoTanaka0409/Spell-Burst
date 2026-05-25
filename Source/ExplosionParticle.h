#pragma once
#include "Object2D.h"

class ExplosionParticle : public Object2D {
private:
    float m_vx;
    float m_vy;
    int m_lifeTime;
    int m_maxLife;
    int m_color;
    float m_size;

public:
    ExplosionParticle(float x, float y, float speed, float angle, int color, int lifeTime, float size);
    virtual ~ExplosionParticle();

    virtual void Update() override;
    virtual void Draw() override;
};
