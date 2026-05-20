#pragma once

class Bullet {
private:
    float m_x, m_y;       // 座標
    float m_speed;        // 移動スピード
    bool m_isActive;      // 画面内に存在しているか（生きているか）

public:
    Bullet(float x, float y);
    void Update();
    void Draw();
    bool IsActive() const { return m_isActive; } // 生存フラグの取得

    // 当たり判定・情報取得用の関数
    float GetX() const { return m_x; }
    float GetY() const { return m_y; }
    float GetRadius() const { return 5.0f; }  // 描画時の半径と同じ
    void Kill() { m_isActive = false; }       // 当たった時に消滅させる
};
