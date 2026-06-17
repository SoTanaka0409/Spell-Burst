#pragma once
#include "Object2D.h"

class CapsuleCollider;

class PlayerHomingBullet : public Object2D {
private:
    
    Vector2 m_dir;
    float m_speed;
    int m_damage;
    bool m_isActive;
    int m_lifeTimer;
    CapsuleCollider* mpCollider;

public:
    PlayerHomingBullet(Vector2 pos, Vector2 dir, float speed);
    virtual ~PlayerHomingBullet() override;

    int GetDamage() const { return m_damage; }

    virtual void Update() override;
    virtual void Draw() override;
    virtual void OnTrigger(Collider* collider, Collider* check) override;
    void Kill();
};
