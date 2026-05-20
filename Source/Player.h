#pragma once
#include "Collider.h"
#include "Object2D.h"

class Player : public Object2D
{
private:
    float m_x, m_y;       // Position
    float m_speed;        // Speed

public:
    Player();
    void Initialize();
    void Update() override;
    void Draw() override;
    float GetX() const { return m_x; }
    float GetY() const { return m_y; }

    virtual void OnEnter(Collider* collider, Collider* check) override;
    virtual void OnTrigger(Collider* collider, Collider* check) override;
    virtual void OnExit(Collider* collider, Collider* check) override;
};
