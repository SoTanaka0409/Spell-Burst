#pragma once
#include "Object2D.h"

class CapsuleCollider;

class EnemyBullet : public Object2D {
private:
    float m_x, m_y;
    float m_dx, m_dy;
    float m_speed;
    bool m_isActive;
    CapsuleCollider* mpCollider;

    bool m_canReflect;
    bool m_hasReflected;

public:
    EnemyBullet(float x, float y, float dx, float dy, float speed, bool canReflect = false);
    virtual ~EnemyBullet() override;

    void Update() override;
    void Draw() override;

    virtual void OnTrigger(Collider* collider, Collider* check) override;
};
