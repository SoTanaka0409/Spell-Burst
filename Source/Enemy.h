#pragma once
#include "Object2D.h"

class CapsuleCollider;

class Enemy : public Object2D {
private:
    float m_x, m_y;       // Position
    float m_speed;        // Speed
    bool m_isActive;      // Active flag
    int m_hp;             // Enemy HP
    int m_maxHp;          // Enemy Max HP
    CapsuleCollider* mpCollider;

public:
    Enemy(float x, float y);
    virtual ~Enemy() override;
    void Update() override;
    void Draw() override;

    // Active check
    bool IsActive() const { return m_isActive; }

    // HP getters and damage
    int GetHp() const { return m_hp; }
    int GetMaxHp() const { return m_maxHp; }
    void TakeDamage(int damage);

    // Collision helper
    float GetX() const { return m_x; }
    float GetY() const { return m_y; }
    float GetRadius() const { return 15.0f; }
    void Kill();

    virtual void OnTrigger(Collider* collider, Collider* check) override;
};
