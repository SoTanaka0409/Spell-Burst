#include "EnemyBullet.h"
#include "CapsuleCollider.h"
#include "Player.h"
#include "Master.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ObjectManager.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include <cmath>
#include "utility.h"

EnemyBullet::EnemyBullet(float x, float y, float dx, float dy, float speed, bool canReflect, bool isStunBullet, int homingFrames, int homingDelayFrames)
    : Object2D(VGet(x, y, 0.0f))
    , mpCollider(nullptr)
{
    SetTag(Tag2D_EnemyBullet);
    mvPosition.x = x;
    mvPosition.y = y;
    m_dx = dx;
    m_dy = dy;
    m_speed = speed;
    m_isActive = true;
    m_canReflect = false;
    m_hasReflected = false;
    m_isStunBullet = isStunBullet;
    m_homingTimer = homingFrames;
    m_homingDelayTimer = homingDelayFrames;


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
    if (m_homingDelayTimer > 0) {
        m_homingDelayTimer--;
    } else if (m_homingTimer > 0) {
        m_homingTimer--;
        Player* player = dynamic_cast<Player*>(Master::sceneManager->GetCurrentScene()->GetObjectManager()->GetObject2DByTag(Tag2D_Player));
        if (player) {
            float currentAngle = std::atan2(m_dy, m_dx);
            float targetAngle = std::atan2(player->GetY() - mvPosition.y, player->GetX() - mvPosition.x);
            
            float diff = targetAngle - currentAngle;
            while (diff > 3.14159265f) diff -= 2.0f * 3.14159265f;
            while (diff < -3.14159265f) diff += 2.0f * 3.14159265f;
            float turnSpeed = 0.03f; 
            if (diff > turnSpeed) diff = turnSpeed;
            if (diff < -turnSpeed) diff = -turnSpeed;
            
            currentAngle += diff;
            m_dx = std::cos(currentAngle);
            m_dy = std::sin(currentAngle);
        }
    }

    mvPosition.x += m_dx * m_speed * Utility::TimeScale;
    mvPosition.y += m_dy * m_speed * Utility::TimeScale;
    mvPosition = VGet(mvPosition.x, mvPosition.y, 0.0f);

    if (mpCollider) {
        mpCollider->mvPosition = mvPosition;
        mpCollider->mvPosition2 = mvPosition;
    }
    if (mvPosition.x < -50.0f || mvPosition.x > Utility::SCREEN_WIDTH + 50.0f || mvPosition.y < -50.0f || mvPosition.y > Utility::SCREEN_HEIGHT + 50.0f) {
        m_isActive = false;
        SetDeleteFlag(true);
    }
}
void EnemyBullet::Draw() {
    if (!m_isActive) return;
    
    if (m_isStunBullet) {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 14, GetColor(0, 150, 255), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 10, GetColor(0, 255, 255), TRUE);
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 6, GetColor(255, 255, 255), TRUE);
    } else {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 14, GetColor(255, 0, 128), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 10, GetColor(255, 100, 200), TRUE);
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 6, GetColor(255, 255, 255), TRUE);
    }
}

void EnemyBullet::OnTrigger(Collider* collider, Collider* check) 
{
    if(check!=nullptr&&check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == tag2D_BarierPla)
        {
            check->GetParentObject()->OnTrigger(check, collider);
            Kill();
            return;
        }
	}
    if (check != nullptr && check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == Tag2D_Player) {
            Player* player = dynamic_cast<Player*>(check->GetParentObject());
            if (player != nullptr) {
                player->TakeDamage(1);
                if (m_isStunBullet) {
                    player->Stun(60);
                }
            }
            Kill();
        }
    }
}

void EnemyBullet::Kill() 
{
    m_isActive = false;
    SetDeleteFlag(true);
    if (mpCollider) {
        mpCollider->SetDeleteFlag(true);
    }
}
