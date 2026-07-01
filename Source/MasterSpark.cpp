#include "MasterSpark.h"
#include "CapsuleCollider.h"
#include "Enemy.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include "Utility.h"
#include "Master.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ObjectManager.h"
#include "Player.h"
#include <cmath>
#include <cstdlib>

MasterSpark::MasterSpark(float x, float y)
    : Projectile(Vector2(x, y), Vector2(0, -1), 0.0f, 3) // ★ダメージを3に調整
{
    SetTag(Tag2D_PlayerBullet);
    m_maxLife = 120;
    m_lifeTimer = m_maxLife;
    m_radius = 120.0f; // ★エフェクトを大幅に大きく
    m_colorHue = 0;
    m_AttackCount = 0;

    mpCollider = new CapsuleCollider(this, Vector2(mvPosition.x, mvPosition.y), Vector2(mvPosition.x, mvPosition.y - 1200.0f), m_radius);
}

MasterSpark::~MasterSpark() {
}

void MasterSpark::Update() {
    m_lifeTimer--;
    if (m_lifeTimer <= 0) {
        Projectile::Kill(); // 寿命が来たら消滅
        return;
    }

    // ★プレイヤーの位置を取得して追尾する処理
    Player* player = dynamic_cast<Player*>(
        Master::sceneManager->GetCurrentScene()->GetObjectManager()->GetObject2DByTag(Tag2D_Player)
    );
    if (player != nullptr) {
        mvPosition.x = player->GetX();
        mvPosition.y = player->GetY() - 45.0f; // プレイヤーの少し上から発射
    }

    float target_radius = 120.0f;
    if (m_lifeTimer < 20) {
        m_radius = target_radius * (m_lifeTimer / 20.0f);
    } else if (m_maxLife - m_lifeTimer < 10) {
        m_radius = target_radius * ((m_maxLife - m_lifeTimer) / 10.0f);
    } else {
        m_radius = target_radius;
    }

    // ★荒ぶるようなランダムな振動（ノイズ）を加えて迫力を出す
    m_radius += (rand() % 20 - 10) * 0.5f;

    m_colorHue += 15;
    if (m_colorHue >= 360) m_colorHue -= 360;

    if (mpCollider) {
        mpCollider->mvPosition = Vector2(mvPosition.x, mvPosition.y);
        mpCollider->mvPosition2 = Vector2(mvPosition.x, mvPosition.y - 1200.0f);
        mpCollider->mfRadius = m_radius; // コライダーのサイズも動的に変更
    }
}

void MasterSpark::Draw() {
    if (!m_isActive) return;

    // ★激しい閃光のようなエフェクト（外側のオーラ）
    SetDrawBlendMode(DX_BLENDMODE_ADD, 180);
    for (int i = 0; i < 7; ++i) {
        float rad = (m_colorHue + i * 50) * 3.14159265f / 180.0f;
        int r = static_cast<int>(sin(rad) * 127 + 128);
        int g = static_cast<int>(sin(rad + 2.0f * 3.14159265f / 3.0f) * 127 + 128);
        int b = static_cast<int>(sin(rad + 4.0f * 3.14159265f / 3.0f) * 127 + 128);

        float drawRadius = m_radius * (1.0f - i * 0.12f) + (rand() % 15);
        float offset_x = (rand() % 10 - 5) * 0.5f; // 微小な揺れ

        DrawBox(static_cast<int>(mvPosition.x - drawRadius + offset_x), static_cast<int>(mvPosition.y - 1200.0f),
                static_cast<int>(mvPosition.x + drawRadius + offset_x), static_cast<int>(mvPosition.y), GetColor(r, g, b), TRUE);
        DrawCircle(static_cast<int>(mvPosition.x + offset_x), static_cast<int>(mvPosition.y), static_cast<int>(drawRadius), GetColor(r, g, b), TRUE);
    }

    // ★中心の強烈な光（コア）
    SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
    float innerRadius = m_radius * 0.4f + (rand() % 10);
    DrawBox(static_cast<int>(mvPosition.x - innerRadius), static_cast<int>(mvPosition.y - 1200.0f),
            static_cast<int>(mvPosition.x + innerRadius), static_cast<int>(mvPosition.y), GetColor(255, 255, 255), TRUE);
    DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), static_cast<int>(innerRadius), GetColor(255, 255, 255), TRUE);

    // ★さらに中心を貫く細い線（超高熱の芯）
    float coreRadius = m_radius * 0.15f;
    DrawBox(static_cast<int>(mvPosition.x - coreRadius), static_cast<int>(mvPosition.y - 1200.0f),
            static_cast<int>(mvPosition.x + coreRadius), static_cast<int>(mvPosition.y), GetColor(200, 255, 255), TRUE);

    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void MasterSpark::Kill() {
    // 貫通レーザーなので衝突で消滅しない
}

void MasterSpark::OnTrigger(Collider* collider, Collider* check) {
    if (check != nullptr && check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == Tag2D_Enemy) {
            Character* enemy = dynamic_cast<Character*>(check->GetParentObject());
            // ★ヒット間隔を短くし（毎フレーム等）、ダメージを与えやすくする
            if (enemy != nullptr && m_lifeTimer % 2 == 0) {
                enemy->TakeDamage(m_damage);
                m_AttackCount++;
            }
        } else if (check->GetParentObject()->GetTag() == Tag2D_EnemyBullet) {
            check->GetParentObject()->SetDeleteFlag(true);
        }
    }
}

void MasterSpark::OnEnter(Collider* collider, Collider* check) {
}