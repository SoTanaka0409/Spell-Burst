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

Barrier::Barrier(float x, float y, float radius, Object2D::Tag2D obj)
    : Object2D(Vector2(x, y))
    , collider_(nullptr)
{
    SetTag(obj); 
    deploy_interval_ = 300.0f;
    active_duration_ = 120.0f;
    timer_ = 0.0f;
    this->radius_ = radius_;
    is_deployed_ = false;
    hit_count_ = 0;
}

Barrier::~Barrier()
{
    if (collider_)
    {
        delete collider_;
        collider_ = nullptr;
    }
}

void Barrier::Update()
{
    timer_ += 1.0f * Utility::time_scale_;

    if (!is_deployed_)
    {
        if (timer_ >= deploy_interval_)
        {
            is_deployed_ = true;
            SoundManager::GetInstance()->PlaySE("Resource/se_barrier.wav");
            timer_ = 0.0f;
            collider_ = new CapsuleCollider(this, position_, position_, radius_);
        }
    } else
    {
        if (timer_ >= active_duration_)
        {
            is_deployed_ = false;
            timer_ = 0.0f;
           
            if (collider_)
            {
                collider_->position_ = position_;
                collider_->position2_ = position_;
            }
            if (collider_)
            {
                collider_->SetDeleteFlag(true);
                collider_ = nullptr;
            }
        }
    }

    if (collider_)
    {
        collider_->position_ = position_;
        collider_->position2_ = position_;
    }
}

void Barrier::Draw()
{
    if (is_deployed_)
    {
        int alpha = 150 + static_cast<int>(std::sin(GetNowCount() * 0.005f) * 50);
        
        if (GetTag() == kTag2dBarrierEnemy)
        {
            // 敵バリア�E�赤〜オレンジのシールチE
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
            DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), static_cast<int>(radius_), GetColor(150, 20, 0), TRUE);
            
            SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
            DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), static_cast<int>(radius_), GetColor(255, 80, 0), FALSE);
            DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), static_cast<int>(radius_) - 2, GetColor(255, 200, 0), FALSE);
            DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), static_cast<int>(radius_) + 2, GetColor(255, 200, 0), FALSE);
        } else
        {
            // プレイヤーバリア�E�青〜シアン
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
            DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), static_cast<int>(radius_), GetColor(0, 50, 150), TRUE);
            
            SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
            DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), static_cast<int>(radius_), GetColor(100, 255, 255), FALSE);
            DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), static_cast<int>(radius_) - 2, GetColor(0, 255, 255), FALSE);
            DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), static_cast<int>(radius_) + 2, GetColor(0, 255, 255), FALSE);
        }
        
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
}

void Barrier::OnTrigger(Collider* collider, Collider* check)
{
    if (!is_deployed_) return;

    if (check != nullptr && check->GetParentObject() != nullptr)
    {
        auto tag_ = check->GetParentObject()->GetTag();
        if (this->GetTag() == kTag2dBarrierPlayer && tag_ == kTag2dEnemyBullet)
        {
            check->GetParentObject()->SetDeleteFlag(true);
            hit_count_++;
            if (hit_count_ >= 30)
            {
                hit_count_ = 0;
                SoundManager::GetInstance()->PlaySE("Resource/SE/se_button1.mp3");
                float baseSpeed = 10.0f;
                for (int dir = 0; dir < 4; ++dir)
                {
                    float baseAngle = dir * (3.14159265f / 2.0f);
                    for (int i = 0; i < 10; ++i)
                    {
                        float spread = (i - 4.5f) * 0.1f; 
                        float angle = baseAngle + spread;
                        
                        Vector2 dir = Vector2::FromAngle(angle);
                        ObjectManager::Instantiate<PlayerHomingBullet>(position_ + dir * 30.0f, dir, baseSpeed);
                    }
                }
            }
        }
        else if (GetTag() == kTag2dBarrierEnemy && tag_ == kTag2dPlayerBullet)
        {
            check->GetParentObject()->SetDeleteFlag(true);
        }
       
    }
}




