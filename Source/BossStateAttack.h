// BossStateAttack.h
// Concrete attack states for Boss.
// BossStateSimple   -> Boss type 1: regular barrage
// BossStateBouncing -> Boss type 2: bouncing barrage
// BossStateFinal    -> Boss type 3: rotating pattern + spell cards
#pragma once
#include "BossState.h"

// Boss type 1 state: simple straight-fire barrage
class BossStateSimple : public BossState
{
public:
    BossStateSimple() : attack_timer_(0) {}
    void Update(Boss* boss) override;

private:
    int attack_timer_;
};

// Boss type 2 state: bouncing barrage
class BossStateBouncing : public BossState
{
public:
    BossStateBouncing() : attack_timer_(0) {}
    void Update(Boss* boss) override;

private:
    int attack_timer_;
};

// Boss type 3 state: rotating pattern + spell cards + summon minions
class BossStateFinal : public BossState
{
public:
    BossStateFinal() : attack_timer_(0), pattern_index_(0),
        invincible_timer_(0), invincible_cycle_timer_(0) {}
    void Update(Boss* boss) override;

private:
    int attack_timer_;
    int pattern_index_;
    int invincible_timer_;
    int invincible_cycle_timer_;
};

// Dying state: plays death animation then signals scene transition
class BossStateDying : public BossState
{
public:
    BossStateDying() : death_timer_(180) {}
    void Update(Boss* boss) override;

private:
    int death_timer_;
};
