#include "Boss.h"
#include "CapsuleCollider.h"
#include "Bullet.h"
#include "MeleeAttack.h"
#include "SpecialBullet.h"
#include "Player.h"
#include "EnemyBullet.h"
#include "ObjectManager.h"
#include "Master.h"
#include "SceneManager.h"
#include "ResultScene.h"
#include "Enemy.h"
#include <DxLib.h>
#include <cmath>
#include <cstdlib>

Boss::Boss(float x, float y, int bossType)
    : Object2D(VGet(x, y, 0.0f))
    , mpCollider(nullptr)
{
    SetTag(Tag2D_Enemy);
    m_x = x;
    m_y = y;
    m_bossType = bossType;
    if (m_bossType == 1) {
        m_speed = 1.5f;
        m_hp = 20;
    } else if (m_bossType == 2) {
        m_speed = 2.0f;
        m_hp = 30;
    } else {
        m_speed = 2.5f;
        m_hp = 50;
    }
    m_maxHp = m_hp;
    m_isActive = true;
    m_attackTimer = 0;
    m_patternIndex = 0;
    m_isDying = false;
    if (m_bossType == 3) {
        m_lives = 3;
    } else {
        m_lives = 1;
    }
    m_invincibleTimer = 0;
    m_invincibleCycleTimer = 0;
    m_isDying = false;
    m_deathTimer = 0;

    // Radius 80.0f for the giant boss
    mpCollider = new CapsuleCollider(this, mvPosition, mvPosition, 80.0f);
    SelectNewTarget();
}

Boss::~Boss() {
    if (mpCollider) {
        delete mpCollider;
        mpCollider = nullptr;
    }
}

// ランダム移動のターゲット座標を更新する処理
// 画面上部（プレイヤーが攻撃しやすい範囲）からランダムに次の移動先を決めます。
void Boss::SelectNewTarget() {
    // Top half boundary: X between 100 and 1180, Y between 80 and 260
    m_targetX = 100.0f + static_cast<float>(rand() % 1080);
    m_targetY = 80.0f + static_cast<float>(rand() % 180);
}

// ボスの毎フレームの更新処理
// 死亡演出中なら上にフェードアウトし、生存中ならターゲット座標に向かって移動しながら弾幕を撃ちます。
void Boss::Update() {
    if (m_isDying) {
        m_deathTimer--;
        m_y -= 1.0f; // Move upwards while dying
        mvPosition = VGet(m_x, m_y, 0.0f);
        if (m_deathTimer <= 0) {
            Kill();
        }
        return; // Skip normal behavior
    }

    if (m_invincibleTimer > 0) {
        m_invincibleTimer--;
    }

    // 最終ボス（タイプ3）のみ、5秒（300フレーム）おきに2秒間（120フレーム）無敵になる
    if (m_bossType == 3) {
        m_invincibleCycleTimer++;
        if (m_invincibleCycleTimer >= 300) {
            m_invincibleTimer = 120; // 2 seconds invincibility
            m_invincibleCycleTimer = 0;
            
            // 無敵化と同時に取り巻きを召喚
            new Enemy(m_x - 60.0f, m_y + 60.0f, 1);
            new Enemy(m_x + 60.0f, m_y + 60.0f, 1);
        }
    } else {
        m_invincibleTimer = 0;
        m_invincibleCycleTimer = 0;
    }

    // Move towards current target
    float dx = m_targetX - m_x;
    float dy = m_targetY - m_y;
    float dist = std::sqrt(dx * dx + dy * dy);

    if (dist < 15.0f) {
        SelectNewTarget();
    } else {
        m_x += (dx / dist) * m_speed;
        m_y += (dy / dist) * m_speed;
    }

    mvPosition = VGet(m_x, m_y, 0.0f);

    if (mpCollider) {
        mpCollider->mvPosition = mvPosition;
        mpCollider->mvPosition2 = mvPosition;
    }

    // Shoot barrage patterns cyclically
    m_attackTimer++;
    if (m_bossType == 1) {
        if (m_attackTimer >= 60) {
            m_attackTimer = 0;
            ShootSimpleBarrage();
        }
    } else if (m_bossType == 2) {
        if (m_attackTimer >= 80) {
            m_attackTimer = 0;
            ShootBouncingBarrage();
        }
    } else {
        if (m_attackTimer >= 100) { // Every 1.6s approx.
            m_attackTimer = 0;
            if (m_patternIndex == 0) {
                ShootRadialBarrage();
            } else if (m_patternIndex == 1) {
                ShootFanBarrage();
            } else if (m_patternIndex == 2) {
                ShootTargetedBarrage();
            }
            m_patternIndex = (m_patternIndex + 1) % 3;
        }
    }
}

