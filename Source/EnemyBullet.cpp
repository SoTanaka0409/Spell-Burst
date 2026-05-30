#include "EnemyBullet.h"
#include "CapsuleCollider.h"
#include "Player.h"
#include "Master.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ObjectManager.h"
#include <DxLib.h>
#include <cmath>
#include "utility.h"

EnemyBullet::EnemyBullet(float x, float y, float dx, float dy, float speed, bool canReflect, bool isStunBullet, int homingFrames, int homingDelayFrames)
    : Object2D(VGet(x, y, 0.0f))
    , mpCollider(nullptr)
{
    SetTag(Tag2D_EnemyBullet);// / Important: so it hits the player!
    m_x = x;
    m_y = y;
    m_dx = dx;
    m_dy = dy;
    m_speed = speed;
    m_isActive = true;
    m_canReflect = false; // Bounce (reflection) disabled as requested by user
    m_hasReflected = false;
    m_isStunBullet = isStunBullet;
    m_homingTimer = homingFrames;
    m_homingDelayTimer = homingDelayFrames;

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

// Update processing called every frame
// Move the bullet in the specified vector direction, and set a deletion flag when it goes off the screen.
void EnemyBullet::Update() {
    if (m_homingDelayTimer > 0) {
        m_homingDelayTimer--;
    } else if (m_homingTimer > 0) {
        m_homingTimer--;
        Player* player = dynamic_cast<Player*>(Master::sceneManager->GetCurrentScene()->GetObjectManager()->GetObject2DByTag(Tag2D_Player));
        if (player) {
            float currentAngle = std::atan2(m_dy, m_dx);
            float targetAngle = std::atan2(player->GetY() - m_y, player->GetX() - m_x);
            
            float diff = targetAngle - currentAngle;
            // Normalize angle to -PI ~ PI
            while (diff > 3.14159265f) diff -= 2.0f * 3.14159265f;
            while (diff < -3.14159265f) diff += 2.0f * 3.14159265f;
            
            // Rotation speed (e.g. 0.05 radians per frame)
            float turnSpeed = 0.03f; 
            if (diff > turnSpeed) diff = turnSpeed;
            if (diff < -turnSpeed) diff = -turnSpeed;
            
            currentAngle += diff;
            m_dx = std::cos(currentAngle);
            m_dy = std::sin(currentAngle);
        }
    }

    m_x += m_dx * m_speed;
    m_y += m_dy * m_speed;
    mvPosition = VGet(m_x, m_y, 0.0f);

    if (mpCollider) {
        mpCollider->mvPosition = mvPosition;
        mpCollider->mvPosition2 = mvPosition;
    }

    // Delete when it goes off screen (bounce processing has been disabled)
    if (m_x < -50.0f || m_x > Utility::SCREEN_WIDTH + 50.0f || m_y < -50.0f || m_y > Utility::SCREEN_HEIGHT + 50.0f) {
        m_isActive = false;
        SetDeleteFlag(true);
    }
}

// Drawing processing
// Draw an image of enemy bullets.
void EnemyBullet::Draw() {
    if (!m_isActive) return;
    
    if (m_isStunBullet) {
        // Stun bullets are light blue
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
        DrawCircle(static_cast<int>(m_x), static_cast<int>(m_y), 14, GetColor(0, 150, 255), TRUE); // aura
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        DrawCircle(static_cast<int>(m_x), static_cast<int>(m_y), 10, GetColor(0, 255, 255), TRUE); // outer frame
        DrawCircle(static_cast<int>(m_x), static_cast<int>(m_y), 6, GetColor(255, 255, 255), TRUE); // core
    } else {
        // Normal enemy bullets (for barrage) are magenta/red.
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
        DrawCircle(static_cast<int>(m_x), static_cast<int>(m_y), 14, GetColor(255, 0, 128), TRUE); // aura
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        DrawCircle(static_cast<int>(m_x), static_cast<int>(m_y), 10, GetColor(255, 100, 200), TRUE); // outer frame
        DrawCircle(static_cast<int>(m_x), static_cast<int>(m_y), 6, GetColor(255, 255, 255), TRUE); // core
    }
}

void EnemyBullet::OnTrigger(Collider* collider, Collider* check) {
    if (check != nullptr && check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == Tag2D_Player) {
            Player* player = dynamic_cast<Player*>(check->GetParentObject());
            if (player != nullptr) {
                player->TakeDamage(1);
                if (m_isStunBullet) {
                    player->Stun(60); // Stun for 1 second
                }
            }
            m_isActive = false;
            SetDeleteFlag(true);
            if (mpCollider) {
                mpCollider->SetDeleteFlag(true);
            }
        }
    }
}
