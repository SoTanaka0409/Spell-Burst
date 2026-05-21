#include "Enemy.h"
#include "CapsuleCollider.h"
#include <DxLib.h>
#include "Bullet.h"
#include "EnemyBullet.h"
#include "Player.h"
#include "Master.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "Utility.h"
#include <cmath>

Enemy::Enemy(float x, float y, int enemyType) 
    : Object2D(VGet(x, y, 0.0f))
    , mpCollider(nullptr)
{
    SetTag(Tag2D_Enemy);
    m_x = x;
    m_y = y;
    m_isActive = true;
    m_enemyType = enemyType;
    m_attackTimer = 0;

    if (m_enemyType == 1) {
        m_speed = 3.0f;
        m_maxHp = 3;
    } else if (m_enemyType == 2) {
        m_speed = 2.0f;
        m_maxHp = 5;
    } else {
        m_speed = 1.5f;
        m_maxHp = 8;
    }
    m_hp = m_maxHp;

    // Create a circular collider with radius 35
    mpCollider = new CapsuleCollider(this, mvPosition, mvPosition, 35.0f);
}

Enemy::~Enemy() {
    if (mpCollider) {
        delete mpCollider;
        mpCollider = nullptr;
    }
}

// 毎フレーム呼ばれる更新処理
// 敵を下方向に移動させ、画面外に出たら活動停止・削除フラグを立てます。
void Enemy::Update() {
    m_y += m_speed;
    mvPosition = VGet(m_x, m_y, 0.0f);

    if (mpCollider) {
        mpCollider->mvPosition = mvPosition;
        mpCollider->mvPosition2 = mvPosition;
    }

    // 種類2, 3の場合は定期的にプレイヤーへ向けて弾を撃つ
    if (m_enemyType == 2 || m_enemyType == 3) {
        m_attackTimer++;
        if (m_attackTimer >= 150) { // 2.5秒ごと
            m_attackTimer = 0;
            Player* player = dynamic_cast<Player*>(Master::sceneManager->GetCurrentScene()->GetObjectManager()->GetObject2DByTag(Tag2D_Player));
            float targetX = m_x;
            float targetY = m_y + 100.0f;
            if (player != nullptr) {
                targetX = player->GetX();
                targetY = player->GetY();
            }
            float dx = targetX - m_x;
            float dy = targetY - m_y;
            float dist = std::sqrt(dx * dx + dy * dy);
            if (dist > 0.0f) {
                dx /= dist;
                dy /= dist;
            } else {
                dx = 0.0f;
                dy = 1.0f;
            }
            
            if (m_enemyType == 2) {
                new EnemyBullet(m_x, m_y, dx, dy, 4.0f, false, false); // 通常弾
            } else if (m_enemyType == 3) {
                new EnemyBullet(m_x, m_y, dx, dy, 3.5f, false, true); // スタン弾
            }
        }
    }

    if (m_y > Utility::SCREEN_HEIGHT + 50.0f) {
        m_isActive = false;
        SetDeleteFlag(true);
    }
}

// 敵の消滅処理
// 活動フラグをオフにし、オブジェクト管理システムに削除されるようフラグを立てます。
void Enemy::Kill() {
    m_isActive = false;
    SetDeleteFlag(true);
    if (mpCollider) {
        mpCollider->SetDeleteFlag(true);
    }
}


// ダメージを受ける処理
// プレイヤーの攻撃と当たった際に呼ばれ、HPを減らします。0以下になったら消滅処理(Kill)を呼びます。
void Enemy::TakeDamage(int damage) {
    m_hp -= damage;
    if (m_hp <= 0) {
        m_hp = 0;
        Kill();
    }
}

// 他のオブジェクトと重なっている時の処理（当たり判定イベント）
// プレイヤーの弾（通常弾、近接、必殺技）と当たった場合に、自身のTakeDamageを呼び出します。
void Enemy::OnTrigger(Collider* collider, Collider* check) {
    if (check != nullptr && check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == Tag2D_PlayerBullet) {
            Bullet* bullet = dynamic_cast<Bullet*>(check->GetParentObject());
            if (bullet != nullptr) {
                TakeDamage(bullet->GetDamage());
                bullet->Kill(); // Destroy the bullet on impact
            }
        }
    }
}

// 描画処理
// 敵自身の画像を描画し、頭上にHPバーを表示します。
void Enemy::Draw() 
{
    if (!m_isActive) return;

    static int s_enemyGraphHandle = -1;
    if (s_enemyGraphHandle == -1) {
        s_enemyGraphHandle = LoadGraph("Resource/enemy.png");
    }

    if (s_enemyGraphHandle != -1) {
        // タイプによって色を変える
        if (m_enemyType == 1) SetDrawBright(255, 255, 255);
        else if (m_enemyType == 2) SetDrawBright(255, 200, 100);
        else if (m_enemyType == 3) SetDrawBright(100, 100, 255);

        DrawExtendGraph(
            static_cast<int>(mvPosition.x - 35.0f), 
            static_cast<int>(mvPosition.y - 35.0f), 
            static_cast<int>(mvPosition.x + 35.0f), 
            static_cast<int>(mvPosition.y + 35.0f), 
            s_enemyGraphHandle, 
            TRUE
        );

        SetDrawBright(255, 255, 255); // 色を元に戻す
    } else {
        unsigned int color = GetColor(255, 100, 100);
        if (m_enemyType == 2) color = GetColor(255, 200, 100);
        else if (m_enemyType == 3) color = GetColor(100, 100, 255);
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 35, color, TRUE);
    }

    // Draw HP text above enemy
    DrawFormatString(static_cast<int>(mvPosition.x) - 15, static_cast<int>(mvPosition.y) - 55, GetColor(255, 255, 255), "HP:%d", m_hp);
}
