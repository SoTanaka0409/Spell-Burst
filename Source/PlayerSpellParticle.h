#pragma once
#include "Object2D.h"

class CapsuleCollider;

class PlayerSpellParticle : public Object2D {
private:
    Vector2 m_dir;
    float m_speed;
    int m_damage;
    bool m_isActive;
    int m_lifeTimer;
    CapsuleCollider* mpCollider;

public:
    PlayerSpellParticle(Vector2 pos, Vector2 dir, float speed);
    virtual ~PlayerSpellParticle() override;

    virtual void Update() override;
    virtual void Draw() override;
    virtual void OnTrigger(Collider* collider, Collider* check) override;
    
    void Kill(); 
};
