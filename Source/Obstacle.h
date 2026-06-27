#pragma once
#include "Object2D.h"

class CapsuleCollider;

class Obstacle : public Object2D {
private:
    CapsuleCollider* collider;
    float fallSpeed;

public:
    Obstacle(float x, float y);
    virtual ~Obstacle() override;

    virtual void Update() override;
    virtual void Draw() override;
    virtual void OnTrigger(Collider* collider, Collider* check) override;
};
