#pragma once
#include "Object2D.h"

class CapsuleCollider;

class Player : public Object2D
{
public:
    enum AttackMode {
        AttackMode_Bullet,
        AttackMode_Melee,
        AttackMode_Special
    };

private:
    float m_x, m_y;       // Position
    float m_speed;        // Speed
    int m_hp;             // Current HP
    int m_maxHp;          // Maximum HP
	float mfAttack;	   // Base attack damage (can be modified by level-ups)
    AttackMode m_attackMode;      // Current attack pattern
    int m_specialCooldown;        // Cooldown for ultimate
    CapsuleCollider* mpCollider;

    // Level-up & Experience system
    int m_level;
    int m_xp;
    int m_xpNeeded;
    int m_levelUpTimer;

public:
    Player();
    virtual ~Player() override;
    void Initialize();
    void Update() override;
    void Draw() override;
    float GetX() const { return m_x; }
    float GetY() const { return m_y; }
    int GetHp() const { return m_hp; }
    int GetMaxHp() const { return m_maxHp; }
    AttackMode GetAttackMode() const { return m_attackMode; }
    int GetSpecialCooldown() const { return m_specialCooldown; }
    int GetLevel() const { return m_level; }
    int GetXp() const { return m_xp; }
    int GetXpNeeded() const { return m_xpNeeded; }
    int GetLevelUpTimer() const { return m_levelUpTimer; }
    void AddXp(int amount);
    void TakeDamage(int damage);

    virtual void OnEnter(Collider* collider, Collider* check) override;
    virtual void OnTrigger(Collider* collider, Collider* check) override;
    virtual void OnExit(Collider* collider, Collider* check) override;
};
