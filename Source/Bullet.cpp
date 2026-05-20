#include "Bullet.h"
#include "DxLib.h"

Bullet::Bullet(float x, float y) 
    :Object2D(VGet(x,y,0))
{
    m_x = x;
    m_y = y;
    m_speed = 10.0f; // 弾のスピード（上に向かって飛ぶ）
    m_isActive = true;
}

Bullet::~Bullet()
{
}

void Bullet::Update() 
{
    // 上に向かって移動（y座標を減らす）
    m_y -= m_speed;

    // 画面外（上端）に出たら消す
    if (m_y < 0) {
        m_isActive = false;
    }
}

void Bullet::Draw()
{

}


