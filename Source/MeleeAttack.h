#pragma once
#include "Object2D.h"

class CapsuleCollider;

class MeleeAttack : public Object2D {
private:
    float m_x, m_y;
    int m_lifetime; // Duration of the slash in frames
    int m_damage;
    CapsuleCollider* mpCollider;

public:
    MeleeAttack(float x, float y);
    virtual ~MeleeAttack() override;

    virtual void Update() override;
    virtual void Draw() override;

    int GetDamage() const { return m_damage; }
    void Kill();

    virtual void OnTrigger(Collider* collider, Collider* check) override;
};
