#pragma once
#include "Object2D.h"

class CapsuleCollider;

class SpellCardBullet : public Object2D {
private:
    float m_x, m_y;
    float m_speed;
    int m_damage;
    bool m_isActive;
    int m_lifeTimer;
    CapsuleCollider* mpCollider;

    void Explode();

public:
    SpellCardBullet(float x, float y);
    virtual ~SpellCardBullet() override;

    virtual void Update() override;
    virtual void Draw() override;
    virtual void OnTrigger(Collider* collider, Collider* check) override;
};
