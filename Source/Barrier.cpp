#include "Barrier.h"
#include "ObjectManager.h"
#include "CapsuleCollider.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include "Utility.h"
#include "PlayerHomingBullet.h"
#include "SoundManager.h"
#include <cmath>

Barrier::Barrier(float x, float y, float radius_, Object2D::Tag2D obj)
    : Object2D(Vector2(x, y))
    , collider_(nullptr)
{
    SetTag(obj); 
    deployInterval = 300.0f;
    activeDuration = 180.0f;
    timer = 0.0f;
    radius_ = radius_;
    isDeployed = false;
    hit_count = 0;
}

Barrier::~Barrier() {
    if (collider_) {
        delete collider_;
        collider_ = nullptr;
    }
}

void Barrier::Update() {
    timer += 1.0f * Utility::TimeScale;

    if (!isDeployed) {
        if (timer >= deployInterval) {
            isDeployed = true;
            SoundManager::GetInstance()->PlaySE("Resource/se_barrier.wav");
            timer = 0.0f;
            collider_ = new CapsuleCollider(this, position_, position_, radius_);
        }
    } else {
        if (timer >= activeDuration) {
            isDeployed = false;
            timer = 0.0f;
           
            if (collider_)
            {
                collider_->position_ = position_;
                collider_->position2 = position_;
            }
            if (collider_) {
                collider_->SetDeleteFlag(true);
                collider_ = nullptr;
            }
        }
    }

    if (collider_) {
        collider_->position_ = position_;
        collider_->position2 = position_;
    }
}

void Barrier::Draw() {
    if (isDeployed) {
        int alpha = 150 + static_cast<int>(std::sin(GetNowCount() * 0.005f) * 50);
        SetDrawBlendMode(DX_BLENDMODE_ADD, alpha);
        
        DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), static_cast<int>(radius_), GetColor(0, 50, 150), TRUE);
        DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), static_cast<int>(radius_), GetColor(255, 255, 255), FALSE);
        DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), static_cast<int>(radius_) - 1, GetColor(0, 255, 255), FALSE);
        DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), static_cast<int>(radius_) + 1, GetColor(0, 255, 255), FALSE);
        
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
}

void Barrier::OnTrigger(Collider* collider_, Collider* check) {
    if (!isDeployed) return;

    if (check != nullptr && check->GetParentObject() != nullptr) {
        auto tag_ = check->GetParentObject()->GetTag();
        if (this->GetTag() == kTag2dBarrierPlayer && tag_ == kTag2dEnemyBullet)
        {
            check->GetParentObject()->SetDeleteFlag(true);
            hit_count++;
            if (hit_count >= 30) {
                hit_count = 0;
                SoundManager::GetInstance()->PlaySE("Resource/SE/?K???X???????1.3");
                float baseSpeed = 10.0f;
                for (int dir = 0; dir < 4; ++dir) {
                    float baseAngle = dir * (3.14159265f / 2.0f);
                    for (int i = 0; i < 10; ++i) {
                        float spread = (i - 4.5f) * 0.1f; 
                        float angle = baseAngle + spread;
                        
                        Vector2 dir = Vector2::FromAngle(angle);
                        ObjectManager::Instantiate<PlayerHomingBullet>(position_ + dir * 30.0f, dir, baseSpeed);
                    }
                }
            }
        }
        else if (GetTag() == kTag2dBarrierEnemy && tag_ == kTag2dPlayerBullet) {
            check->GetParentObject()->SetDeleteFlag(true);
        }
       
    }
}




