#pragma once
#include "Object2D.h"

class CapsuleCollider;

class Boss : public Object2D {
private:
    float m_speed;
    int m_hp;
    int m_maxHp;
    bool m_isActive;
    int m_bossType;
    
    float m_targetX, m_targetY;
    
    int m_attackTimer;
    int m_patternIndex;

    bool m_isDying;
    int m_deathTimer;
    
    int m_lives;
    int m_invincibleTimer;
    int m_invincibleCycleTimer;
    
    CapsuleCollider* mpCollider;

public:
    Boss(float x, float y, int bossType = 3);
    virtual ~Boss() override;

    void Update() override;

    void Draw() override;

    int GetHp() const { return m_hp; }
    int GetMaxHp() const { return m_maxHp; }
    bool IsActive() const { return m_isActive; }
    int GetLives() const { return m_lives; }

    float GetX() const { return mvPosition.x; }
    float GetY() const { return mvPosition.y; }
    float GetRadius() const { return 80.0f; }

    void TakeDamage(int damage);

    void Kill();

    virtual void OnTrigger(Collider* collider, Collider* check) override;

private:
    void ShootRadialBarrage();
    void ShootFanBarrage();
    void ShootTargetedBarrage();
    void ShootSimpleBarrage();
    void ShootBouncingBarrage();
    void ShootSpellCardBarrage();
    
    void SelectNewTarget();
};
