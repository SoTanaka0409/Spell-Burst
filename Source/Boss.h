#pragma once
#include "Object2D.h"

class CapsuleCollider;

// A class that manages boss character data, behavior, and barrage patterns.
class Boss : public Object2D {
private:
    float m_x, m_y;       // XY coordinates of the boss on the screen
    float m_speed;        // movement speed
    int m_hp;             // current physical strength
    int m_maxHp;          // maximum health
    bool m_isActive;      // Flag for whether the boss is active or not
    int m_bossType;       // Boss type (1-3)
    
    // Random movement destination (target coordinates)
    float m_targetX, m_targetY;
    
    // Timer to manage attack patterns and firing intervals
    int m_attackTimer;
    int m_patternIndex;

    // Status and timer to manage death effect when defeated
    bool m_isDying;
    int m_deathTimer;
    
    // Variables that manage phase (remaining lives) and invincibility time
    int m_lives;
    int m_invincibleTimer;
    int m_invincibleCycleTimer; // Timer to manage invincibility every 5 seconds
    
    CapsuleCollider* mpCollider;

public:
    Boss(float x, float y, int bossType = 3);
    virtual ~Boss() override;

    // It is called every frame and performs movement processing, attack processing, and death effects.
    void Update() override;

    // Called every frame, draws the boss image and the flashing effect when receiving damage.
    void Draw() override;

    int GetHp() const { return m_hp; }
    int GetMaxHp() const { return m_maxHp; }
    bool IsActive() const { return m_isActive; }
    int GetLives() const { return m_lives; }

    float GetX() const { return m_x; }
    float GetY() const { return m_y; }
    float GetRadius() const { return 80.0f; }

    // Damage processing called when attacked by a player
    void TakeDamage(int damage);

    // Process to completely eliminate the boss
    void Kill();

    // Processing when overlapping with other objects (determination of collision with bullet)
    virtual void OnTrigger(Collider* collider, Collider* check) override;

private:
    // Boss barrage pattern processing group
    void ShootRadialBarrage();    // Barrage in all directions (radial)
    void ShootFanBarrage();       // Barrage in fan shape (wide area in front)
    void ShootTargetedBarrage();  // A barrage aimed at the player
    void ShootSimpleBarrage();    // Simple bullet for type 1
    void ShootBouncingBarrage();  // Reflector bullet for type 2
    
    // Determine the destination of the next random move
    void SelectNewTarget();
};
