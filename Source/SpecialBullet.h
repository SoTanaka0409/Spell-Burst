#pragma once
#include "Object2D.h"

class CapsuleCollider;

class SpecialBullet : public Object2D {
private:
    float m_x, m_y;
    float m_speed;
    int m_damage;
    bool m_isActive;
    CapsuleCollider* mpCollider;

public:
    SpecialBullet(float x, float y);
    virtual ~SpecialBullet() override;

    virtual void Update() override;
    virtual void Draw() override;

    int GetDamage() const { return m_damage; }
    void Kill();

    virtual void OnTrigger(Collider* collider, Collider* check) override;
};
