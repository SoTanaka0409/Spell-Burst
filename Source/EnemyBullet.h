#pragma once
#include "Object2D.h"

class CapsuleCollider;

// A class that manages bullets fired by enemy characters (minions and bosses)
class EnemyBullet : public Object2D {
private:
    float m_x, m_y;     // bullet coordinates
    float m_dx, m_dy;   // vector of movement direction
    float m_speed;      // Bullet movement speed
    bool m_isActive;    // Is the bullet effective?
    CapsuleCollider* mpCollider;

    bool m_canReflect;
    bool m_hasReflected;
    bool m_isStunBullet; // Whether the bullet has a stun effect or not
    int m_homingTimer;   // Number of remaining frames for tracking (homing)
    int m_homingDelayTimer;

public:
    EnemyBullet(float x, float y, float dx, float dy, float speed, bool canReflect = false, bool isStunBullet = false, int homingFrames = 0, int homingDelayFrames = 0);
    virtual ~EnemyBullet() override;

    void Update() override;
    void Draw() override;

    virtual void OnTrigger(Collider* collider, Collider* check) override;
};
