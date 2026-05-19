#include "Bullet.h"
#include <DxLib.h>

Bullet::Bullet(float x, float y) {
    m_x = x;
    m_y = y;
    m_speed = 10.0f; // 弾のスピード（上に向かって飛ぶ）
    m_isActive = true;
}

void Bullet::Update() {
    // 上に向かって移動（y座標を減らす）
    m_y -= m_speed;

    // 画面外（上端）に出たら消す
    if (m_y < 0) {
        m_isActive = false;
    }
}

void Bullet::Draw() {
    // 弾として黄色の小さい円を描画
    DrawCircle((int)m_x, (int)m_y, 5, GetColor(255, 255, 0), TRUE);
}
