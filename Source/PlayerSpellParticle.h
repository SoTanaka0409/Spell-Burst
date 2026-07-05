#pragma once
#include "Object2D.h"

class CapsuleCollider;

class PlayerSpellParticle : public Object2D {
private:
    Vector2 dir;
    float speed_;
    int damage_;
    bool is_active_;
    int life_timer_;
    CapsuleCollider* collider_;

public:
    PlayerSpellParticle(Vector2 pos, Vector2 dir, float speed_);
    virtual ~PlayerSpellParticle() override;

    virtual void Update() override;
    virtual void Draw() override;
    virtual void OnTrigger(Collider* collider_, Collider* check) override;
    
    void Kill(); 
};
