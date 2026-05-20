#include "Player.h"
#include "InputManager.h"
#include "Bullet.h"
#include <DxLib.h>

Player::Player() 
    : Object2D(VGet(1280.0f / 2.0f, 720.0f / 2.0f, 0.0f))
{
    Initialize();
}

void Player::Initialize() {
    m_x = 1280.0f / 2.0f;
    m_y = 720.0f / 2.0f;
    m_speed = 5.0f;
}

void Player::Update()
{
    if (InputManager::CheckPressKey(KEY_INPUT_W)) { m_y -= m_speed; }
    if (InputManager::CheckPressKey(KEY_INPUT_S)) { m_y += m_speed; }
    if (InputManager::CheckPressKey(KEY_INPUT_A)) { m_x -= m_speed; }
    if (InputManager::CheckPressKey(KEY_INPUT_D)) { m_x += m_speed; }

    if (m_x < 20.0f) m_x = 20.0f;
    if (m_x > 1260.0f) m_x = 1260.0f;
    if (m_y < 20.0f) m_y = 20.0f;
    if (m_y > 700.0f) m_y = 700.0f;

    mvPosition = VGet(m_x, m_y, 0.0f);

    if (InputManager::CheckDownKey(KEY_INPUT_SPACE)) {
        new Bullet(m_x, m_y - 20.0f);
    }
}

void Player::Draw() {
    DrawCircle(mvPosition.x, mvPosition.y, 20, GetColor(0, 255, 0), TRUE);
}

void Player::OnEnter(Collider* collider, Collider* check) {}
void Player::OnTrigger(Collider* collider, Collider* check) {}
void Player::OnExit(Collider* collider, Collider* check) {}
