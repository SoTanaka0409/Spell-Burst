#pragma once
#include "Object2D.h"

class CapsuleCollider;

class Obstacle : public Object2D
{
private:
    CapsuleCollider* collider_;
    float fall_speed_;

public:
    Obstacle(float x, float y);
    virtual ~Obstacle() override;

    virtual void Update() override;
    virtual void Draw() override;
    /*
     */
    virtual void OnTrigger(Collider* collider, Collider* check) override;
    /*
     */
    virtual void OnEnter(Collider* collider, Collider* check) override;
};
