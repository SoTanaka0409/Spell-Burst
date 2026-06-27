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
    : Projectile(pos, dir.Normalized(), speed, 1)
{
    SetTag(Tag2D_EnemyBullet);
    canReflect = false;
    hasReflected = false;
    isStunBullet = isStunBullet;
    homingTimer = homingFrames;
    homingDelayTimer = homingDelayFrames;

    if (dir.MagnitudeSq() == 0.0f) {
        dir = Vector2(0.0f, 1.0f);
    }

    collider = new CapsuleCollider(this, position, position, 10.0f);
}

EnemyBullet::~EnemyBullet() {
}

void EnemyBullet::Update() {
    if (homingDelayTimer > 0) {
        homingDelayTimer--;
    } else if (homingTimer > 0) {
        homingTimer--;
        Player* player = dynamic_cast<Player*>(Master::sceneManager->GetCurrentScene()->GetObjectManager()->GetObject2DByTag(Tag2D_Player));
        if (player) {
            Vector2 targetPos(player->GetX(), player->GetY());
            float currentAngle = Vector2(0, 0).AngleTo(dir);
            float targetAngle = position.AngleTo(targetPos);
            float diff = targetAngle - currentAngle;
            while (diff > 3.14159265f) diff -= 2.0f * 3.14159265f;
            while (diff < -3.14159265f) diff += 2.0f * 3.14159265f;
            float turnSpeed = 0.05f * Utility::TimeScale;
            if (diff > turnSpeed) currentAngle += turnSpeed;
            else if (diff < -turnSpeed) currentAngle -= turnSpeed;
            else currentAngle = targetAngle;
            dir = Vector2::FromAngle(currentAngle);
        }
    }

    position += dir * (speed * Utility::TimeScale);

    Projectile::Update();

    if (IsOutOfBounds()) {
        Kill();
    }
}

void EnemyBullet::Draw() {
    if (!isActive) return;
    
    if (isStunBullet) {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
        DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), 14, GetColor(0, 150, 255), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), 10, GetColor(0, 255, 255), TRUE);
        DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), 6, GetColor(255, 255, 255), TRUE);
    } else {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
        DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), 14, GetColor(255, 0, 128), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), 10, GetColor(255, 100, 200), TRUE);
        DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), 6, GetColor(255, 255, 255), TRUE);
    }
}

void EnemyBullet::OnTrigger(Collider* collider, Collider* check) 
{
    if(check!=nullptr&&check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == Tag2D_BarrierPlayer)
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
                if (isStunBullet) {
                    player->Stun(60);
                }
            }
            Kill();
        }
    }
}