#include "Player.h"
#include "InputManager.h"
#include "Bullet.h"
#include "CapsuleCollider.h"
#include"dxlib.h"
#include "Utility.h"

Player::Player() 
    : Object2D(VGet((float)Utility::SCREEN_WIDTH / 2.0f, (float)Utility::SCREEN_HEIGHT / 2.0f, 0.0f))
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

#include "MeleeAttack.h"
#include "SpecialBullet.h"

void Player::Initialize() {
    m_x = (float)Utility::SCREEN_WIDTH / 2.0f;
    m_y = (float)Utility::SCREEN_HEIGHT / 2.0f;
    m_speed = 5.0f;
    m_maxHp = 5;
    m_hp = m_maxHp;
    m_attackMode = AttackMode_Bullet;
    m_specialCooldown = 0;

    // Level & XP system initialization
    m_level = 1;
    m_xp = 0;
    m_xpNeeded = 5; // Level 1 needs 5 XP to level up
    m_levelUpTimer = 0;

    // Create a circular collider with radius 35
    mpCollider = new CapsuleCollider(this, mvPosition, mvPosition, 35.0f);
}

void Player::Update()
{
    if (InputManager::CheckPressKey(KEY_INPUT_W)) { m_y -= m_speed; }
    if (InputManager::CheckPressKey(KEY_INPUT_S)) { m_y += m_speed; }
    if (InputManager::CheckPressKey(KEY_INPUT_A)) { m_x -= m_speed; }
    if (InputManager::CheckPressKey(KEY_INPUT_D)) { m_x += m_speed; }

    // Clamp inside screen with 45.0f padding
    if (m_x < 45.0f) m_x = 45.0f;
    if (m_x > Utility::SCREEN_WIDTH - 45.0f) m_x = Utility::SCREEN_WIDTH - 45.0f;
    if (m_y < 45.0f) m_y = 45.0f;
    if (m_y > Utility::SCREEN_HEIGHT - 45.0f) m_y = Utility::SCREEN_HEIGHT - 45.0f;

    mvPosition = VGet(m_x, m_y, 0.0f);

    if (mpCollider) {
        mpCollider->mvPosition = mvPosition;
        mpCollider->mvPosition2 = mvPosition;
    }

    // Cooldown decrement
    if (m_specialCooldown > 0) {
        m_specialCooldown--;
    }

    // Level-up flash timer decrement
    if (m_levelUpTimer > 0) {
        m_levelUpTimer--;
    }

    // Switch attack modes
    if (InputManager::CheckDownKey(KEY_INPUT_Q)) {
        if (m_attackMode == AttackMode_Bullet) m_attackMode = AttackMode_Melee;
        else if (m_attackMode == AttackMode_Melee) m_attackMode = AttackMode_Special;
        else m_attackMode = AttackMode_Bullet;
    }
    if (InputManager::CheckDownKey(KEY_INPUT_1)) {
        m_attackMode = AttackMode_Bullet;
    }
    if (InputManager::CheckDownKey(KEY_INPUT_2)) {
        m_attackMode = AttackMode_Melee;
    }
    if (InputManager::CheckDownKey(KEY_INPUT_3)) {
        m_attackMode = AttackMode_Special;
    }

    // Firing attacks
    if (InputManager::CheckDownKey(KEY_INPUT_SPACE)) {
        if (m_attackMode == AttackMode_Bullet) {
            int numBullets = m_level;
            float spacing = 20.0f;
            float startX = m_x - (numBullets - 1) * spacing / 2.0f;
            for (int i = 0; i < numBullets; ++i) {
                new Bullet(startX + i * spacing, m_y - 45.0f);
            }
        }
        else if (m_attackMode == AttackMode_Melee) {
            new MeleeAttack(m_x, m_y - 70.0f);
        }
        else if (m_attackMode == AttackMode_Special) {
            if (m_specialCooldown == 0) {
                new SpecialBullet(m_x, m_y - 90.0f);
                m_specialCooldown = 180; // 3 seconds cooldown
            }
        }
    }
}

void Player::Draw() {
    static int s_playerGraphHandle = -1;
    if (s_playerGraphHandle == -1) {
        s_playerGraphHandle = LoadGraph("Resource/player.png");
    }

    if (s_playerGraphHandle != -1) {
        DrawExtendGraph(
            static_cast<int>(mvPosition.x - 45.0f), 
            static_cast<int>(mvPosition.y - 45.0f), 
            static_cast<int>(mvPosition.x + 45.0f), 
            static_cast<int>(mvPosition.y + 45.0f), 
            s_playerGraphHandle, 
            TRUE
        );
    } else {
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 45, GetColor(0, 255, 0), TRUE);
    }
}

#include "Enemy.h"
#include "Master.h"
#include "SceneManager.h"
#include "ResultScene.h"

void Player::TakeDamage(int damage) {
    m_hp -= damage;
    if (m_hp <= 0) {
        m_hp = 0;
        ResultScene::s_isVictory = false;
        Master::sceneManager->SetNextScene(SceneManager::SCENE_RESULT);
    }
}

void Player::AddXp(int amount) {
    m_xp += amount;
    // Level-up loop (handles multiple level-ups from one big XP gain)
    while (m_xp >= m_xpNeeded) {
        m_xp -= m_xpNeeded;
        m_level++;
        m_xpNeeded = m_level * 5; // Each level requires (level * 5) XP
        // Bonus on level up: full HP restore
        m_hp = m_maxHp;
        m_levelUpTimer = 120; // Show "LEVEL UP!" for 120 frames (~2 seconds)
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
