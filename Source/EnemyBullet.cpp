#include "EnemyBullet.h"
#include "CapsuleCollider.h"
#include "Player.h"
#include "Master.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ObjectManager.h"
#include <DxLib.h>
#include <cmath>
#include "utility.h"

EnemyBullet::EnemyBullet(float x, float y, float dx, float dy, float speed, bool canReflect, bool isStunBullet, int homingFrames, int homingDelayFrames)
    : Object2D(VGet(x, y, 0.0f))
    , mpCollider(nullptr)
{
    SetTag(Tag2D_EnemyBullet);// / Important: so it hits the player!
<<<<<<< HEAD
    m_x = x;
    m_y = y;
=======
    mvPosition.x = x;
    mvPosition.y = y;
>>>>>>> main
    m_dx = dx;
    m_dy = dy;
    m_speed = speed;
    m_isActive = true;
<<<<<<< HEAD
    m_canReflect = false; // ユーザーの要望により跳ね返り（反射）を無効化
=======
    m_canReflect = false; // ユーザーの要望により跳ね返り�E�反封E��を無効匁E
>>>>>>> main
    m_hasReflected = false;
    m_isStunBullet = isStunBullet;
    m_homingTimer = homingFrames;
    m_homingDelayTimer = homingDelayFrames;

    // Normalize direction vector just in case
    float len = std::sqrt(m_dx * m_dx + m_dy * m_dy);
    if (len > 0.0f) {
        m_dx /= len;
        m_dy /= len;
    } else {
        m_dx = 0.0f;
        m_dy = 1.0f;
    }

    mpCollider = new CapsuleCollider(this, mvPosition, mvPosition, 10.0f);
}

EnemyBullet::~EnemyBullet() {
    if (mpCollider) {
        delete mpCollider;
        mpCollider = nullptr;
    }
}

