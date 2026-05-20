#include "Enemy.h"
#include <DxLib.h>

Enemy::Enemy(float x, float y) {
    m_x = x;
    m_y = y;
    m_speed = 3.0f; // 下へ移動するスピード
    m_isActive = true;
}

void Enemy::Update() {
    // 下に向かって移動
    m_y += m_speed;

    // 画面外（下）に出たら消滅フラグを立てる
    if (m_y > 800.0f) { // 720よりも少し下まで行ったら消す
        m_isActive = false;
    }
}

void Enemy::Draw() {
    if (!m_isActive) return;

    // 仮の画像として、赤色の円を描画する
    // (x, y, 半径, 色, 塗りつぶしフラグ)
    DrawCircle((int)m_x, (int)m_y, 15, GetColor(255, 0, 0), TRUE);
}
