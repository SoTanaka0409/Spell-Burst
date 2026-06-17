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

EnemyBullet::EnemyBullet(Vector2 pos, Vector2 dir, float speed, bool canReflect, bool isStunBullet, int homingFrames, int homingDelayFrames)
    : Object2D(pos)
    , mpCollider(nullptr)
{
    SetTag(Tag2D_EnemyBullet);
    mvPosition = pos;
    m_dir = dir.Normalized();
    m_speed = speed;
    m_isActive = true;
    m_canReflect = false;
    m_hasReflected = false;
    m_isStunBullet = isStunBullet;
    m_homingTimer = homingFrames;
    m_homingDelayTimer = homingDelayFrames;


    if (m_dir.MagnitudeSq() == 0.0f) {
        m_dir = Vector2(0.0f, 1.0f);
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
            Vector2 targetPos(player->GetX(), player->GetY());
            float currentAngle = Vector2(0, 0).AngleTo(m_dir);
            float targetAngle = mvPosition.AngleTo(targetPos);
            float diff = targetAngle - currentAngle;
            while (diff > 3.14159265f) diff -= 2.0f * 3.14159265f;
            while (diff < -3.14159265f) diff += 2.0f * 3.14159265f;
            float turnSpeed = 0.05f * Utility::TimeScale;
            if (diff > turnSpeed) currentAngle += turnSpeed;
            else if (diff < -turnSpeed) currentAngle -= turnSpeed;
            else currentAngle = targetAngle;
            m_dir = Vector2::FromAngle(currentAngle);
        }
    }

    mvPosition += m_dir * (m_speed * Utility::TimeScale);
    mvPosition = Vector2(mvPosition.x, mvPosition.y);

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
