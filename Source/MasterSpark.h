#pragma once
#include "Object2D.h"

class CapsuleCollider;

class MasterSpark : public Object2D {
private:
    CapsuleCollider* mpCollider;
    int m_lifeTimer;
    int m_maxLife;
    float m_radius;
    int m_damage;
    int m_colorHue;
    bool m_isActive;
    int m_AttackCount;

public:
    MasterSpark(float x, float y);
    virtual ~MasterSpark() override;

    virtual void Update() override;
    virtual void Draw() override;
    virtual void OnTrigger(Collider* collider, Collider* check) override;
    virtual void OnEnter(Collider* collider, Collider* check) override;
};
