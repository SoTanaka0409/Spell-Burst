#pragma once
#include "Object2D.h"

class Enemy : public Object2D {
private:
    float m_x, m_y;       // Position
    float m_speed;        // Speed
    bool m_isActive;      // Active flag

public:
    Enemy(float x, float y);
    ~Enemy() override;
    void Update() override;
    void Draw() override;

    // Active check
    bool IsActive() const { return m_isActive; }

    // Collision helper
    float GetX() const { return m_x; }
    float GetY() const { return m_y; }
    float GetRadius() const { return 15.0f; }
    void Kill() { m_isActive = false; SetDeleteFlag(true); }
};
