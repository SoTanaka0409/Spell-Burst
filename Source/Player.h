#pragma once
#include"Collider.h"
#include"Object2D.h"
class Player:public Object2D
{
private:
    float m_x, m_y;       // プレイヤーの座標
    float m_speed;        // 移動スピード

public:
    Player();
    void Initialize();
    void Update();
    void Draw();
    float GetX() const { return m_x; } // X座標の取得
    float GetY() const { return m_y; } // Y座標の取得

    virtual void OnEnter(Collider* collider, Collider* check);
    virtual void OnTrigger(Collider* collider, Collider* check);
    virtual void OnExit(Collider* collider, Collider* check);
};
