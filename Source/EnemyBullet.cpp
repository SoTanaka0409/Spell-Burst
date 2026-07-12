#include "EnemyBullet.h"
#include "ObjectManager.h"
#include "CapsuleCollider.h"
#include "Player.h"
#include "Master.h"
#include "SceneManager.h"
#include "Scene.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include <cmath>
#include "utility.h"

EnemyBullet::EnemyBullet(Vector2 pos, Vector2 dir, float speed_, bool can_reflect_, bool is_stun_bullet_, int homingFrames, int homingDelayFrames)
    : Projectile(pos, dir.Normalized(), speed_, 1)
{
    SetTag(kTag2dEnemyBullet);
    this->can_reflect_ = can_reflect_;
    this->has_reflected_ = false;
    this->is_stun_bullet_ = is_stun_bullet_;
    homing_timer_ = homingFrames;
    homing_delay_timer_ = homingDelayFrames;

    if (dir.MagnitudeSq() == 0.0f) {
        dir = Vector2(0.0f, 1.0f);
    }

    collider_ = new CapsuleCollider(this, position_, position_, 10.0f);
}

EnemyBullet::~EnemyBullet() {
}

void EnemyBullet::Update() {
    if (homing_delay_timer_ > 0) {
        homing_delay_timer_--;
    } else if (homing_timer_ > 0) {
        homing_timer_--;
        Player* player = dynamic_cast<Player*>(Master::sceneManager->GetCurrentScene()->GetObjectManager()->GetObject2DByTag(kTag2dPlayer).get());
        if (player) {
            Vector2 targetPos(player->GetX(), player->GetY());
            float currentAngle = Vector2(1, 0).AngleTo(dir);
            float targetAngle = Vector2(1, 0).AngleTo(targetPos - position_);
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

    position_ += dir * (speed_ * Utility::TimeScale);

    Projectile::Update();

    if (IsOutOfBounds()) {
        Kill();
    }
}

void EnemyBullet::Draw() {
    if (!is_active_) return;
    
    if (is_stun_bullet_) {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
        DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 14, GetColor(0, 150, 255), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 10, GetColor(0, 255, 255), TRUE);
        DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 6, GetColor(255, 255, 255), TRUE);
    } else {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
        DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 14, GetColor(255, 0, 128), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 10, GetColor(255, 100, 200), TRUE);
        DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 6, GetColor(255, 255, 255), TRUE);
    }
}

void EnemyBullet::OnTrigger(Collider* collider_, Collider* check) 
{
    if(check!=nullptr&&check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == kTag2dBarrierPlayer)
        {
            check->GetParentObject()->OnTrigger(check, collider_);
            Kill();
            return;
        }
	}
    if (check != nullptr && check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == kTag2dPlayer) {
            Player* player = dynamic_cast<Player*>(check->GetParentObject());
            if (player != nullptr) {
                player->TakeDamage(1);
                if (is_stun_bullet_) {
                    player->Stun(60);
                }
            }
            Kill();
        }
    }
}

