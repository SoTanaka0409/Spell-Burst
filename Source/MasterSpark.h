#pragma once
#include "Projectile.h"

class CapsuleCollider;

class MasterSpark : public Projectile {
private:
    int lifeTimer;
    int maxLife;
    float radius;
    int colorHue;
    int attackCount;

public:
    MasterSpark(float x, float y);
    virtual ~MasterSpark() override;

    virtual void Update() override;
    virtual void Draw() override;
    virtual void Kill() override;
    virtual void OnTrigger(Collider* collider, Collider* check) override;
    virtual void OnEnter(Collider* collider, Collider* check) override;
};