#include "Enemy.h"
#include "CapsuleCollider.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include "Bullet.h"
#include "EnemyBullet.h"
#include "Player.h"
#include "Master.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "Utility.h"
#include "ResourceManager.h"
#include "GameScene.h"
#include "EnemyManager.h"
#include "SoundManager.h"
#include <cmath>
#include <cstdlib>
void Enemy::SelectNewTarget() {
    m_targetX = 100.0f + static_cast<float>(rand() % 1080);
    m_targetY = 80.0f + static_cast<float>(rand() % 180);
}
Enemy::Enemy(float x, float y, int enemyType)
    : Object2D(VGet(x, y, 0.0f))
    , mpCollider(nullptr)
{
    SetTag(Tag2D_Enemy);
    mvPosition.x = x;
    mvPosition.y = y;
    m_isActive = true;
    m_enemyType = enemyType;
    m_attackTimer = 0;
    if (m_enemyType == 1) {
        m_speed = 3.0f;
        m_maxHp = 3;
    }
    else if (m_enemyType == 2) {
        m_speed = 2.0f;
        m_maxHp = 5;
    }
    else if (m_enemyType == 3) {
        m_speed = 1.5f;
        m_maxHp = 8;
    }
    else if (m_enemyType == 4) {
        m_speed = 2.5f;
        m_maxHp = 20; // 中ボスはタフ
        SelectNewTarget();
    }
    m_hp = m_maxHp;
    float colRadius = (m_enemyType == 4) ? 45.0f : 35.0f;
    mpCollider = new CapsuleCollider(this, mvPosition, mvPosition, colRadius);
}
Enemy::~Enemy() {
    if (mpCollider) {
        delete mpCollider;
        mpCollider = nullptr;
    }
}
void Enemy::Update() {
    if (m_enemyType == 4) {
        float dx = m_targetX - mvPosition.x;
        float dy = m_targetY - mvPosition.y;
        float dist = std::sqrt(dx * dx + dy * dy);

        if (dist < 15.0f) {
            SelectNewTarget();
        }
        else {
            mvPosition.x += (dx / dist) * m_speed * Utility::TimeScale;
            mvPosition.y += (dy / dist) * m_speed * Utility::TimeScale;
        }
    }
    else {
        mvPosition.y += m_speed * Utility::TimeScale;
    }
    mvPosition = VGet(mvPosition.x, mvPosition.y, 0.0f);
    if (mpCollider) {
        mpCollider->mvPosition = mvPosition;
        mpCollider->mvPosition2 = mvPosition;
    }
    if (m_enemyType == 2 || m_enemyType == 3 || m_enemyType == 4) 
    {
        m_attackTimer++;
        int interval = (m_enemyType == 4) ? 120 : 150; // 中ボスは頻繁に撃つ
        if (m_attackTimer >= interval)
        {
            
            m_attackTimer = 0;
            Player* player = dynamic_cast<Player*>(Master::sceneManager->GetCurrentScene()->GetObjectManager()->GetObject2DByTag(Tag2D_Player));
            float targetX = mvPosition.x;
            float targetY = mvPosition.y + 100.0f;
            if (player != nullptr) {
                targetX = player->GetX();
                targetY = player->GetY();
            }
            float dx = targetX - mvPosition.x;
            float dy = targetY - mvPosition.y;
            float dist = std::sqrt(dx * dx + dy * dy);
            if (dist > 0.0f) {
                dx /= dist;
                dy /= dist;
            }
            else {
                dx = 0.0f;
                dy = 1.0f;
            }
            if (m_enemyType == 2) {
                new EnemyBullet(mvPosition.x, mvPosition.y, dx, dy, 4.0f, false, false); // 通常弾
            }
            else if (m_enemyType == 3) {
                new EnemyBullet(mvPosition.x, mvPosition.y, dx, dy, 3.5f, false, true);  // スタン弾
            }
            else if (m_enemyType == 4) {
                static float mbAngle = 0.0f;
                mbAngle += 0.2f;
                for (int i = 0; i < 4; i++) {
                    float angle = mbAngle + (i * 2.0f * 3.14159265f) / 16;
                    new EnemyBullet(mvPosition.x, mvPosition.y, std::cos(angle), std::sin(angle), 2.0f);
                }
                float baseAngle = std::atan2(dy, dx);
                for (int i = -1; i <= 1; i++) {
                    float angle = baseAngle + (i * 8.0f * 3.14159265f / 180.0f);
                    new EnemyBullet(mvPosition.x, mvPosition.y, std::cos(angle), std::sin(angle), 3.5f);
                }
            }
        }
    }
    if (mvPosition.y > Utility::SCREEN_HEIGHT + 50.0f) {
        m_isActive = false;
        SetDeleteFlag(true);
    }
}
void Enemy::Kill() {
    m_isActive = false;
    SetDeleteFlag(true);
    if (mpCollider) {
        mpCollider->SetDeleteFlag(true);
    }
}
void Enemy::TakeDamage(int damage) {
    if (!m_isActive) return;

    m_hp -= damage;
    if (m_hp <= 0) {
        m_hp = 0;
        SoundManager::GetInstance()->PlaySE("Resource/se_enemy_die.wav");
        Kill();
        Player* player = dynamic_cast<Player*>(
            Master::sceneManager->GetCurrentScene()->GetObjectManager()->GetObject2DByTag(Object2D::Tag2D_Player)
        );
        if (player != nullptr) {
            player->AddXp(1);
        }
        GameScene* gs = dynamic_cast<GameScene*>(Master::sceneManager->GetCurrentScene());
        if (gs != nullptr && gs->GetEnemyManager() != nullptr) {
            gs->GetEnemyManager()->AddDefeatedCount();
        }
    }
}
void Enemy::OnTrigger(Collider* collider, Collider* check) {
    if (check != nullptr && check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == Tag2D_PlayerBullet) {
            Bullet* bullet = dynamic_cast<Bullet*>(check->GetParentObject());
            if (bullet != nullptr) {
                TakeDamage(bullet->GetDamage());
                bullet->Kill(); // 当たったプレイヤーの弾を消滅させる

            }
        }
    }
}
void Enemy::Draw()
{
    if (!m_isActive) return;

    int s_enemyGraphHandle = ResourceManager::GetInstance()->GetGraph("Resource/enemy.png");

    if (s_enemyGraphHandle != -1) {
        if (m_enemyType == 1) SetDrawBright(255, 255, 255);
        else if (m_enemyType == 2) SetDrawBright(255, 200, 100);
        else if (m_enemyType == 3) SetDrawBright(100, 100, 255);
        else if (m_enemyType == 4) SetDrawBright(255, 50, 50); // 中ボスは赤っぽい

        float drawSize = (m_enemyType == 4) ? 45.0f : 35.0f;
        DrawExtendGraph(
            static_cast<int>(mvPosition.x - drawSize),
            static_cast<int>(mvPosition.y - drawSize),
            static_cast<int>(mvPosition.x + drawSize),
            static_cast<int>(mvPosition.y + drawSize),
            s_enemyGraphHandle,
            TRUE
        );

        SetDrawBright(255, 255, 255); // 輝度設定を元に戻す
    }
    else {
        unsigned int color = GetColor(255, 100, 100);
        if (m_enemyType == 2) color = GetColor(255, 200, 100);
        else if (m_enemyType == 3) color = GetColor(100, 100, 255);
        else if (m_enemyType == 4) color = GetColor(255, 50, 50);

        int drawRadius = (m_enemyType == 4) ? 45 : 35;
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), drawRadius, color, TRUE);
    }
    int hpOffset = (m_enemyType == 4) ? 65 : 55;
    DrawFormatString(static_cast<int>(mvPosition.x) - 15, static_cast<int>(mvPosition.y) - hpOffset, GetColor(255, 255, 255), "HP:%d", m_hp);
}