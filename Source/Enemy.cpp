#include "Enemy.h"
#include "CapsuleCollider.h"
#include <DxLib.h>
#include "Bullet.h"


Enemy::Enemy(float x, float y) 
    : Object2D(VGet(x, y, 0.0f))
    , mpCollider(nullptr)
{
    SetTag(Tag2D_Enemy);
    m_x = x;
    m_y = y;
    m_speed = 3.0f;
    m_isActive = true;
    m_maxHp = 3; // Take 3 hits to kill
    m_hp = m_maxHp;

    // Create a circular collider with radius 35 (previously 15)
    mpCollider = new CapsuleCollider(this, mvPosition, mvPosition, 35.0f);
}

Enemy::~Enemy() {
    if (mpCollider) {
        delete mpCollider;
        mpCollider = nullptr;
    }
}

void Enemy::Update() {
    m_y += m_speed;
    mvPosition = VGet(m_x, m_y, 0.0f);

    if (mpCollider) {
        mpCollider->mvPosition = mvPosition;
        mpCollider->mvPosition2 = mvPosition;
    }

    if (m_y > 770.0f) {
        m_isActive = false;
        SetDeleteFlag(true);
    }
}

void Enemy::Kill() {
    m_isActive = false;
    SetDeleteFlag(true);
    if (mpCollider) {
        mpCollider->SetDeleteFlag(true);
    }
}


void Enemy::TakeDamage(int damage) {
    m_hp -= damage;
    if (m_hp <= 0) {
        m_hp = 0;
        Kill();
    }
}

void Enemy::OnTrigger(Collider* collider, Collider* check) {
    if (check != nullptr && check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == Tag2D_PlayerBullet) {
            Bullet* bullet = dynamic_cast<Bullet*>(check->GetParentObject());
            if (bullet != nullptr) {
                TakeDamage(bullet->GetDamage());
                bullet->Kill(); // Destroy the bullet on impact
            }
        }
    }
}

void Enemy::Draw() 
{
    if (!m_isActive) return;

    static int s_enemyGraphHandle = -1;
    if (s_enemyGraphHandle == -1) {
        s_enemyGraphHandle = LoadGraph("Resource/enemy.png");
    }

    if (s_enemyGraphHandle != -1) {
        DrawExtendGraph(
            static_cast<int>(mvPosition.x - 35.0f), 
            static_cast<int>(mvPosition.y - 35.0f), 
            static_cast<int>(mvPosition.x + 35.0f), 
            static_cast<int>(mvPosition.y + 35.0f), 
            s_enemyGraphHandle, 
            TRUE
        );
    } else {
        // Draw red circle for enemy as fallback
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 35, GetColor(255, 0, 0), TRUE);
    }

    // Draw HP text above enemy
    DrawFormatString(static_cast<int>(mvPosition.x) - 15, static_cast<int>(mvPosition.y) - 55, GetColor(255, 255, 255), "HP:%d", m_hp);
}
