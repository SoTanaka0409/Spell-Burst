<<<<<<< HEAD
#include "SoundManager.h"
=======
<<<<<<< HEAD
>>>>>>> 240f2f277102418da5ddb286e12d12d717854dca

=======
>>>>>>> main
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
#include "ResourceManager.h"
<<<<<<< HEAD
#include <cmath>
#include <cstdlib>

=======
#include "GameScene.h"
#include "EnemyManager.h"
#include <cmath>
#include <cstdlib>

// 新しい移動目標地点をランダムに決定する
>>>>>>> main
void Enemy::SelectNewTarget() {
    m_targetX = 100.0f + static_cast<float>(rand() % 1080);
    m_targetY = 80.0f + static_cast<float>(rand() % 180);
}

<<<<<<< HEAD

Enemy::Enemy(float x, float y, int enemyType) 
=======
// コンストラクタ（初期化処理）
Enemy::Enemy(float x, float y, int enemyType)
>>>>>>> main
    : Object2D(VGet(x, y, 0.0f))
    , mpCollider(nullptr)
{
    SetTag(Tag2D_Enemy);
<<<<<<< HEAD
    m_x = x;
    m_y = y;
=======
    mvPosition.x = x;
    mvPosition.y = y;
>>>>>>> main
    m_isActive = true;
    m_enemyType = enemyType;
    m_attackTimer = 0;

<<<<<<< HEAD
    if (m_enemyType == 1) {
        m_speed = 3.0f;
        m_maxHp = 3;
    } else if (m_enemyType == 2) {
        m_speed = 2.0f;
        m_maxHp = 5;
    } else if (m_enemyType == 3) {
        m_speed = 1.5f;
        m_maxHp = 8;
    } else if (m_enemyType == 4) {
=======
    // 敵のタイプ（1〜4）に応じてステータスを設定
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
>>>>>>> main
        m_speed = 2.5f;
        m_maxHp = 20; // 中ボスはタチE
        SelectNewTarget();
    }
    m_hp = m_maxHp;

<<<<<<< HEAD
    // Create a circular collider
=======
    // 円形の当たり判定（コライダー）を作成
>>>>>>> main
    float colRadius = (m_enemyType == 4) ? 45.0f : 35.0f;
    mpCollider = new CapsuleCollider(this, mvPosition, mvPosition, colRadius);
}

<<<<<<< HEAD
=======
// デストラクタ（解放処理）
>>>>>>> main
Enemy::~Enemy() {
    if (mpCollider) {
        delete mpCollider;
        mpCollider = nullptr;
    }
}

