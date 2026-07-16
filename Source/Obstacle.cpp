#include "Obstacle.h"
#include "ObjectManager.h"
#include "CapsuleCollider.h"
#include "Utility.h"
#include "Player.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "MasterSpark.h"
#include "SpecialBullet.h"
#include "SpellCardBullet.h"
#include "RainbowBullet.h"
#include "ExplosionParticle.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"

Obstacle::Obstacle(float x, float y)
    : Object2D(Vector2(x, y))
    , collider_(nullptr)
    , fall_speed_(3.0f)
{
    SetTag(kTag2dEnemy); // 繝励Ξ繧､繝､繝ｼ縺ｮ蠑ｾ繧・ｽ灘ｽ薙◆繧雁愛螳壹・蟇ｾ雎｡縺ｨ縺吶ｋ縺溘ａ萓ｿ螳應ｸ頑雰繧ｿ繧ｰ繧剃ｻ倅ｸ・
    collider_ = new CapsuleCollider(this, position_, position_, 40.0f);
}

Obstacle::~Obstacle()
{
    if (collider_)
    {
        delete collider_;
        collider_ = nullptr;
    }
}

void Obstacle::Update()
{
    position_.y += fall_speed_ * Utility::time_scale_;
    
    if (collider_)
    {
        collider_->position_ = position_;
        collider_->position2_ = position_;
    }

    if (position_.y > Utility::kScreenHeight + 100.0f)
    {
        SetDeleteFlag(true);
        if (collider_)
        {
            collider_->SetDeleteFlag(true);
        }
    }
}

void Obstacle::Draw()
{
    int graph = ResourceManager::GetInstance()->GetGraph("Resource/rock.png");
    if (graph != -1)
    {
        DrawExtendGraph(
            static_cast<int>(position_.x - 45.0f),
            static_cast<int>(position_.y - 45.0f),
            static_cast<int>(position_.x + 45.0f),
            static_cast<int>(position_.y + 45.0f),
            graph, TRUE
        );
    } else
    {
        DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 40, GetColor(100, 100, 100), TRUE);
        DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 38, GetColor(80, 80, 80), TRUE);
    }
}

void Obstacle::OnTrigger(Collider* collider, Collider* check)
{
    if (check != nullptr && check->GetParentObject() != nullptr)
    {
        Object2D* parent = check->GetParentObject();
        // 繝励Ξ繧､繝､繝ｼ蛛ｴ縺ｮ謾ｻ謦・→陦晉ｪ√＠縺溷ｴ蜷医・蜃ｦ逅・ｼ育音谿雁ｼｾ縺九←縺・°縺ｧ蛻・ｲ撰ｼ・
        if (parent->GetTag() == kTag2dPlayerBullet)
        {
            bool isSpecial = false;
            if (dynamic_cast<MasterSpark*>(parent) != nullptr ||
                dynamic_cast<RainbowBullet*>(parent) != nullptr ||
                dynamic_cast<SpellCardBullet*>(parent) != nullptr ||
                dynamic_cast<SpecialBullet*>(parent) != nullptr)
                {
                isSpecial = true;
            }

            if (isSpecial)
            {
                this->SetDeleteFlag(true);
                if (collider_) collider_->SetDeleteFlag(true);
                SoundManager::GetInstance()->PlaySE("Resource/se_enemy_die.wav");
                for (int i = 0; i < 5; i++)
                {
                    ObjectManager::Instantiate<ExplosionParticle>(position_.x, position_.y, 2.0f, static_cast<float>(rand() % 360) * 3.14159f / 180.0f, GetColor(150, 150, 150), 30, 10.0f);
                }
            } else
            {
                parent->SetDeleteFlag(true);
                check->SetDeleteFlag(true);
            }
        }
    }
}

void Obstacle::OnEnter(Collider* collider, Collider* check)
{
    if (check != nullptr && check->GetParentObject() != nullptr)
    {
        Object2D* parent = check->GetParentObject();
        // 繝励Ξ繧､繝､繝ｼ閾ｪ霄ｫ縺碁囿螳ｳ迚ｩ縺ｫ陦晉ｪ√＠縺溷ｴ蜷医∝屓驕ｿ繝壹リ繝ｫ繝・ぅ縺ｨ縺励※繝繝｡繝ｼ繧ｸ繧剃ｸ弱∴繧・
        if (parent->GetTag() == kTag2dPlayer)
        {
            Player* p = dynamic_cast<Player*>(parent);
            if (p)
            {
                p->TakeDamage(2);
            }
        }
    }
}




