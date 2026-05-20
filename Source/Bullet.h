#pragma once
#include "dxlib.h"
#include "Object2D.h"

class Bullet : public Object2D
{
public:
    Bullet(float x, float y);
    ~Bullet() override;
    void Draw() override;
    void Update() override;
    bool IsActive() { return m_isActive; }

    // Collision helper
    float GetX() { return m_x; }
    float GetY() { return m_y; }
    float GetRadius() const { return 5.0f; }
    void Kill() { m_isActive = false; SetDeleteFlag(true); }

private:
    float m_x, m_y;       // Position
    float m_speed;        // Movement speed
    bool m_isActive;      // Active flag
};
