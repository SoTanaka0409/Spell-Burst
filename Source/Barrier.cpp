#include "Barrier.h"
#include "CapsuleCollider.h"
#include "DxLib.h"
#include "Utility.h"
#include "PlayerHomingBullet.h"
#include "SoundManager.h"
#include <cmath>

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
    m_hitCount = 0;
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
            SoundManager::GetInstance()->PlaySE("Resource/se_barrier.wav");
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
        if (GetTag() == tag2D_BarierPla && tag == Tag2D_EnemyBullet)
        {
            check->GetParentObject()->SetDeleteFlag(true);
            m_hitCount++;
            
            // 5発防いだらカウンター発動！
            if (m_hitCount >= 50) {
                m_hitCount = 0; // カウントリセット
                
                // 四方向に10発ずつ（計40発）放出
                float baseSpeed = 10.0f; // 少し速めに設定
                for (int dir = 0; dir < 4; ++dir) {
                    float baseAngle = dir * (3.14159265f / 2.0f); // 0, 90, 180, 270度
                    for (int i = 0; i < 10; ++i) {
                        // 各方向で扇状に少しずつ角度をずらして発射 (-0.45 ～ +0.45 ラジアン)
                        float spread = (i - 4.5f) * 0.1f; 
                        float angle = baseAngle + spread;
                        
                        float dx = std::cos(angle);
                        float dy = std::sin(angle);
                        
                        // バリアの中心から少し離した位置から発生させる
                        new PlayerHomingBullet(mvPosition.x + dx * 30.0f, mvPosition.y + dy * 30.0f, dx, dy, baseSpeed);
                    }
                }
            }
        }
        // 敵のバリアならプレイヤーの弾のみを消す
        else if (GetTag() == tag2D_BarierEne && tag == Tag2D_PlayerBullet) {
            check->GetParentObject()->SetDeleteFlag(true);
        }
       
    }
}
