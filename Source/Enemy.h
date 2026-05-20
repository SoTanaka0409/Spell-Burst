#pragma once

class Enemy {
private:
    float m_x, m_y;       // 座標
    float m_speed;        // 移動スピード
    bool m_isActive;      // 生きているかどうかのフラグ

public:
    Enemy(float x, float y);
    void Update();
    void Draw();

    // 生きているか確認するための関数
    bool IsActive() const { return m_isActive; }

    // 当たり判定・情報取得用の関数
    float GetX() const { return m_x; }
    float GetY() const { return m_y; }
    float GetRadius() const { return 15.0f; } // 描画時の半径と同じ
    void Kill() { m_isActive = false; }       // 当たった時に消滅させる
};
