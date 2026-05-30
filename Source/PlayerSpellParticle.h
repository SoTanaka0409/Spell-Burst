#pragma once
#include "Object2D.h"

class CapsuleCollider;

class PlayerSpellParticle : public Object2D {
private:
<<<<<<< HEAD
    float m_x, m_y;
=======
>>>>>>> main
    float m_dx, m_dy;
    float m_speed;
    int m_damage;
    bool m_isActive;
    int m_lifeTimer;
    CapsuleCollider* mpCollider;

public:
    PlayerSpellParticle(float x, float y, float dx, float dy, float speed);
    virtual ~PlayerSpellParticle() override;

    virtual void Update() override;
    virtual void Draw() override;
    virtual void OnTrigger(Collider* collider, Collider* check) override;
    
    void Kill(); 
};
