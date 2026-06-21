#pragma once
#include "Projectile.h"

class CapsuleCollider;

class PlayerHomingBullet : public Projectile {
private:
    int m_lifeTimer;

public:
    PlayerHomingBullet(Vector2 pos, Vector2 dir, float speed);
    virtual ~PlayerHomingBullet() override;

    virtual void Update() override;
    virtual void Draw() override;
    virtual void OnTrigger(Collider* collider, Collider* check) override;
};