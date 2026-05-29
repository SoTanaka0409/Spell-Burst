#include "MasterSpark.h"
#include "CapsuleCollider.h"
#include "Player.h"
#include "Enemy.h"
#include "Boss.h"
#include "Master.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "GameScene.h"
#include <DxLib.h>
#include <cmath>
#include <cstdlib>

MasterSpark::MasterSpark(float x, float y)
    : Object2D(VGet(x, y, 0.0f))
    , mpCollider(nullptr)
    , m_lifeTimer(180)
    , m_maxLife(180)
    , m_radius(10.0f)
    , m_damage(2) // 5 damage per frame means 300 damage per second (MASSIVE)
    , m_colorHue(0)
{
    SetTag(Tag2D_PlayerBullet);
    m_isActive = true;

    // Laser reaches up to y = -1000
    mpCollider = new CapsuleCollider(this, mvPosition, VGet(mvPosition.x, mvPosition.y - 1000.0f, 0.0f), m_radius);
}

MasterSpark::~MasterSpark() {
    if (mpCollider) {
        delete mpCollider;
        mpCollider = nullptr;
    }
}

void MasterSpark::Update() {
    if (!m_isActive) return;

    m_lifeTimer--;
    if (m_lifeTimer <= 0) {
        m_isActive = false;
        SetDeleteFlag(true);
        if (mpCollider) {
            mpCollider->SetDeleteFlag(true);
            mpCollider = nullptr; // Let ColliderManager handle deletion or do it safely
        }
        return;
    }

    // Continuously follow player position
    Player* player = dynamic_cast<Player*>(Master::sceneManager->GetCurrentScene()->GetObjectManager()->GetObject2DByTag(Tag2D_Player));
    if (player != nullptr) {
        mvPosition.x = player->GetX();
        mvPosition.y = player->GetY() - 30.0f; // Start slightly above the player
    }

    float progress = 1.0f - (static_cast<float>(m_lifeTimer) / static_cast<float>(m_maxLife));
    
    // Smooth expansion and shrinkage
    if (progress < 0.1f) {
        m_radius = 10.0f + (150.0f * (progress / 0.1f));
    } else if (progress > 0.9f) {
        m_radius = 160.0f * ((1.0f - progress) / 0.1f);
    } else {
        // Pulsate wildly while firing
        m_radius = 150.0f + (std::sin(progress * 3.14159f * 30.0f) * 15.0f);
    }

    if (mpCollider) {
        mpCollider->mvPosition = mvPosition;
        mpCollider->mvPosition2 = VGet(mvPosition.x, mvPosition.y - 1200.0f, 0.0f);
        mpCollider->mfRadius = m_radius;
    }

    // Screen shake while firing!
    GameScene* gs = dynamic_cast<GameScene*>(Master::sceneManager->GetCurrentScene());
    if (gs != nullptr) {
        gs->AddScreenShake(2, 5.0f + (m_radius / 30.0f));
    }

    m_colorHue = (m_colorHue + 15) % 360;
}

void MasterSpark::Draw() {
    if (!m_isActive) return;

    float radiusOuter = m_radius;
    float radiusMid = m_radius * 0.7f;
    float radiusInner = m_radius * 0.3f;

    // Red/Vermilion based colors for outer layer
    int mySparkR = 255;
    int mySparkG = static_cast<int>(std::sin(m_colorHue * 3.14159f / 180.0f) * 80 + 80);
    int mySparkB = 30;
    
    unsigned int colorOuter = GetColor(mySparkR, mySparkG, mySparkB);
    unsigned int colorMid = GetColor(255, 120, 30); // Orange-ish mid
    unsigned int colorInner = GetColor(255, 255, 200); // White/yellow core

    SetDrawBlendMode(DX_BLENDMODE_ADD, 150);
    DrawBox(static_cast<int>(mvPosition.x - radiusOuter), static_cast<int>(mvPosition.y - 1200.0f),
            static_cast<int>(mvPosition.x + radiusOuter), static_cast<int>(mvPosition.y),
            colorOuter, TRUE);
    DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), static_cast<int>(radiusOuter), colorOuter, TRUE);
    
    SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
    DrawBox(static_cast<int>(mvPosition.x - radiusMid), static_cast<int>(mvPosition.y - 1200.0f),
            static_cast<int>(mvPosition.x + radiusMid), static_cast<int>(mvPosition.y),
            colorMid, TRUE);
    DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), static_cast<int>(radiusMid), colorMid, TRUE);

    SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
    DrawBox(static_cast<int>(mvPosition.x - radiusInner), static_cast<int>(mvPosition.y - 1200.0f),
            static_cast<int>(mvPosition.x + radiusInner), static_cast<int>(mvPosition.y),
            colorInner, TRUE);
    DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), static_cast<int>(radiusInner), colorInner, TRUE);

    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void MasterSpark::OnTrigger(Collider* collider, Collider* check) {
    if (!m_isActive) return;

    if (check != nullptr && check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == Tag2D_Enemy) {
            // Apply continuous damage every frame!
            Object2D* obj = check->GetParentObject();
            Boss* boss = dynamic_cast<Boss*>(obj);
            if (boss != nullptr && boss->IsActive() && !boss->IsDeleteFlag()) {
                boss->TakeDamage(m_damage);
            } else {
                Enemy* enemy = dynamic_cast<Enemy*>(obj);
                if (enemy != nullptr && enemy->IsActive() && !enemy->IsDeleteFlag()) {
                    enemy->TakeDamage(m_damage);
                }
            }
        } else if (check->GetParentObject()->GetTag() == Tag2D_EnemyBullet) {
            // 敵の弾を消す
            check->GetParentObject()->SetDeleteFlag(true);
        }
    }
}
