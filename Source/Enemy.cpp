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
    targetX = 100.0f + static_cast<float>(rand() % 1080);
    targetY = 80.0f + static_cast<float>(rand() % 180);
}

Enemy::Enemy(float x, float y, int enemyType)
    : Character(Vector2(x, y), 3, 3.0f)
{
    SetTag(Tag2D_Enemy);
    enemyType = enemyType;
    attackTimer = 0;
    
    if (enemyType == 1) {
        speed = 3.0f;
        maxHp = 3;
    }
    else if (enemyType == 2) {
        speed = 2.0f;
        maxHp = 5;
    }
    else if (enemyType == 3) {
        speed = 1.5f;
        maxHp = 8;
    }
    else if (enemyType == 4) {
        speed = 2.5f;
        maxHp = 20; // 中ボス
        SelectNewTarget();
    }
    hp = maxHp;
    
    if (collider) delete collider;
    float colRadius = (enemyType == 4) ? 45.0f : 35.0f;
    collider = new CapsuleCollider(this, position, position, colRadius);
}

Enemy::~Enemy() {
}

void Enemy::Update() {
    Character::Update(); // スタン時間の減少など

    if (stunTimer > 0) return; // スタン中は行動不能

    if (enemyType == 4) {
        Vector2 target(targetX, targetY);
        float dist = position.DistanceTo(target);

        if (dist < 15.0f) {
            SelectNewTarget();
        }
        else {
            position += (target - position).Normalized() * (speed * Utility::TimeScale);
        }
    }
    else {
        position.y += speed * Utility::TimeScale;
    }

    if (enemyType == 2 || enemyType == 3 || enemyType == 4) 
    {
        attackTimer++;
        int interval = (enemyType == 4) ? 120 : 150; 
        if (attackTimer >= interval)
        {
            attackTimer = 0;
            Player* player = dynamic_cast<Player*>(Master::sceneManager->GetCurrentScene()->GetObjectManager()->GetObject2DByTag(Tag2D_Player));
            Vector2 targetPos(position.x, position.y + 100.0f);
            if (player != nullptr) {
                targetPos = Vector2(player->GetX(), player->GetY());
            }
            Vector2 dir = (targetPos - position).Normalized();
            if (dir.MagnitudeSq() == 0.0f) {
                dir = Vector2(0.0f, 1.0f);
            }
            if (enemyType == 2) {
                new EnemyBullet(position, dir, 4.0f, false, false);
            }
            else if (enemyType == 3) {
                new EnemyBullet(position, dir, 3.5f, false, true);  
            }
            else if (enemyType == 4) {
                static float angle = 0.0f;
                angle += 0.2f;
                for (int i = 0; i < 4; i++) {
                    float angle = angle + (i * 2.0f * 3.14159265f) / 16;
                    new EnemyBullet(position, Vector2::FromAngle(angle), 2.0f);
                }
                float baseAngle = position.AngleTo(targetPos);
                for (int i = -1; i <= 1; i++) {
                    float angle = baseAngle + (i * 8.0f * 3.14159265f / 180.0f);
                    new EnemyBullet(position, Vector2::FromAngle(angle), 3.5f);
                }
            }
        }
    }
    
    if (position.y > Utility::SCREEN_HEIGHT + 50.0f) {
        Character::Kill();
    }
}

void Enemy::Kill() {
    Character::Kill();
}

void Enemy::TakeDamage(int damage) {
    if (!isActive) return;

    Character::TakeDamage(damage); // HPを減らし、0になったらKillを呼ぶ処理など

    if (hp <= 0) {
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
    if (!isActive) return;

    if (stunTimer > 0) {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
        DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), 45, GetColor(0, 200, 255), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }

    int enemyGraphHandle = ResourceManager::GetInstance()->GetGraph("Resource/enemy.png");

    if (enemyGraphHandle != -1) {
        if (enemyType == 1) SetDrawBright(255, 255, 255);
        else if (enemyType == 2) SetDrawBright(255, 200, 100);
        else if (enemyType == 3) SetDrawBright(100, 100, 255);
        else if (enemyType == 4) SetDrawBright(255, 50, 50);

        float drawSize = (enemyType == 4) ? 45.0f : 35.0f;
        DrawExtendGraph(
            static_cast<int>(position.x - drawSize),
            static_cast<int>(position.y - drawSize),
            static_cast<int>(position.x + drawSize),
            static_cast<int>(position.y + drawSize),
            enemyGraphHandle,
            TRUE
        );

        SetDrawBright(255, 255, 255);
    }
    else {
        unsigned int color = GetColor(255, 100, 100);
        if (enemyType == 2) color = GetColor(255, 200, 100);
        else if (enemyType == 3) color = GetColor(100, 100, 255);
        else if (enemyType == 4) color = GetColor(255, 50, 50);

        int drawRadius = (enemyType == 4) ? 45 : 35;
        DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), drawRadius, color, TRUE);
    }
    int hpOffset = (enemyType == 4) ? 65 : 55;
    DrawFormatString(static_cast<int>(position.x) - 15, static_cast<int>(position.y) - hpOffset, GetColor(255, 255, 255), "HP:%d", hp);
}