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
        m_maxHp = 20; // 荳ｭ繝懊せ縺ｯ繧ｿ繝・
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

// 豈弱ヵ繝ｬ繝ｼ繝蜻ｼ縺ｰ繧後ｋ譖ｴ譁ｰ蜃ｦ逅・
// 謨ｵ繧剃ｸ区婿蜷代↓遘ｻ蜍輔＆縺帙∫判髱｢螟悶↓蜃ｺ縺溘ｉ豢ｻ蜍募●豁｢繝ｻ蜑企勁繝輔Λ繧ｰ繧堤ｫ九※縺ｾ縺吶・
void Enemy::Update() {
    if (m_enemyType == 4) {
        // 荳ｭ繝懊せ縺ｮ遘ｻ蜍募・逅・ｼ医・繧ｹ縺ｨ蜷後§・・
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
        // 騾壼ｸｸ縺ｮ謨ｵ縺ｮ遘ｻ蜍募・逅・
        m_y += m_speed;
    }
    mvPosition = VGet(m_x, m_y, 0.0f);

    if (mpCollider) {
        mpCollider->mvPosition = mvPosition;
        mpCollider->mvPosition2 = mvPosition;
    }

    // 遞ｮ鬘・, 3, 4縺ｮ蝣ｴ蜷医・螳壽悄逧・↓繝励Ξ繧､繝､繝ｼ縺ｸ蜷代￠縺ｦ蠑ｾ繧呈茶縺､
    if (m_enemyType == 2 || m_enemyType == 3 || m_enemyType == 4) {
        m_attackTimer++;
        int interval = (m_enemyType == 4) ? 60 : 150; // 荳ｭ繝懊せ縺ｯ鬆ｻ郢√↓謦・▽
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
                new EnemyBullet(m_x, m_y, dx, dy, 4.0f, false, false); // 騾壼ｸｸ蠑ｾ
            } else if (m_enemyType == 3) {
                new EnemyBullet(m_x, m_y, dx, dy, 3.5f, false, true); // 繧ｹ繧ｿ繝ｳ蠑ｾ
            } else if (m_enemyType == 4) {
                // 荳ｭ繝懊せ・夊・讖溽漁縺・WAY縺ｨ貂ｦ蟾ｻ縺榊ｼｾ縺ｮ隍・粋・医せ繝壹Ν繧ｫ繝ｼ繝蛾｢ｨ・・
                static float mbAngle = 0.0f;
                mbAngle += 0.2f;
                // 貂ｦ蟾ｻ縺榊ｼｾ
                for (int i = 0; i < 4; i++) {
                    float angle = mbAngle + (i * 2.0f * 3.14159265f) / 16;
                    new EnemyBullet(m_x, m_y, std::cos(angle), std::sin(angle), 2.0f);
                }
                // 閾ｪ讖溽漁縺・WAY
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

// 謨ｵ縺ｮ豸域ｻ・・逅・
// 豢ｻ蜍輔ヵ繝ｩ繧ｰ繧偵が繝輔↓縺励√が繝悶ず繧ｧ繧ｯ繝育ｮ｡逅・す繧ｹ繝・Β縺ｫ蜑企勁縺輔ｌ繧九ｈ縺・ヵ繝ｩ繧ｰ繧堤ｫ九※縺ｾ縺吶・
void Enemy::Kill() {
    m_isActive = false;
    SetDeleteFlag(true);
    if (mpCollider) {
        mpCollider->SetDeleteFlag(true);
    }
}


// 繝繝｡繝ｼ繧ｸ繧貞女縺代ｋ蜃ｦ逅・
// 繝励Ξ繧､繝､繝ｼ縺ｮ謾ｻ謦・→蠖薙◆縺｣縺滄圀縺ｫ蜻ｼ縺ｰ繧後？P繧呈ｸ帙ｉ縺励∪縺吶・莉･荳九↓縺ｪ縺｣縺溘ｉ豸域ｻ・・逅・Kill)繧貞他縺ｳ縺ｾ縺吶・
void Enemy::TakeDamage(int damage) {
    m_hp -= damage;
    if (m_hp <= 0) {
        m_hp = 0;
        Kill();
    }
}

// 莉悶・繧ｪ繝悶ず繧ｧ繧ｯ繝医→驥阪↑縺｣縺ｦ縺・ｋ譎ゅ・蜃ｦ逅・ｼ亥ｽ薙◆繧雁愛螳壹う繝吶Φ繝茨ｼ・
// 繝励Ξ繧､繝､繝ｼ縺ｮ蠑ｾ・磯壼ｸｸ蠑ｾ縲∬ｿ第磁縲∝ｿ・ｮｺ謚・峨→蠖薙◆縺｣縺溷ｴ蜷医↓縲∬・霄ｫ縺ｮTakeDamage繧貞他縺ｳ蜃ｺ縺励∪縺吶・
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

// 謠冗判蜃ｦ逅・
// 謨ｵ閾ｪ霄ｫ縺ｮ逕ｻ蜒上ｒ謠冗判縺励・ｭ荳翫↓HP繝舌・繧定｡ｨ遉ｺ縺励∪縺吶・
void Enemy::Draw() 
{
    if (!m_isActive) return;

    int s_enemyGraphHandle = ResourceManager::GetInstance()->GetGraph("Resource/enemy.png");

    if (s_enemyGraphHandle != -1) {
        // 繧ｿ繧､繝励↓繧医▲縺ｦ濶ｲ繧貞､峨∴繧・
        if (m_enemyType == 1) SetDrawBright(255, 255, 255);
        else if (m_enemyType == 2) SetDrawBright(255, 200, 100);
        else if (m_enemyType == 3) SetDrawBright(100, 100, 255);
        else if (m_enemyType == 4) SetDrawBright(255, 50, 50); // 荳ｭ繝懊せ縺ｯ襍､縺｣縺ｽ縺・

        float drawSize = (m_enemyType == 4) ? 45.0f : 35.0f;
        DrawExtendGraph(
            static_cast<int>(mvPosition.x - drawSize), 
            static_cast<int>(mvPosition.y - drawSize), 
            static_cast<int>(mvPosition.x + drawSize), 
            static_cast<int>(mvPosition.y + drawSize), 
            s_enemyGraphHandle, 
            TRUE
        );

        SetDrawBright(255, 255, 255); // 濶ｲ繧貞・縺ｫ謌ｻ縺・
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
