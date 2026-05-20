#pragma once
#include "Object2D.h"

class CapsuleCollider;

class Player : public Object2D
{
private:
    float m_x, m_y;       // Position
    float m_speed;        // Speed
    int m_hp;             // Current HP
    int m_maxHp;          // Maximum HP
    CapsuleCollider* mpCollider;

public:
    Player();
    virtual ~Player() override;
    void Initialize();
    void Update() override;
    void Draw() override;
    float GetX() const { return m_x; }
    float GetY() const { return m_y; }
    int GetHp() const { return m_hp; }
    int GetMaxHp() const { return m_maxHp; }
    void TakeDamage(int damage);

    virtual void OnEnter(Collider* collider, Collider* check) override;
    virtual void OnTrigger(Collider* collider, Collider* check) override;
    virtual void OnExit(Collider* collider, Collider* check) override;
};
