#pragma once
#include "Character.h"
#include "BossState.h"
#include <memory>

class CapsuleCollider;

// ボスクラス（Character継承）
class Boss : public Character {
private:
    int bossType; 
    float targetX, targetY; 
    
    int attack_timer_; 
    int patternIndex; 

    bool isDying; 
    int deathTimer; 
    
    int lives; 
    int invincibleTimer; 
    int invincibleCycleTimer; 

    std::unique_ptr<BossState> state_; // Current behavior state

public:
    Boss(float x, float y, int bossType = 3);
    virtual ~Boss() override;

    void Update() override;
    void Draw() override;

    int GetLives() const { return lives; }

    virtual void TakeDamage(int damage_) override;
    virtual void Kill() override;

    float GetRadius() const { return 80.0f; }

    virtual void OnTrigger(Collider* collider_, Collider* check) override;

    // Exposed for BossState subclasses
    void ShootRadialBarrage();
    void ShootFanBarrage();
    void ShootTargetedBarrage();
    void ShootSimpleBarrage();
    void ShootBouncingBarrage();
    void ShootSpellCardBarrage();
    void SelectNewTarget();

    void SetState(BossState* newState) { state_.reset(newState); }
    int GetBossType() const { return bossType; }
    bool GetIsDying() const { return isDying; }
    int GetInvincibleTimer() const { return invincibleTimer; }
    void SetInvincibleTimer(int t) { invincibleTimer = t; }
};