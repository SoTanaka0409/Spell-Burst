#include "Player.h"
#include "InputManager.h"
#include "Bullet.h"
#include "CapsuleCollider.h"
#include <DxLib.h>

Player::Player() 
    : Object2D(VGet(1280.0f / 2.0f, 720.0f / 2.0f, 0.0f))
    , mpCollider(nullptr)
{
    SetTag(Tag2D_Player);
    Initialize();
}

Player::~Player() {
    if (mpCollider) {
        delete mpCollider;
        mpCollider = nullptr;
    }
}

void Player::Initialize() {
    m_x = 1280.0f / 2.0f;
    m_y = 720.0f / 2.0f;
    m_speed = 5.0f;
    m_maxHp = 5;
    m_hp = m_maxHp;

    // Create a circular collider with radius 20
    mpCollider = new CapsuleCollider(this, mvPosition, mvPosition, 20.0f);
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

    if (mpCollider) {
        mpCollider->mvPosition = mvPosition;
        mpCollider->mvPosition2 = mvPosition;
    }

    if (InputManager::CheckDownKey(KEY_INPUT_SPACE)) {
        new Bullet(m_x + 20.0f, m_y);
    }
}

void Player::Draw() {
    static int s_playerGraphHandle = -1;
    if (s_playerGraphHandle == -1) {
        s_playerGraphHandle = LoadGraph("Resource/player.png");
    }

    if (s_playerGraphHandle != -1) {
        DrawExtendGraph(
            static_cast<int>(mvPosition.x - 20.0f), 
            static_cast<int>(mvPosition.y - 20.0f), 
            static_cast<int>(mvPosition.x + 20.0f), 
            static_cast<int>(mvPosition.y + 20.0f), 
            s_playerGraphHandle, 
            TRUE
        );
    } else {
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 20, GetColor(0, 255, 0), TRUE);
    }
}

#include "Enemy.h"
#include "Master.h"
#include "SceneManager.h"

void Player::TakeDamage(int damage) {
    m_hp -= damage;
    if (m_hp <= 0) {
        m_hp = 0;
        Master::sceneManager->SetNextScene(SceneManager::SCENE_RESULT);
    }
}

void Player::OnEnter(Collider* collider, Collider* check) {}
void Player::OnTrigger(Collider* collider, Collider* check) {
    if (check != nullptr && check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == Tag2D_Enemy) {
            Enemy* enemy = dynamic_cast<Enemy*>(check->GetParentObject());
            if (enemy != nullptr) {
                TakeDamage(1); // Player takes 1 damage
                //enemy->Kill(); // Destroy the enemy on crash
            }
        }
    }
}
void Player::OnExit(Collider* collider, Collider* check) {}
