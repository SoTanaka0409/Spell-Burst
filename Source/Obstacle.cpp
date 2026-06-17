#include "Obstacle.h"
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
    , mpCollider(nullptr)
    , m_fallSpeed(3.0f)
{
    SetTag(Tag2D_Enemy); // プレイヤーの弾や体当たり判定の対象とするため便宜上敵タグを付与
    mpCollider = new CapsuleCollider(this, mvPosition, mvPosition, 40.0f);
}

Obstacle::~Obstacle() {
    if (mpCollider) {
        delete mpCollider;
        mpCollider = nullptr;
    }
}

void Obstacle::Update() {
    mvPosition.y += m_fallSpeed * Utility::TimeScale;
    
    if (mpCollider) {
        mpCollider->mvPosition = mvPosition;
        mpCollider->mvPosition2 = mvPosition;
    }

    if (mvPosition.y > Utility::SCREEN_HEIGHT + 100.0f) {
        SetDeleteFlag(true);
        if (mpCollider) {
            mpCollider->SetDeleteFlag(true);
        }
    }
}

void Obstacle::Draw() {
    int graph = ResourceManager::GetInstance()->GetGraph("Resource/rock.png");
    if (graph != -1) {
        DrawExtendGraph(
            static_cast<int>(mvPosition.x - 45.0f),
            static_cast<int>(mvPosition.y - 45.0f),
            static_cast<int>(mvPosition.x + 45.0f),
            static_cast<int>(mvPosition.y + 45.0f),
            graph, TRUE
        );
    } else {
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 40, GetColor(100, 100, 100), TRUE);
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 38, GetColor(80, 80, 80), TRUE);
    }
}

void Obstacle::OnTrigger(Collider* collider, Collider* check) {
    if (check != nullptr && check->GetParentObject() != nullptr) {
        Object2D* parent = check->GetParentObject();
        // プレイヤー側の攻撃と衝突した場合の処理（特殊弾かどうかで分岐）
        if (parent->GetTag() == Tag2D_PlayerBullet) {
            bool isSpecial = false;
            if (dynamic_cast<MasterSpark*>(parent) != nullptr ||
                dynamic_cast<RainbowBullet*>(parent) != nullptr ||
                dynamic_cast<SpellCardBullet*>(parent) != nullptr ||
                dynamic_cast<SpecialBullet*>(parent) != nullptr) {
                isSpecial = true;
            }

            if (isSpecial) {
                this->SetDeleteFlag(true);
                if (mpCollider) mpCollider->SetDeleteFlag(true);
                SoundManager::GetInstance()->PlaySE("Resource/se_enemy_die.wav");
                for (int i = 0; i < 5; i++) {
                    new ExplosionParticle(mvPosition.x, mvPosition.y, 2.0f, static_cast<float>(rand() % 360) * 3.14159f / 180.0f, GetColor(150, 150, 150), 30, 10.0f);
                }
            } else {
                parent->SetDeleteFlag(true);
                check->SetDeleteFlag(true);
            }
        }
        // プレイヤー自身が障害物に衝突した場合、回避ペナルティとしてダメージを与える
        if (parent->GetTag() == Tag2D_Player) {
            Player* p = dynamic_cast<Player*>(parent);
            if (p) {
                p->TakeDamage(2);
            }
        }
    }
}
