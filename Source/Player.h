#pragma once
#include "Character.h"
#include <memory>
#include "Barrier.h"

class SpecialBullet;

class Player : public Character
{
public:
    static int kSelectedCharacterType;
    
    enum AttackMode
    {
        kAttackModeMelee,
        kAttackModeSpecial
    };

private:
    float attack;
    float attack_timer_{};
    float attack_interval_{};
    float attack_timer2_{};
    float attack_interval2_{};
    float barrier_count_{};
    AttackMode attack_mode_;
    int special_cooldown_;
    std::weak_ptr<Barrier> barrier_;

    int level_;
    int xp_;
    int xp_needed_;
    int level_up_timer_;
    int spell_gauge_;
    int max_spell_gauge_;

public:
    Player();
    virtual ~Player() override;

    std::shared_ptr<Barrier> GetBarrier() const { return barrier_.lock(); }
    void Initialize();

    void Update() override;
    void Draw() override;

    void Attack();
    void RunBarrierAttack();

    AttackMode GetAttackMode() const { return attack_mode_; }
    int GetSpecialCooldown() const { return special_cooldown_; }
    int GetLevel() const { return level_; }
    int GetXp() const { return xp_; }
    int GetXpNeeded() const { return xp_needed_; }
    int GetLevelUpTimer() const { return level_up_timer_; }
    int GetSpellGauge() const { return spell_gauge_; }
    int GetMaxSpellGauge() const { return max_spell_gauge_; }

    void AddXp(int amount);
    virtual void TakeDamage(int damage_) override;

    virtual void OnEnter(Collider* collider_, Collider* check) override;
    virtual void OnTrigger(Collider* collider_, Collider* check) override;
    virtual void OnExit(Collider* collider_, Collider* check) override;

private:
    void HandleMovement();
    void ShootNormalBullets();
    void HandleDebugAttacks(int mouseInput);
    void UseSpellCard();
    void DrawBarrierAura();
    void DrawStunEffect();
    void DrawPlayerSprite();
};