// 全方位弾幕を撃つ処理
// ボスの周囲360度に向かって、円形に広がるように弾を発射します。
void Boss::ShootRadialBarrage() {
    const float PI = 3.14159265f;
    const int bulletCount = 18;
    bool reflect = (m_lives == 2);
    for (int i = 0; i < bulletCount; i++) {
        float angle = (i * 2.0f * PI) / bulletCount;
        float dx = std::cos(angle);
        float dy = std::sin(angle);
        new EnemyBullet(m_x, m_y, dx, dy, 4.0f, reflect);
    }
}

// 扇状弾幕を撃つ処理
// ボスの前方下方向を中心に、扇形に広がるように弾を発射します。
void Boss::ShootFanBarrage() {
    const float PI = 3.14159265f;
    const int bulletCount = 7;
    bool reflect = (m_lives == 2);
    // Straight down is PI/2 (90 degrees). We spread out +/- 45 degrees.
    float baseAngle = PI / 2.0f;
    for (int i = 0; i <= bulletCount; i++) {
        float angle = baseAngle + (i * 12.0f * PI / 180.0f);
        float dx = std::cos(angle);
        float dy = std::sin(angle);
        new EnemyBullet(m_x, m_y, dx, dy, 5.0f, reflect);
    }
}

// 自機狙い弾幕を撃つ処理
// プレイヤーの現在位置を計算し、そこに向かって3WAYの弾を発射します。
void Boss::ShootTargetedBarrage() {
    const float PI = 3.14159265f;
    Player* player = dynamic_cast<Player*>(Master::sceneManager->GetCurrentScene()->GetObjectManager()->GetObject2DByTag(Tag2D_Player));
    float targetX = m_x;
    float targetY = m_y + 200.0f; // Default targeted direction (downwards)

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

    float baseAngle = std::atan2(dy, dx);

    // 3-way spread shot aimed at player
    for (int i = -1; i <= 1; i++) {
        float angle = baseAngle + (i * 10.0f * PI / 180.0f);
        new EnemyBullet(m_x, m_y, std::cos(angle), std::sin(angle), 6.5f);
    }
}

void Boss::ShootSimpleBarrage() {
    Player* player = dynamic_cast<Player*>(Master::sceneManager->GetCurrentScene()->GetObjectManager()->GetObject2DByTag(Tag2D_Player));
    float targetX = m_x;
    float targetY = m_y + 200.0f;

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

    new EnemyBullet(m_x, m_y, dx, dy, 5.0f);
}

void Boss::ShootBouncingBarrage() {
    const float PI = 3.14159265f;
    for (int i = 0; i < 6; i++) {
        float angle = (i * 2.0f * PI) / 6.0f;
        float dx = std::cos(angle);
        float dy = std::sin(angle);
        // pass canReflect = true
        new EnemyBullet(m_x, m_y, dx, dy, 4.5f, true);
    }
}

