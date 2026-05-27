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
    mvPosition.x = x;
    mvPosition.y = y;
    m_dx = dx;
    m_dy = dy;
    m_speed = speed;
    m_isActive = true;
    m_canReflect = false; // 繝ｦ繝ｼ繧ｶ繝ｼ縺ｮ隕∵悍縺ｫ繧医ｊ霍ｳ縺ｭ霑斐ｊ・亥渚蟆・ｼ峨ｒ辟｡蜉ｹ蛹・
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

// 豈弱ヵ繝ｬ繝ｼ繝�蜻ｼ縺ｰ繧後ｋ譖ｴ譁ｰ蜃ｦ逅・
// 謖・ｮ壹＆繧後◆繝吶け繝医Ν譁ｹ蜷代∈蠑ｾ繧堤ｧｻ蜍輔＆縺帙∫判髱｢螟悶↓蜃ｺ縺溘ｉ蜑企勁繝輔Λ繧ｰ繧堤ｫ九※縺ｾ縺吶・
void EnemyBullet::Update() {
    if (m_homingDelayTimer > 0) {
        m_homingDelayTimer--;
    } else if (m_homingTimer > 0) {
        m_homingTimer--;
        Player* player = dynamic_cast<Player*>(Master::sceneManager->GetCurrentScene()->GetObjectManager()->GetObject2DByTag(Tag2D_Player));
        if (player) {
            float currentAngle = std::atan2(m_dy, m_dx);
            float targetAngle = std::atan2(player->GetY() - mvPosition.y, player->GetX() - mvPosition.x);
            
            float diff = targetAngle - currentAngle;
            // 隗貞ｺｦ繧・-PI ~ PI 縺ｫ豁｣隕丞喧
            while (diff > 3.14159265f) diff -= 2.0f * 3.14159265f;
            while (diff < -3.14159265f) diff += 2.0f * 3.14159265f;
            
            // 譌句屓騾溷ｺｦ・井ｾ・ 豈弱ヵ繝ｬ繝ｼ繝� 0.05 繝ｩ繧ｸ繧｢繝ｳ・・
            float turnSpeed = 0.03f; 
            if (diff > turnSpeed) diff = turnSpeed;
            if (diff < -turnSpeed) diff = -turnSpeed;
            
            currentAngle += diff;
            m_dx = std::cos(currentAngle);
            m_dy = std::sin(currentAngle);
        }
    }

    mvPosition.x += m_dx * m_speed * Utility::TimeScale;
    mvPosition.y += m_dy * m_speed * Utility::TimeScale;
    mvPosition = VGet(mvPosition.x, mvPosition.y, 0.0f);

    if (mpCollider) {
        mpCollider->mvPosition = mvPosition;
        mpCollider->mvPosition2 = mvPosition;
    }

    // 逕ｻ髱｢螟悶↓蜃ｺ縺溘ｉ蜑企勁縺吶ｋ・郁ｷｳ縺ｭ霑斐ｊ蜃ｦ逅・・辟｡蜉ｹ蛹悶＆繧後∪縺励◆・・
    if (mvPosition.x < -50.0f || mvPosition.x > Utility::SCREEN_WIDTH + 50.0f || mvPosition.y < -50.0f || mvPosition.y > Utility::SCREEN_HEIGHT + 50.0f) {
        m_isActive = false;
        SetDeleteFlag(true);
    }
}

// 謠冗判蜃ｦ逅・
// 謨ｵ蠑ｾ縺ｮ逕ｻ蜒上ｒ謠冗判縺励∪縺吶・
void EnemyBullet::Draw() {
    if (!m_isActive) return;
    
    if (m_isStunBullet) {
        // 繧ｹ繧ｿ繝ｳ蠑ｾ縺ｯ豌ｴ濶ｲ邉ｻ
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 14, GetColor(0, 150, 255), TRUE); // 繧ｪ繝ｼ繝ｩ
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 10, GetColor(0, 255, 255), TRUE); // 螟匁棧
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 6, GetColor(255, 255, 255), TRUE); // 繧ｳ繧｢
    } else {
        // 騾壼ｸｸ縺ｮ謨ｵ蠑ｾ・亥ｼｾ蟷慕畑・峨・繝槭ぞ繝ｳ繧ｿ・剰ｵ､邉ｻ
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 14, GetColor(255, 0, 128), TRUE); // 繧ｪ繝ｼ繝ｩ
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 10, GetColor(255, 100, 200), TRUE); // 螟匁棧
        DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 6, GetColor(255, 255, 255), TRUE); // 繧ｳ繧｢
    }
}

void EnemyBullet::OnTrigger(Collider* collider, Collider* check) 
{
    if(check!=nullptr&&check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == tag2D_BarierPla)
        {
            // バリア側に衝突を通知してカウントを進めさせる
            check->GetParentObject()->OnTrigger(check, collider);
            Kill();
            return;//playerとバリアに同時に当たった時にバリアを優先するため、プレイヤーへのダメージをスキップ
        }
	}
    if (check != nullptr && check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == Tag2D_Player) {
            Player* player = dynamic_cast<Player*>(check->GetParentObject());
            if (player != nullptr) {
                player->TakeDamage(1);
                if (m_isStunBullet) {
                    player->Stun(60); // 1遘帝俣繧ｹ繧ｿ繝ｳ
                }
            }
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
