#pragma once
#include "Projectile.h"

class CapsuleCollider;

class SpecialBullet : public Projectile
{
public:
    SpecialBullet(float x, float y);
    virtual ~SpecialBullet() override;

    virtual void Update() override;
    virtual void Draw() override;
    virtual void Kill() override;
    virtual void OnTrigger(Collider* collider, Collider* check) override;
};
