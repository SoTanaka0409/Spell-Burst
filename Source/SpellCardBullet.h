#pragma once
#include "Projectile.h"

class CapsuleCollider;

class SpellCardBullet : public Projectile {
private:
    int life_timer_;
    void Explode();

public:
    SpellCardBullet(float x, float y);
    virtual ~SpellCardBullet() override;

    virtual void Update() override;
    virtual void Draw() override;
    virtual void OnTrigger(Collider* collider_, Collider* check) override;
};