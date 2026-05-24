#pragma once
#include "Object2D.h"

class CapsuleCollider;

class RainbowBullet : public Object2D {
private:
    CapsuleCollider* mpCollider;
    float m_speed;
    int m_damage;
    int m_colorHue;

public:
    RainbowBullet(float x, float y);
    virtual ~RainbowBullet() override;

    virtual void Update() override;
    virtual void Draw() override;
    virtual void OnTrigger(Collider* collider, Collider* check) override;
};