// ダメージを受ける処理
// プレイヤーの攻撃と当たった際に呼ばれ、HPを減らします。0以下になったら死亡演出(m_isDying)を開始します。
void Boss::TakeDamage(int damage) {
    if (m_isDying || m_invincibleTimer > 0) return;

    // m_lives の手動減少ロジックを削除し、0になった時のみ判定

    m_hp -= damage;
    if (m_hp <= 0) {
        m_hp = 0;
        m_lives--;
        
        if (m_lives > 0) {
            // Heal back to max and become invincible for a while
            m_hp = m_maxHp;
            m_invincibleTimer = 180; // 3 seconds invincibility on phase change
        } else {
            m_isDying = true;
            m_deathTimer = 180; // 3 seconds flash and fly up
            if (mpCollider) {
                mpCollider->SetDeleteFlag(true); // Disable collision
                mpCollider = nullptr;
            }
        }
    }
}

// 完全に消滅させる処理
// 死亡演出が終わった後に呼ばれ、ゲームクリア（ResultSceneへの移行）をトリガーします。
void Boss::Kill() {
    m_isActive = false;
    SetDeleteFlag(true);
    if (mpCollider) {
        mpCollider->SetDeleteFlag(true);
    }
    // Transition to victory result screen only if it's the phase 3 boss
    if (m_bossType == 3) {
        ResultScene::s_isVictory = true;
        Master::sceneManager->SetNextScene(SceneManager::SCENE_RESULT);
    }
}

// 他のオブジェクトと重なっている時の処理（当たり判定イベント）
// プレイヤーの弾（通常弾、近接、必殺技）と当たった場合に、自身のTakeDamageを呼び出します。
void Boss::OnTrigger(Collider* collider, Collider* check) {
    if (m_isDying) return;

    if (check != nullptr && check->GetParentObject() != nullptr) {
        Object2D* parent = check->GetParentObject();
        if (parent->GetTag() == Tag2D_PlayerBullet) {
            int damage = 1;
            Bullet* b = dynamic_cast<Bullet*>(parent);
            if (b != nullptr) {
                damage = b->GetDamage();
                b->Kill(); // Bullet is destroyed on impact
            } else {
                MeleeAttack* m = dynamic_cast<MeleeAttack*>(parent);
                if (m != nullptr) {
                    damage = m->GetDamage(); // Melee pierces/survives
                } else {
                    SpecialBullet* s = dynamic_cast<SpecialBullet*>(parent);
                    if (s != nullptr) {
                        damage = s->GetDamage(); // Special piercing bullet pierces/survives
                    }
                }
            }
            TakeDamage(damage);
        }
    }
}

// 描画処理
// ボスの画像を描画します。死亡演出中はチカチカと点滅させ、英語のメッセージを表示します。
void Boss::Draw() {
    if (!m_isActive) return;

    static int s_bossGraphHandle = -1;
    if (s_bossGraphHandle == -1) {
        s_bossGraphHandle = LoadGraph("Resource/boss.png");
    }

    if (s_bossGraphHandle != -1) {
        if (!m_isDying || (m_deathTimer / 5) % 2 == 0) {
            if (m_invincibleTimer > 0) {
                SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128 + (m_invincibleTimer % 20) * 5);
            }
            DrawExtendGraph(
                static_cast<int>(mvPosition.x - 80.0f), 
                static_cast<int>(mvPosition.y - 80.0f), 
                static_cast<int>(mvPosition.x + 80.0f), 
                static_cast<int>(mvPosition.y + 80.0f), 
                s_bossGraphHandle, 
                TRUE
            );
            if (m_invincibleTimer > 0) {
                SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
            }
        }
    } else {
        if (!m_isDying || (m_deathTimer / 5) % 2 == 0) {
            unsigned int color = GetColor(255, 0, 0);
            if (m_invincibleTimer > 0 && (m_invincibleTimer / 5) % 2 == 0) {
                color = GetColor(255, 255, 0); // Blink yellow during invincibility
            }
            DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 80, color, TRUE);
        }
    }

    if (m_isDying) {
        DrawString(static_cast<int>(mvPosition.x) - 150, static_cast<int>(mvPosition.y) + 90, "I will be waiting for you in the next stage...!", GetColor(255, 100, 100));
    }
}
