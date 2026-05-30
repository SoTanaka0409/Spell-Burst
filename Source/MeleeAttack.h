#pragma once
#include "Object2D.h"

class CapsuleCollider;

// A class that manages the player's melee attacks (knife and sword swings)
class MeleeAttack : public Object2D {
private:
    float m_x, m_y; // Coordinates where attack judgment is occurring
    int m_lifetime; // Duration of attack (number of frames)
    int m_damage;   // Amount of damage dealt
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
