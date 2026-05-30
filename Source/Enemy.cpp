#include "SoundManager.h"

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
    } else if (m_enemyType == 3) {
        m_speed = 1.5f;
        m_maxHp = 8;
    } else if (m_enemyType == 4) {
        m_speed = 2.5f;
        m_maxHp = 20; // The binding is tied.
        SelectNewTarget();
    }
    m_hp = m_maxHp;

    // Create a circular collider
    float colRadius = (m_enemyType == 4) ? 45.0f : 35.0f;
    mpCollider = new CapsuleCollider(this, mvPosition, mvPosition, colRadius);
}

Enemy::~Enemy() {
    if (mpCollider) {
        delete mpCollider;
        mpCollider = nullptr;
    }
}

// If you are weak, you will be disappointed.
// 謨ｵ繧? Ward Groom ↓ 遘蜍輔 & ?帙 ∫ 螟悶 ↓ 蜃ｺ?溘
void Enemy::Update() {
    if (m_enemyType == 4) {
        // 荳ｭ???ｮｘ轍Recruiting・者・ｼPhysician・繧ｹ縺ｨAfter the spider §・・
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
        // Recruitment/Dating/
        m_y += m_speed;
    }
    mvPosition = VGet(m_x, m_y, 0.0f);

    if (mpCollider) {
        mpCollider->mvPosition = mvPosition;
        mpCollider->mvPosition2 = mvPosition;
    }

    // 遞ｮ?・, 3, 4 ?ｮｮｴ?Physician・螳ju悄?・↓EncouragementΞ繧、繝、繝ｼ縺ｸ?縺￠縺蠑ｾ繧present tea pen、
    if (m_enemyType == 2 || m_enemyType == 3 || m_enemyType == 4) {
        m_attackTimer++;
        int interval = (m_enemyType == 4) ? 60 : 150; // 荳ｭ???鬆ﾆ郢√↓謦・▽
        if (m_attackTimer >= interval) {
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
                new EnemyBullet(m_x, m_y, dx, dy, 4.0f, false, false); // The name
            } else if (m_enemyType == 3) {
                new EnemyBullet(m_x, m_y, dx, dy, 3.5f, false, true); // The string
            } else if (m_enemyType == 4) {
                // ??懊し、夊、讖溽??、WAY繝ｨ貂?縺縺?ｾ縺黍、?、???Ν繧?繼繝繝繝 '...
                static float mbAngle = 0.0f;
                mbAngle += 0.2f;
                // 貂ｦ蟾? Sakaki
                for (int i = 0; i < 4; i++) {
                    float angle = mbAngle + (i * 2.0f * 3.14159265f) / 16;
                    new EnemyBullet(m_x, m_y, std::cos(angle), std::sin(angle), 2.0f);
                }
                // Threshold fishing line/WAY
                float baseAngle = std::atan2(dy, dx);
                for (int i = -1; i <= 1; i++) {
                    float angle = baseAngle + (i * 8.0f * 3.14159265f / 180.0f);
                    new EnemyBullet(m_x, m_y, std::cos(angle), std::sin(angle), 3.5f);
                }
            }
        }
    }

    if (m_y > Utility::SCREEN_HEIGHT + 50.0f) {
        m_isActive = false;
        SetDeleteFlag(true);
    }
}

// The place where you can meet...
// I can't help but encourage you, but I can't help but educate you.
void Enemy::Kill() {
    m_isActive = false;
    SetDeleteFlag(true);
    if (mpCollider) {
        mpCollider->SetDeleteFlag(true);
    }
}


// 繝繝。
// EncouragementΞ繧、繝、繝ｼ縺ｮ謬謦・→薙◆縺"縺滄圀縺ｫ蜻ｼ縺ｰ繧after?P繧presentｸ?i縺
void Enemy::TakeDamage(int damage) {
    m_hp -= damage;
    if (m_hp <= 0) {
        m_hp = 0;
        Kill();
    }
}

// 繧ｧ繧繧繹Physician→Musaka↑縺”縺ｦ縺・k 
// EncouragementΞ繧、繝、繝ｼ縺ｮ蠑?、磯壼く蠑ｾ縲∬ｿ st porcelain 縲∝ｿｿｯｚｚ・?→蠖?◆
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

// Encounter with a friend
// Pass the threshold.
void Enemy::Draw() 
{
    if (!m_isActive) return;

    int s_enemyGraphHandle = ResourceManager::GetInstance()->GetGraph("Resource/enemy.png");

    if (s_enemyGraphHandle != -1) {
        // 繧ｿ繧、繝?↓繧Physician▲縺ｦ濶ｲ繧正、冨∴繧・
        if (m_enemyType == 1) SetDrawBright(255, 255, 255);
        else if (m_enemyType == 2) SetDrawBright(255, 200, 100);
        else if (m_enemyType == 3) SetDrawBright(100, 100, 255);
        else if (m_enemyType == 4) SetDrawBright(255, 50, 50); // ?????襍、?”??・

        float drawSize = (m_enemyType == 4) ? 45.0f : 35.0f;
        DrawExtendGraph(
            static_cast<int>(mvPosition.x - drawSize), 
            static_cast<int>(mvPosition.y - drawSize), 
            static_cast<int>(mvPosition.x + drawSize), 
            static_cast<int>(mvPosition.y + drawSize), 
            s_enemyGraphHandle, 
            TRUE
        );

        SetDrawBright(255, 255, 255); // ?い繧縺・??縺・
    } else {
        unsigned int color = GetColor(255, 100, 100);
        if (m_enemyType == 2) color = GetColor(255, 200, 100);
        else if (m_enemyType == 3) color = GetColor(100, 100, 255);
        else if (m_enemyType == 4) color = GetColor(255, 50, 50);
        
        int drawRadius = (m_enemyType == 4) ? 45 : 35;
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), drawRadius, color, TRUE);
    }

    // Draw HP text above enemy
    int hpOffset = (m_enemyType == 4) ? 65 : 55;
    DrawFormatString(static_cast<int>(mvPosition.x) - 15, static_cast<int>(mvPosition.y) - hpOffset, GetColor(255, 255, 255), "HP:%d", m_hp);
}
