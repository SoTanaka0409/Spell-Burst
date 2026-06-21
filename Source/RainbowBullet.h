#pragma once
#include "Projectile.h"

class CapsuleCollider;

class RainbowBullet : public Projectile {
private:
    int m_colorHue;

public:
    RainbowBullet(float x, float y);
    virtual ~RainbowBullet() override;

    virtual void Update() override;
    virtual void Draw() override;
    virtual void OnTrigger(Collider* collider, Collider* check) override;
};