<<<<<<< HEAD
// 毎フレーム呼ばれる更新処理
// 指定されたベクトル方向へ弾を移動させ、画面外に出たら削除フラグを立てます。
=======
// 毎フレーム呼ばれる更新処琁E
// 持E��されたベクトル方向へ弾を移動させ、画面外に出たら削除フラグを立てます、E
>>>>>>> main
void EnemyBullet::Update() {
    if (m_homingDelayTimer > 0) {
        m_homingDelayTimer--;
    } else if (m_homingTimer > 0) {
        m_homingTimer--;
        Player* player = dynamic_cast<Player*>(Master::sceneManager->GetCurrentScene()->GetObjectManager()->GetObject2DByTag(Tag2D_Player));
        if (player) {
            float currentAngle = std::atan2(m_dy, m_dx);
<<<<<<< HEAD
            float targetAngle = std::atan2(player->GetY() - m_y, player->GetX() - m_x);
            
            float diff = targetAngle - currentAngle;
            // 角度を -PI ~ PI に正規化
            while (diff > 3.14159265f) diff -= 2.0f * 3.14159265f;
            while (diff < -3.14159265f) diff += 2.0f * 3.14159265f;
            
            // 旋回速度（例: 毎フレーム 0.05 ラジアン）
=======
            float targetAngle = std::atan2(player->GetY() - mvPosition.y, player->GetX() - mvPosition.x);
            
            float diff = targetAngle - currentAngle;
            // 角度めE-PI ~ PI に正規化
            while (diff > 3.14159265f) diff -= 2.0f * 3.14159265f;
            while (diff < -3.14159265f) diff += 2.0f * 3.14159265f;
            
            // 旋回速度�E�侁E 毎フレーム 0.05 ラジアン�E�E
>>>>>>> main
            float turnSpeed = 0.03f; 
            if (diff > turnSpeed) diff = turnSpeed;
            if (diff < -turnSpeed) diff = -turnSpeed;
            
            currentAngle += diff;
            m_dx = std::cos(currentAngle);
            m_dy = std::sin(currentAngle);
        }
    }

<<<<<<< HEAD
    m_x += m_dx * m_speed;
    m_y += m_dy * m_speed;
    mvPosition = VGet(m_x, m_y, 0.0f);
=======
    mvPosition.x += m_dx * m_speed * Utility::TimeScale;
    mvPosition.y += m_dy * m_speed * Utility::TimeScale;
    mvPosition = VGet(mvPosition.x, mvPosition.y, 0.0f);
>>>>>>> main

    if (mpCollider) {
        mpCollider->mvPosition = mvPosition;
        mpCollider->mvPosition2 = mvPosition;
    }

<<<<<<< HEAD
    // 画面外に出たら削除する（跳ね返り処理は無効化されました）
    if (m_x < -50.0f || m_x > Utility::SCREEN_WIDTH + 50.0f || m_y < -50.0f || m_y > Utility::SCREEN_HEIGHT + 50.0f) {
=======
    // 画面外に出たら削除する�E�跳ね返り処琁E�E無効化されました�E�E
    if (mvPosition.x < -50.0f || mvPosition.x > Utility::SCREEN_WIDTH + 50.0f || mvPosition.y < -50.0f || mvPosition.y > Utility::SCREEN_HEIGHT + 50.0f) {
>>>>>>> main
        m_isActive = false;
        SetDeleteFlag(true);
    }
}

<<<<<<< HEAD
// 描画処理
// 敵弾の画像を描画します。
=======
// 描画処琁E
// 敵弾の画像を描画します、E
>>>>>>> main
void EnemyBullet::Draw() {
    if (!m_isActive) return;
    
    if (m_isStunBullet) {
        // スタン弾は水色系
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
<<<<<<< HEAD
        DrawCircle(static_cast<int>(m_x), static_cast<int>(m_y), 14, GetColor(0, 150, 255), TRUE); // オーラ
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        DrawCircle(static_cast<int>(m_x), static_cast<int>(m_y), 10, GetColor(0, 255, 255), TRUE); // 外枠
        DrawCircle(static_cast<int>(m_x), static_cast<int>(m_y), 6, GetColor(255, 255, 255), TRUE); // コア
    } else {
        // 通常の敵弾（弾幕用）はマゼンタ／赤系
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
        DrawCircle(static_cast<int>(m_x), static_cast<int>(m_y), 14, GetColor(255, 0, 128), TRUE); // オーラ
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        DrawCircle(static_cast<int>(m_x), static_cast<int>(m_y), 10, GetColor(255, 100, 200), TRUE); // 外枠
        DrawCircle(static_cast<int>(m_x), static_cast<int>(m_y), 6, GetColor(255, 255, 255), TRUE); // コア
    }
}

void EnemyBullet::OnTrigger(Collider* collider, Collider* check) {
=======
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 14, GetColor(0, 150, 255), TRUE); // オーラ
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 10, GetColor(0, 255, 255), TRUE); // 外枠
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 6, GetColor(255, 255, 255), TRUE); // コア
    } else {
        // 通常の敵弾�E�弾幕用�E��Eマゼンタ�E�赤系
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 14, GetColor(255, 0, 128), TRUE); // オーラ
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 10, GetColor(255, 100, 200), TRUE); // 外枠
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 6, GetColor(255, 255, 255), TRUE); // コア
    }
}

void EnemyBullet::OnTrigger(Collider* collider, Collider* check) 
{
    if(check!=nullptr&&check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == tag2D_BarierPla)
        {
          
            Kill();
			return;//player�ƃo���A�ɓ����ɓ����������Ƀo���A�ɓ����������Ƃ�D�悳���邽�߁A�v���C���[�ւ̃_���[�W�������X�L�b�v
        }
	}
>>>>>>> main
    if (check != nullptr && check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == Tag2D_Player) {
            Player* player = dynamic_cast<Player*>(check->GetParentObject());
            if (player != nullptr) {
                player->TakeDamage(1);
                if (m_isStunBullet) {
                    player->Stun(60); // 1秒間スタン
                }
            }
<<<<<<< HEAD
            m_isActive = false;
            SetDeleteFlag(true);
            if (mpCollider) {
                mpCollider->SetDeleteFlag(true);
            }
        }
    }
}
=======
            Kill();
        }
    }
}

void EnemyBullet::Kill() 
{
    m_isActive = false;
    SetDeleteFlag(true);
    if (mpCollider) {
        mpCollider->SetDeleteFlag(true);
    }
}
>>>>>>> main
