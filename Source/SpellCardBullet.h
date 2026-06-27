#pragma once
#include "Projectile.h"

class CapsuleCollider;

class SpellCardBullet : public Projectile {
private:
    int lifeTimer;
    void Explode();

public:
    SpellCardBullet(float x, float y);
    virtual ~SpellCardBullet() override;

    virtual void Update() override;
    virtual void Draw() override;
    virtual void OnTrigger(Collider* collider, Collider* check) override;
};