#include "PlayerSpellParticle.h"
#include "CapsuleCollider.h"
#include "Enemy.h"
#include "DxLib.h"
#include "Utility.h"
#include <cmath>

PlayerSpellParticle::PlayerSpellParticle(float x, float y, float dx, float dy, float speed)
    : Object2D(VGet(x, y, 0.0f))
    , mpCollider(nullptr)
{
    SetTag(Tag2D_PlayerBullet);
    m_x = x;
    m_y = y;
    m_dx = dx;
    m_dy = dy;
    m_speed = speed;
    m_isActive = true;
    m_damage = 2; // Damage per particle
    m_lifeTimer = 0;

    mpCollider = new CapsuleCollider(this, mvPosition, mvPosition, 16.0f);
}

PlayerSpellParticle::~PlayerSpellParticle() {
    if (mpCollider) {
        delete mpCollider;
        mpCollider = nullptr;
    }
}

void PlayerSpellParticle::Update() {
    m_x += m_dx * m_speed;
    m_y += m_dy * m_speed;
    mvPosition = VGet(m_x, m_y, 0.0f);

    if (mpCollider) {
        mpCollider->mvPosition = mvPosition;
        mpCollider->mvPosition2 = mvPosition;
    }

    m_lifeTimer++;
    
    // Slight curve to make it look beautiful (butterfly/sakura spiral)
    if (m_lifeTimer < 60) {
        float currentAngle = std::atan2(m_dy, m_dx);
        currentAngle += 0.02f; // Slight curve
        m_dx = std::cos(currentAngle);
        m_dy = std::sin(currentAngle);
    }

    if (m_x < -50.0f || m_x > Utility::SCREEN_WIDTH + 50.0f || m_y < -50.0f || m_y > Utility::SCREEN_HEIGHT + 50.0f) {
        Kill();
    }
}

void PlayerSpellParticle::Draw() {
    if (!m_isActive) return;

    // Sakura pink colors
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
    DrawCircle(static_cast<int>(m_x), static_cast<int>(m_y), 20, GetColor(255, 100, 150), TRUE); // aura
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    DrawCircle(static_cast<int>(m_x), static_cast<int>(m_y), 12, GetColor(255, 180, 220), TRUE); // outline
    DrawCircle(static_cast<int>(m_x), static_cast<int>(m_y), 6, GetColor(255, 255, 255), TRUE); // core
}

void PlayerSpellParticle::Kill() {
    m_isActive = false;
    SetDeleteFlag(true);
    if (mpCollider) {
        mpCollider->SetDeleteFlag(true);
    }
}

void PlayerSpellParticle::OnTrigger(Collider* collider, Collider* check) {
    if (!m_isActive || m_lifeTimer < 10) return; // Wait 10 frames to spread out before hitting

    if (check != nullptr && check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == Tag2D_Enemy) {
            Enemy* enemy = dynamic_cast<Enemy*>(check->GetParentObject());
            // Ignore enemies that are already dead or dying
            if (enemy != nullptr && enemy->IsActive() && !enemy->IsDeleteFlag()) {
                enemy->TakeDamage(m_damage);
                Kill();
            }
        }
    }
}
