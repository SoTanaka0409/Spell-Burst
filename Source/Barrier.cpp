#include "Barrier.h"
#include "CapsuleCollider.h"
#include "DxLib.h"
#include "Utility.h"

Barrier::Barrier(float x, float y, float radius, Object2D::Tag2D obj)
    : Object2D(VGet(x, y, 0.0f))
    , mpCollider(nullptr)
{
    SetTag(obj); 
    m_deployInterval = 300.0f; // 5 seconds
    m_activeDuration = 180.0f; // 3 seconds
    m_timer = 0.0f;
    m_radius = radius;
    m_isDeployed = false;

}

Barrier::~Barrier() {
    if (mpCollider) {
        delete mpCollider;
        mpCollider = nullptr;
    }
}

void Barrier::Update() {
    m_timer += 1.0f * Utility::TimeScale;

    if (!m_isDeployed) {
        if (m_timer >= m_deployInterval) {
            m_isDeployed = true;
            m_timer = 0.0f;
            mpCollider = new CapsuleCollider(this, mvPosition, mvPosition, m_radius);
        }
    } else {
        if (m_timer >= m_activeDuration) {
            m_isDeployed = false;
            m_timer = 0.0f;
           
            if (mpCollider)
            {
                mpCollider->mvPosition = mvPosition;
                mpCollider->mvPosition2 = mvPosition;
            }
            if (mpCollider) {
                mpCollider->SetDeleteFlag(true);
                mpCollider = nullptr;
            }
        }
    }

    if (mpCollider) {
        mpCollider->mvPosition = mvPosition;
        mpCollider->mvPosition2 = mvPosition;
    }
}

void Barrier::Draw() {
    if (m_isDeployed) {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), static_cast<int>(m_radius), GetColor(0, 150, 255), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), static_cast<int>(m_radius), GetColor(150, 255, 255), FALSE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
}

void Barrier::OnTrigger(Collider* collider, Collider* check) {
    if (!m_isDeployed) return;

    if (check != nullptr && check->GetParentObject() != nullptr) {
        auto tag = check->GetParentObject()->GetTag();
        
        // プレイヤーのバリアなら敵の弾のみを消す
        if (GetTag() == tag2D_BarierPla && tag == Tag2D_EnemyBullet) {
            check->GetParentObject()->SetDeleteFlag(true);
        }
        // 敵のバリアならプレイヤーの弾のみを消す
        else if (GetTag() == tag2D_BarierEne && tag == Tag2D_PlayerBullet) {
            check->GetParentObject()->SetDeleteFlag(true);
        }
    }
}
