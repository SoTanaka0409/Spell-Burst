#pragma once

class Player {
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
};
