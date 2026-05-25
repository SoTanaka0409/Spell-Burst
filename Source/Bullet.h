#pragma once
#include "Object2D.h"

class CapsuleCollider;

// A class that manages normal bullets fired by the player.
class Bullet : public Object2D
{
public:
    Bullet(float x, float y,float damage);
    virtual ~Bullet() override;
    void Draw() override;
    void Update() override;
    bool IsActive() { return m_isActive; }

    // Collision helper
    float GetX() { return m_x; }
    float GetY() { return m_y; }
    float GetRadius() const { return 10.0f; }
    int GetDamage() const { return m_damage; }
    void Kill();

    virtual void OnTrigger(Collider* collider, Collider* check) override;

private:
    float m_x, m_y;       // bullet coordinates
    float m_speed;        // Bullet movement speed
    bool m_isActive;      // Is the bullet effective?
    int m_damage;         // Amount of damage caused by bullets
    CapsuleCollider* mpCollider;
};
