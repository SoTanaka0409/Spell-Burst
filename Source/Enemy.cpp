#include "Enemy.h"
#include <DxLib.h>

Enemy::Enemy(float x, float y) 
    : Object2D(VGet(x, y, 0.0f))
{
    m_x = x;
    m_y = y;
    m_speed = 3.0f;
    m_isActive = true;
}

Enemy::~Enemy() {
}

void Enemy::Update() {
    m_y += m_speed;
    mvPosition = VGet(m_x, m_y, 0.0f);

    if (m_y > 800.0f) {
        m_isActive = false;
        SetDeleteFlag(true);
    }
}

void Enemy::Draw() {
    if (!m_isActive) return;
    DrawCircle(mvPosition.x,mvPosition.y, 15, GetColor(255, 0, 0), TRUE);
}
