#include "EnemyBullet.h"
#include "CapsuleCollider.h"
#include "Player.h"
#include <DxLib.h>
#include <cmath>
#include "utility.h"

EnemyBullet::EnemyBullet(float x, float y, float dx, float dy, float speed, bool canReflect)
    : Object2D(VGet(x, y, 0.0f))
    , mpCollider(nullptr)
{
    SetTag(Tag2D_Enemy); // Important: so it hits the player!
    m_x = x;
    m_y = y;
    m_dx = dx;
    m_dy = dy;
    m_speed = speed;
    m_isActive = true;
    m_canReflect = canReflect;
    m_hasReflected = false;

    // Normalize direction vector just in case
    float len = std::sqrt(m_dx * m_dx + m_dy * m_dy);
    if (len > 0.0f) {
        m_dx /= len;
        m_dy /= len;
    } else {
        m_dx = 0.0f;
        m_dy = 1.0f;
    }

    mpCollider = new CapsuleCollider(this, mvPosition, mvPosition, 10.0f);
}

EnemyBullet::~EnemyBullet() {
    if (mpCollider) {
        delete mpCollider;
        mpCollider = nullptr;
    }
}

void EnemyBullet::Update() {
    m_x += m_dx * m_speed;
    m_y += m_dy * m_speed;
    mvPosition = VGet(m_x, m_y, 0.0f);

    if (mpCollider) {
        mpCollider->mvPosition = mvPosition;
        mpCollider->mvPosition2 = mvPosition;
    }

    if (m_canReflect && !m_hasReflected) {
        bool reflected = false;
        if (m_x < 0.0f) {
            m_x = 0.0f;
            m_dx = -m_dx;
            reflected = true;
        } else if (m_x > Utility::SCREEN_WIDTH) {
            m_x = (float)Utility::SCREEN_WIDTH;
            m_dx = -m_dx;
            reflected = true;
        }
        
        if (m_y < 0.0f) {
            m_y = 0.0f;
            m_dy = -m_dy;
            reflected = true;
        } else if (m_y > Utility::SCREEN_HEIGHT) {
            m_y = (float)Utility::SCREEN_HEIGHT;
            m_dy = -m_dy;
            reflected = true;
        }

        if (reflected) {
            m_hasReflected = true;
        }
    }

    // Clean up when off-screen
    if (!m_canReflect || m_hasReflected) {
        if (m_x < -50.0f || m_x > Utility::SCREEN_WIDTH + 50.0f || m_y < -50.0f || m_y > Utility::SCREEN_HEIGHT + 50.0f) {
            m_isActive = false;
            SetDeleteFlag(true);
        }
    }
}

void EnemyBullet::Draw() {
    if (!m_isActive) return;
    // Draw a bright magenta/red glowing energy ball
    DrawCircle(static_cast<int>(m_x), static_cast<int>(m_y), 10, GetColor(255, 0, 128), TRUE);
    DrawCircle(static_cast<int>(m_x), static_cast<int>(m_y), 6, GetColor(255, 255, 255), TRUE);
}

void EnemyBullet::OnTrigger(Collider* collider, Collider* check) {
    if (check != nullptr && check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == Tag2D_Player) {
            Player* player = dynamic_cast<Player*>(check->GetParentObject());
            if (player != nullptr) {
                player->TakeDamage(1);
            }
            m_isActive = false;
            SetDeleteFlag(true);
            if (mpCollider) {
                mpCollider->SetDeleteFlag(true);
            }
        }
    }
}
