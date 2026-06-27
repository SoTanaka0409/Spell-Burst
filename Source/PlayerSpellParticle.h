#pragma once
#include "Object2D.h"

class CapsuleCollider;

class PlayerSpellParticle : public Object2D {
private:
    Vector2 dir;
    float speed;
    int damage;
    bool isActive;
    int lifeTimer;
    CapsuleCollider* collider;

public:
    PlayerSpellParticle(Vector2 pos, Vector2 dir, float speed);
    virtual ~PlayerSpellParticle() override;

    virtual void Update() override;
    virtual void Draw() override;
    virtual void OnTrigger(Collider* collider, Collider* check) override;
    
    void Kill(); 
};
