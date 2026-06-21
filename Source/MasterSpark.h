#pragma once
#include "Projectile.h"

class CapsuleCollider;

class MasterSpark : public Projectile {
private:
    int m_lifeTimer;
    int m_maxLife;
    float m_radius;
    int m_colorHue;
    int m_AttackCount;

public:
    MasterSpark(float x, float y);
    virtual ~MasterSpark() override;

    virtual void Update() override;
    virtual void Draw() override;
    virtual void Kill() override;
    virtual void OnTrigger(Collider* collider, Collider* check) override;
    virtual void OnEnter(Collider* collider, Collider* check) override;
};