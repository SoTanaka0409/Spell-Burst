#pragma once
#include "Projectile.h"

class CapsuleCollider;

class MasterSpark : public Projectile {
private:
    int life_timer_;
    int max_life_;
    float radius_;
    int color_hue_;
    int attack_count_;

public:
    MasterSpark(float x, float y);
    virtual ~MasterSpark() override;

    virtual void Update() override;
    virtual void Draw() override;
    virtual void Kill() override;
    virtual void OnTrigger(Collider* collider_, Collider* check) override;
    virtual void OnEnter(Collider* collider_, Collider* check) override;
};