<<<<<<< HEAD
// 毎フレーム呼ばれる更新処琁E
// 敵を下方向に移動させ、画面外に出たら活動停止・削除フラグを立てます、E
=======
// 毎フレーム呼ばれる更新処理
<<<<<<< HEAD
// 敵を下方向に移動させ、画面外に出たら活動停止・削除フラグを立てます。
>>>>>>> 240f2f277102418da5ddb286e12d12d717854dca
void Enemy::Update() {
    if (m_enemyType == 4) {
        // 中ボスの移動�E琁E���Eスと同じ�E�E
        float dx = m_targetX - m_x;
        float dy = m_targetY - m_y;
        float dist = std::sqrt(dx * dx + dy * dy);

        if (dist < 15.0f) {
            SelectNewTarget();
        } else {
            m_x += (dx / dist) * m_speed;
            m_y += (dy / dist) * m_speed;
        }
    } else {
        // 通常の敵の移動�E琁E
        m_y += m_speed;
    }
    mvPosition = VGet(m_x, m_y, 0.0f);

=======
// 敵を移動させ、画面外に出たら活動停止・削除フラグを立てます
void Enemy::Update() {
    if (m_enemyType == 4) {
        // 中ボスの移動処理（ボスと同じ動き）
        float dx = m_targetX - mvPosition.x;
        float dy = m_targetY - mvPosition.y;
        float dist = std::sqrt(dx * dx + dy * dy);

        if (dist < 15.0f) {
            // 目標地点に近づいたら次の目標を決定
            SelectNewTarget();
        }
        else {
            // 目標に向かって移動
            mvPosition.x += (dx / dist) * m_speed * Utility::TimeScale;
            mvPosition.y += (dy / dist) * m_speed * Utility::TimeScale;
        }
    }
    else {
        // 通常の敵の移動処理（下方向へ直進）
        mvPosition.y += m_speed * Utility::TimeScale;
    }
    mvPosition = VGet(mvPosition.x, mvPosition.y, 0.0f);

    // 当たり判定の位置も敵の移動に合わせて更新
>>>>>>> main
    if (mpCollider) {
        mpCollider->mvPosition = mvPosition;
        mpCollider->mvPosition2 = mvPosition;
    }

<<<<<<< HEAD
    // 種顁E, 3, 4の場合�E定期皁E��プレイヤーへ向けて弾を撃つ
=======
<<<<<<< HEAD
    // 種類2, 3, 4の場合は定期的にプレイヤーへ向けて弾を撃つ
>>>>>>> 240f2f277102418da5ddb286e12d12d717854dca
    if (m_enemyType == 2 || m_enemyType == 3 || m_enemyType == 4) {
        m_attackTimer++;
        int interval = (m_enemyType == 4) ? 60 : 150; // 中ボスは頻繁に撁E��
        if (m_attackTimer >= interval) {
            m_attackTimer = 0;
            Player* player = dynamic_cast<Player*>(Master::sceneManager->GetCurrentScene()->GetObjectManager()->GetObject2DByTag(Tag2D_Player));
            float targetX = m_x;
            float targetY = m_y + 100.0f;
=======
    // 敵タイプが2, 3, 4の場合は、定期的にプレイヤーへ向けて弾を撃つ
    if (m_enemyType == 2 || m_enemyType == 3 || m_enemyType == 4) {
        m_attackTimer++;
        int interval = (m_enemyType == 4) ? 120 : 150; // 中ボスは頻繁に撃つ
        if (m_attackTimer >= interval) {
            m_attackTimer = 0;

            // プレイヤーの位置を取得
            Player* player = dynamic_cast<Player*>(Master::sceneManager->GetCurrentScene()->GetObjectManager()->GetObject2DByTag(Tag2D_Player));
            float targetX = mvPosition.x;
            float targetY = mvPosition.y + 100.0f;
>>>>>>> main
            if (player != nullptr) {
                targetX = player->GetX();
                targetY = player->GetY();
            }
<<<<<<< HEAD
            float dx = targetX - m_x;
            float dy = targetY - m_y;
=======

            // プレイヤーへの方向ベクトルを計算
            float dx = targetX - mvPosition.x;
            float dy = targetY - mvPosition.y;
>>>>>>> main
            float dist = std::sqrt(dx * dx + dy * dy);
            if (dist > 0.0f) {
                dx /= dist;
                dy /= dist;
<<<<<<< HEAD
            } else {
                dx = 0.0f;
                dy = 1.0f;
            }
            
            if (m_enemyType == 2) {
                new EnemyBullet(m_x, m_y, dx, dy, 4.0f, false, false); // 通常弾
            } else if (m_enemyType == 3) {
                new EnemyBullet(m_x, m_y, dx, dy, 3.5f, false, true); // スタン弾
            } else if (m_enemyType == 4) {
                // 中ボス�E��E機狙ぁEWAYと渦巻き弾の褁E���E�スペルカード風�E�E
                static float mbAngle = 0.0f;
                mbAngle += 0.2f;
                // 渦巻き弾
                for (int i = 0; i < 4; i++) {
                    float angle = mbAngle + (i * 2.0f * 3.14159265f) / 16;
                    new EnemyBullet(m_x, m_y, std::cos(angle), std::sin(angle), 2.0f);
                }
                // 自機狙ぁEWAY
                float baseAngle = std::atan2(dy, dx);
                for (int i = -1; i <= 1; i++) {
                    float angle = baseAngle + (i * 8.0f * 3.14159265f / 180.0f);
                    new EnemyBullet(m_x, m_y, std::cos(angle), std::sin(angle), 3.5f);
=======
            }
            else {
                dx = 0.0f;
                dy = 1.0f;
            }

            // 敵のタイプに応じた弾の発射
            if (m_enemyType == 2) {
                new EnemyBullet(mvPosition.x, mvPosition.y, dx, dy, 4.0f, false, false); // 通常弾
            }
            else if (m_enemyType == 3) {
                new EnemyBullet(mvPosition.x, mvPosition.y, dx, dy, 3.5f, false, true);  // スタン弾
            }
            else if (m_enemyType == 4) {
                // 中ボス：自機狙い3wayと渦巻き弾の複合（スペルカード風）
                static float mbAngle = 0.0f;
                mbAngle += 0.2f;

                // 渦巻き弾の生成
                for (int i = 0; i < 4; i++) {
                    float angle = mbAngle + (i * 2.0f * 3.14159265f) / 16;
                    new EnemyBullet(mvPosition.x, mvPosition.y, std::cos(angle), std::sin(angle), 2.0f);
                }

                // 自機狙い3way弾の生成
                float baseAngle = std::atan2(dy, dx);
                for (int i = -1; i <= 1; i++) {
                    float angle = baseAngle + (i * 8.0f * 3.14159265f / 180.0f);
                    new EnemyBullet(mvPosition.x, mvPosition.y, std::cos(angle), std::sin(angle), 3.5f);
>>>>>>> main
                }
            }
        }
    }

<<<<<<< HEAD
    if (m_y > Utility::SCREEN_HEIGHT + 50.0f) {
=======
    // 画面外（下端）に出たら削除
    if (mvPosition.y > Utility::SCREEN_HEIGHT + 50.0f) {
>>>>>>> main
        m_isActive = false;
        SetDeleteFlag(true);
    }
}

<<<<<<< HEAD
// 敵の消滁E�E琁E
// 活動フラグをオフにし、オブジェクト管琁E��スチE��に削除されるよぁE��ラグを立てます、E
=======
// 敵の消滅処理
<<<<<<< HEAD
// 活動フラグをオフにし、オブジェクト管理システムに削除されるようフラグを立てます。
=======
// 活動フラグをオフにし、オブジェクト管理システムに削除されるようフラグを立てます
>>>>>>> main
>>>>>>> 240f2f277102418da5ddb286e12d12d717854dca
void Enemy::Kill() {
    m_isActive = false;
    SetDeleteFlag(true);
    if (mpCollider) {
        mpCollider->SetDeleteFlag(true);
    }
}

<<<<<<< HEAD

// ダメージを受ける処琁E
// プレイヤーの攻撁E��当たった際に呼ばれ、HPを減らします、E以下になったら消滁E�E琁EKill)を呼びます、E
void Enemy::TakeDamage(int damage) {
=======
// ダメージを受ける処理
// プレイヤーの攻撃と当たった際に呼ばれ、HPを減らします。0以下になったら消滅処理(Kill)を呼びます
void Enemy::TakeDamage(int damage) {
    if (!m_isActive) return;

>>>>>>> main
    m_hp -= damage;
    if (m_hp <= 0) {
        m_hp = 0;
        Kill();
<<<<<<< HEAD
=======

        // 敵を倒した報酬として、プレイヤーに経験値（XP）を付与
        Player* player = dynamic_cast<Player*>(
            Master::sceneManager->GetCurrentScene()->GetObjectManager()->GetObject2DByTag(Object2D::Tag2D_Player)
        );
        if (player != nullptr) {
            player->AddXp(1);
        }

        // マネージャーに撃破数を通知
        GameScene* gs = dynamic_cast<GameScene*>(Master::sceneManager->GetCurrentScene());
        if (gs != nullptr && gs->GetEnemyManager() != nullptr) {
            gs->GetEnemyManager()->AddDefeatedCount();
        }
>>>>>>> main
    }
}

<<<<<<< HEAD
// 他�Eオブジェクトと重なってぁE��時�E処琁E��当たり判定イベント！E
// プレイヤーの弾�E�通常弾、近接、忁E��技�E�と当たった場合に、�E身のTakeDamageを呼び出します、E
=======
// 他のオブジェクトと重なっている時の処理（当たり判定イベント）
<<<<<<< HEAD
// プレイヤーの弾（通常弾、近接、必殺技）と当たった場合に、自身のTakeDamageを呼び出します。
=======
// プレイヤーの弾（通常弾、近接、必殺技など）と当たった場合に、自身のTakeDamageを呼び出します
>>>>>>> main
>>>>>>> 240f2f277102418da5ddb286e12d12d717854dca
void Enemy::OnTrigger(Collider* collider, Collider* check) {
    if (check != nullptr && check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == Tag2D_PlayerBullet) {
            Bullet* bullet = dynamic_cast<Bullet*>(check->GetParentObject());
            if (bullet != nullptr) {
                TakeDamage(bullet->GetDamage());
<<<<<<< HEAD
                bullet->Kill(); // Destroy the bullet on impact
=======
                bullet->Kill(); // 当たったプレイヤーの弾を消滅させる

>>>>>>> main
            }
        }
    }
}

<<<<<<< HEAD
// 描画処琁E
// 敵自身の画像を描画し、E��上にHPバ�Eを表示します、E
=======
// 描画処理
<<<<<<< HEAD
// 敵自身の画像を描画し、頭上にHPバーを表示します。
>>>>>>> 240f2f277102418da5ddb286e12d12d717854dca
void Enemy::Draw() 
=======
// 敵自身の画像を描画し、頭上にHPテキストを表示します
void Enemy::Draw()
>>>>>>> main
{
    if (!m_isActive) return;

    int s_enemyGraphHandle = ResourceManager::GetInstance()->GetGraph("Resource/enemy.png");

    if (s_enemyGraphHandle != -1) {
<<<<<<< HEAD
        // タイプによって色を変えめE
=======
<<<<<<< HEAD
        // タイプによって色を変える
>>>>>>> 240f2f277102418da5ddb286e12d12d717854dca
        if (m_enemyType == 1) SetDrawBright(255, 255, 255);
        else if (m_enemyType == 2) SetDrawBright(255, 200, 100);
        else if (m_enemyType == 3) SetDrawBright(100, 100, 255);
        else if (m_enemyType == 4) SetDrawBright(255, 50, 50); // 中ボスは赤っぽぁE

        float drawSize = (m_enemyType == 4) ? 45.0f : 35.0f;
        DrawExtendGraph(
            static_cast<int>(mvPosition.x - drawSize), 
            static_cast<int>(mvPosition.y - drawSize), 
            static_cast<int>(mvPosition.x + drawSize), 
            static_cast<int>(mvPosition.y + drawSize), 
            s_enemyGraphHandle, 
            TRUE
        );

        SetDrawBright(255, 255, 255); // 色を�Eに戻ぁE
    } else {
=======
        // タイプによって描画の輝度（色合い）を変える
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
        // 画像が見つからない場合のフォールバック（簡易的な円の描画）
>>>>>>> main
        unsigned int color = GetColor(255, 100, 100);
        if (m_enemyType == 2) color = GetColor(255, 200, 100);
        else if (m_enemyType == 3) color = GetColor(100, 100, 255);
        else if (m_enemyType == 4) color = GetColor(255, 50, 50);
<<<<<<< HEAD
        
=======

>>>>>>> main
        int drawRadius = (m_enemyType == 4) ? 45 : 35;
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), drawRadius, color, TRUE);
    }

<<<<<<< HEAD
    // Draw HP text above enemy
    int hpOffset = (m_enemyType == 4) ? 65 : 55;
    DrawFormatString(static_cast<int>(mvPosition.x) - 15, static_cast<int>(mvPosition.y) - hpOffset, GetColor(255, 255, 255), "HP:%d", m_hp);
}
=======
    // 敵の頭上にHPテキストを表示
    int hpOffset = (m_enemyType == 4) ? 65 : 55;
    DrawFormatString(static_cast<int>(mvPosition.x) - 15, static_cast<int>(mvPosition.y) - hpOffset, GetColor(255, 255, 255), "HP:%d", m_hp);
}
>>>>>>> main
