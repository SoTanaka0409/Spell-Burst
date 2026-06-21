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
    : Character(Vector2(x, y), 3, 3.0f)
{
    SetTag(Tag2D_Enemy);
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
        m_maxHp = 20; // 中ボス
        SelectNewTarget();
    }
    m_hp = m_maxHp;
    
    if (mpCollider) delete mpCollider;
    float colRadius = (m_enemyType == 4) ? 45.0f : 35.0f;
    mpCollider = new CapsuleCollider(this, mvPosition, mvPosition, colRadius);
}

Enemy::~Enemy() {
}

void Enemy::Update() {
    Character::Update(); // スタン時間の減少など

    if (m_stunTimer > 0) return; // スタン中は行動不能

    if (m_enemyType == 4) {
        Vector2 target(m_targetX, m_targetY);
        float dist = mvPosition.DistanceTo(target);

        if (dist < 15.0f) {
            SelectNewTarget();
        }
        else {
            mvPosition += (target - mvPosition).Normalized() * (m_speed * Utility::TimeScale);
        }
    }
    else {
        mvPosition.y += m_speed * Utility::TimeScale;
    }

    if (m_enemyType == 2 || m_enemyType == 3 || m_enemyType == 4) 
    {
        m_attackTimer++;
        int interval = (m_enemyType == 4) ? 120 : 150; 
        if (m_attackTimer >= interval)
        {
            m_attackTimer = 0;
            Player* player = dynamic_cast<Player*>(Master::sceneManager->GetCurrentScene()->GetObjectManager()->GetObject2DByTag(Tag2D_Player));
            Vector2 targetPos(mvPosition.x, mvPosition.y + 100.0f);
            if (player != nullptr) {
                targetPos = Vector2(player->GetX(), player->GetY());
            }
            Vector2 dir = (targetPos - mvPosition).Normalized();
            if (dir.MagnitudeSq() == 0.0f) {
                dir = Vector2(0.0f, 1.0f);
            }
            if (m_enemyType == 2) {
                new EnemyBullet(mvPosition, dir, 4.0f, false, false);
            }
            else if (m_enemyType == 3) {
                new EnemyBullet(mvPosition, dir, 3.5f, false, true);  
            }
            else if (m_enemyType == 4) {
                static float mbAngle = 0.0f;
                mbAngle += 0.2f;
                for (int i = 0; i < 4; i++) {
                    float angle = mbAngle + (i * 2.0f * 3.14159265f) / 16;
                    new EnemyBullet(mvPosition, Vector2::FromAngle(angle), 2.0f);
                }
                float baseAngle = mvPosition.AngleTo(targetPos);
                for (int i = -1; i <= 1; i++) {
                    float angle = baseAngle + (i * 8.0f * 3.14159265f / 180.0f);
                    new EnemyBullet(mvPosition, Vector2::FromAngle(angle), 3.5f);
                }
            }
        }
    }
    
    if (mvPosition.y > Utility::SCREEN_HEIGHT + 50.0f) {
        Character::Kill();
    }
}

void Enemy::Kill() {
    Character::Kill();
}

void Enemy::TakeDamage(int damage) {
    if (!m_isActive) return;

    Character::TakeDamage(damage); // HPを減らし、0になったらKillを呼ぶ処理など

    if (m_hp <= 0) {
        SoundManager::GetInstance()->PlaySE("Resource/se_enemy_die.wav");
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
                bullet->Kill(); 
            }
        }
    }
}

void Enemy::Draw()
{
    if (!m_isActive) return;

    if (m_stunTimer > 0) {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 45, GetColor(0, 200, 255), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }

    int s_enemyGraphHandle = ResourceManager::GetInstance()->GetGraph("Resource/enemy.png");

    if (s_enemyGraphHandle != -1) {
        if (m_enemyType == 1) SetDrawBright(255, 255, 255);
        else if (m_enemyType == 2) SetDrawBright(255, 200, 100);
        else if (m_enemyType == 3) SetDrawBright(100, 100, 255);
        else if (m_enemyType == 4) SetDrawBright(255, 50, 50);

        float drawSize = (m_enemyType == 4) ? 45.0f : 35.0f;
        DrawExtendGraph(
            static_cast<int>(mvPosition.x - drawSize),
            static_cast<int>(mvPosition.y - drawSize),
            static_cast<int>(mvPosition.x + drawSize),
            static_cast<int>(mvPosition.y + drawSize),
            s_enemyGraphHandle,
            TRUE
        );

        SetDrawBright(255, 255, 255);
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