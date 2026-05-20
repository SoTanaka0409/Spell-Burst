#include "Player.h"
#include"InputManager.h"
#include <DxLib.h>

Player::Player() {
    Initialize();
}

void Player::Initialize() {
    // 画面の中央あたりに初期配置
    m_x = 1280.0f / 2.0f;
    m_y = 720.0f / 2.0f;
    m_speed = 5.0f; // スピード調整
}

void Player::Update()
{
    // WASDキーで移動（押している間は true）
    if (InputManager::CheckDownKey(KEY_INPUT_W)) { m_y -= m_speed; } // 上
    if (InputManager::CheckDownKey(KEY_INPUT_S)) { m_y += m_speed; } // 下
    if (InputManager::CheckDownKey(KEY_INPUT_A)) { m_x -= m_speed; } // 左
    if (InputManager::CheckDownKey(KEY_INPUT_D)) { m_x += m_speed; } // 右
}

void Player::Draw() {
    // 仮の画像として、緑色の円を描画する
    // (x, y, 半径, 色, 塗りつぶしフラグ)
    DrawCircle((int)m_x, (int)m_y, 20, GetColor(0, 255, 0), TRUE);
}
