#include "Bullet.h"
#include "DxLib.h"

Bullet::Bullet(float x, float y) 
    : Object2D(VGet(x, y, 0.0f))
{
    m_x = x;
    m_y = y;
    m_speed = 10.0f;
    m_isActive = true;
}

Bullet::~Bullet()
{
}

void Bullet::Update() 
{
    m_y -= m_speed;
    mvPosition = VGet(m_x, m_y, 0.0f);

    if (m_y < 0.0f) {
        m_isActive = false;
        SetDeleteFlag(true);
    }
}

void Bullet::Draw()
{
    if (!m_isActive) return;
    DrawCircle((int)m_x, (int)m_y, 5, GetColor(255, 255, 255), TRUE);
}
