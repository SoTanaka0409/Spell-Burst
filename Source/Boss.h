#pragma once
#include "Character.h"

class CapsuleCollider;

// ボスクラス（Character継承）
class Boss : public Character {
private:
    int bossType; 
    float targetX, targetY; 
    
    int attackTimer; 
    int patternIndex; 

    bool isDying; 
    int deathTimer; 
    
    int lives; 
    int invincibleTimer; 
    int invincibleCycleTimer; 

public:
    Boss(float x, float y, int bossType = 3);
    virtual ~Boss() override;

    void Update() override;
    void Draw() override;

    int GetLives() const { return lives; }

    virtual void TakeDamage(int damage) override;
    virtual void Kill() override;

    float GetRadius() const { return 80.0f; }

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