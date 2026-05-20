#pragma once
#include "Object2D.h"

class CapsuleCollider;

class Boss : public Object2D {
private:
    float m_x, m_y;
    float m_speed;
    int m_hp;
    int m_maxHp;
    bool m_isActive;
    
    // Target position for random movement
    float m_targetX, m_targetY;
    
    // Attack timers and states
    int m_attackTimer;
    int m_patternIndex;
    
    CapsuleCollider* mpCollider;

public:
    Boss(float x, float y);
    virtual ~Boss() override;

    void Update() override;
    void Draw() override;

    int GetHp() const { return m_hp; }
    int GetMaxHp() const { return m_maxHp; }
    bool IsActive() const { return m_isActive; }

    float GetX() const { return m_x; }
    float GetY() const { return m_y; }
    float GetRadius() const { return 80.0f; }

    void TakeDamage(int damage);
    void Kill();

    virtual void OnTrigger(Collider* collider, Collider* check) override;

private:
    void ShootRadialBarrage();
    void ShootFanBarrage();
    void ShootTargetedBarrage();
    void SelectNewTarget();
};
