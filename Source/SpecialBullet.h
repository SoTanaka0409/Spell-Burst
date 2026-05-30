#pragma once
#include "Object2D.h"

class CapsuleCollider;

// A class that manages the player's special moves (piercing bullets and powerful attacks)
class SpecialBullet : public Object2D {
private:
    float m_x, m_y;     // Special bullet coordinates
    float m_speed;      // Bullet movement speed
    int m_damage;       // Amount of damage dealt
    bool m_isActive;    // Is the bullet effective?
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
