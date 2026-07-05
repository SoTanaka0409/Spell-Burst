#pragma once
#include "Projectile.h"

class CapsuleCollider;

class PlayerHomingBullet : public Projectile {
private:
    int life_timer_;

public:
    PlayerHomingBullet(Vector2 pos, Vector2 dir, float speed_);
    virtual ~PlayerHomingBullet() override;

    virtual void Update() override;
    virtual void Draw() override;
    virtual void OnTrigger(Collider* collider_, Collider* check) override;
};