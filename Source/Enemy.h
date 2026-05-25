#pragma once
#include "Object2D.h"

class CapsuleCollider;

// A class that manages general enemy character data and behavior.
// It inherits Object2D and has on-screen drawing and collision detection.
class Enemy : public Object2D {
private:
    float m_x, m_y;       // Enemy's on-screen XY coordinates
    float m_speed;        // enemy movement speed
    bool m_isActive;      // Flag indicating whether an enemy is present on screen and active.
    int m_hp;             // Enemy's current health
    int m_maxHp;          // enemy's maximum health
    CapsuleCollider* mpCollider; // Collider that manages hit detection (capsule-shaped/circular)

    int m_enemyType;      // Enemy type (1: Movement only, 2: Normal bullet, 3: Stun bullet, 4: Medium boss)
    int m_attackTimer;    // timer for firing bullets

    float m_targetX, m_targetY; // Random movement destination (for mid-boss)
    void SelectNewTarget();     // Determine the destination of the next random move (for mid-boss)

public:
    Enemy(float x, float y, int enemyType = 1);
    virtual ~Enemy() override;

    // Called every frame, it processes the movement of enemies and deletes them when they go out of the screen.
    void Update() override;

    // Called every frame, draws the enemy's image and HP bar
    void Draw() override;

    // Get active flag
    bool IsActive() const { return m_isActive; }

    // Acquisition of HP information and damage processing
    int GetHp() const { return m_hp; }
    int GetMaxHp() const { return m_maxHp; }

    // A process called when attacked by a player to reduce HP.
    void TakeDamage(int damage);

    // Get coordinates and radius of hit detection
    float GetX() const { return m_x; }
    float GetY() const { return m_y; }
    float GetRadius() const { 
        if (m_enemyType == 4) return 45.0f; // Make the mid-boss a little bigger
        return 15.0f; 
    }

    // A process that is called when HP reaches 0, and causes the enemy to disappear.
    void Kill();

    // Processing when it overlaps with another object (hit detection event)
    virtual void OnTrigger(Collider* collider, Collider* check) override;
};
