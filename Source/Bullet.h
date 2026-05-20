#pragma once
#include "Object2D.h"

class CapsuleCollider;

class Bullet : public Object2D
{
public:
    Bullet(float x, float y);
    virtual ~Bullet() override;
    void Draw() override;
    void Update() override;
    bool IsActive() { return m_isActive; }

    // Collision helper
    float GetX() { return m_x; }
    float GetY() { return m_y; }
    float GetRadius() const { return 5.0f; }
    int GetDamage() const { return m_damage; }
    void Kill();

    virtual void OnTrigger(Collider* collider, Collider* check) override;

private:
    float m_x, m_y;       // Position
    float m_speed;        // Movement speed
    bool m_isActive;      // Active flag
    int m_damage;         // Damage dealt by bullet
    CapsuleCollider* mpCollider;
};
