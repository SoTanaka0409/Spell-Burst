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
    SetTag(kTag2dEnemy); // プレイヤーの弾や体当たり判定の対象とするため便宜上敵タグを付与
    collider_ = new CapsuleCollider(this, position_, position_, 40.0f);
}

Obstacle::~Obstacle() {
    if (collider_) {
        delete collider_;
        collider_ = nullptr;
    }
}

void Obstacle::Update() {
    position_.y += fall_speed_ * Utility::TimeScale;
    
    if (collider_) {
        collider_->position_ = position_;
        collider_->position2 = position_;
    }

    if (position_.y > Utility::SCREEN_HEIGHT + 100.0f) {
        SetDeleteFlag(true);
        if (collider_) {
            collider_->SetDeleteFlag(true);
        }
    }
}

void Obstacle::Draw() {
    int graph = ResourceManager::GetInstance()->GetGraph("Resource/rock.png");
    if (graph != -1) {
        DrawExtendGraph(
            static_cast<int>(position_.x - 45.0f),
            static_cast<int>(position_.y - 45.0f),
            static_cast<int>(position_.x + 45.0f),
            static_cast<int>(position_.y + 45.0f),
            graph, TRUE
        );
    } else {
        DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 40, GetColor(100, 100, 100), TRUE);
        DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 38, GetColor(80, 80, 80), TRUE);
    }
}

void Obstacle::OnTrigger(Collider* collider_, Collider* check) {
    if (check != nullptr && check->GetParentObject() != nullptr) {
        Object2D* parent = check->GetParentObject();
        // プレイヤー側の攻撃と衝突した場合の処理（特殊弾かどうかで分岐）
        if (parent->GetTag() == kTag2dPlayerBullet) {
            bool isSpecial = false;
            if (dynamic_cast<MasterSpark*>(parent) != nullptr ||
                dynamic_cast<RainbowBullet*>(parent) != nullptr ||
                dynamic_cast<SpellCardBullet*>(parent) != nullptr ||
                dynamic_cast<SpecialBullet*>(parent) != nullptr) {
                isSpecial = true;
            }

            if (isSpecial) {
                this->SetDeleteFlag(true);
                if (collider_) collider_->SetDeleteFlag(true);
                SoundManager::GetInstance()->PlaySE("Resource/se_enemy_die.wav");
                for (int i = 0; i < 5; i++) {
                    ObjectManager::Instantiate<ExplosionParticle>(position_.x, position_.y, 2.0f, static_cast<float>(rand() % 360) * 3.14159f / 180.0f, GetColor(150, 150, 150), 30, 10.0f);
                }
            } else {
                parent->SetDeleteFlag(true);
                check->SetDeleteFlag(true);
            }
        }
        // プレイヤー自身が障害物に衝突した場合、回避ペナルティとしてダメージを与える
        if (parent->GetTag() == kTag2dPlayer) {
            Player* p = dynamic_cast<Player*>(parent);
            if (p) {
                p->TakeDamage(2);
            }
        }
    }
}




