#pragma once
#include "Object2D.h"

class CapsuleCollider;

class PlayerHomingBullet : public Object2D {
private:
    float m_x, m_y;
    float m_dx, m_dy;
    float m_speed;
    int m_damage;
    bool m_isActive;
    int m_lifeTimer;
    CapsuleCollider* mpCollider;

public:
    PlayerHomingBullet(float x, float y, float dx, float dy, float speed);
    virtual ~PlayerHomingBullet() override;

    int GetDamage() const { return m_damage; }

    virtual void Update() override;
    virtual void Draw() override;
    virtual void OnTrigger(Collider* collider, Collider* check) override;
    void Kill();
};
