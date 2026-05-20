#pragma once
#include"dxlib.h"
#include"Object2D.h"

class Bullet:public Object2D
{
public:
    Bullet(float x, float y);
    ~Bullet()override;
    void Draw()override;
    void Update()override;
    bool IsActive() { return m_isActive; }

    // 当たり判定・情報取得用の関数
    float GetX() { return m_x; }
    float GetY() { return m_y; }
    float GetRadius() const { return 5.0f; }  // 描画時の半径と同じ
    void Kill() { m_isActive = false; }       // 当たった時に消滅させる
private:
    float m_x, m_y;       // 座標
    float m_speed;        // 移動スピード
    bool m_isActive;      // 画面内に存在しているか（生きているか）
};
