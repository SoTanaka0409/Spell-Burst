#include "Boss.h"
#include "CapsuleCollider.h"
#include "Bullet.h"
#include "MeleeAttack.h"
#include "SpecialBullet.h"
#include "Player.h"
#include "EnemyBullet.h"
#include "ObjectManager.h"
#include "Math.h"
#include "BulletManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Master.h"
#include "ResultScene.h"
#include "GameScene.h"
#include "Enemy.h"
#include <DxLib.h>
#include <cmath>
#include <cstdlib>
#include "ResourceManager.h"
#include "Utility.h"
#include "GameScene.h"
#include "ExplosionParticle.h"
#include "PlayerHomingBullet.h"
#include "SoundManager.h"

Boss::Boss(float x, float y, int bossType)
    : Object2D(VGet(x, y, 0.0f))
    , mpCollider(nullptr)
{
    SetTag(Tag2D_Enemy);
    mvPosition.x = x;
    mvPosition.y = y;
    m_bossType = bossType;
    if (m_bossType == 1) {
        m_speed = 1.5f;
        m_hp = 60; // 隴夲ｽｱ隴・ｽｹ鬯夲ｽｨ邵ｺ・ｪ邵ｺ・ｮ邵ｺ・ｧHP陞溷｣ｹ・・
    } else if (m_bossType == 2) {
        m_speed = 2.0f;
        m_hp = 80;
    } else {
        m_speed = 2.5f;
        m_hp = 150;
    }

    if (GameScene::s_currentStage == 2) {
        m_hp = static_cast<int>(m_hp * 1.3f);
    } else if (GameScene::s_currentStage == 3) {
        m_hp = static_cast<int>(m_hp * 1.5f);
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

// 郢晢ｽｩ郢晢ｽｳ郢昶ぎ郢晞§・ｻ陷崎ｼ斐・郢ｧ・ｿ郢晢ｽｼ郢ｧ・ｲ郢昴・繝ｨ陟趣ｽｧ隶灘生・定ｭ厄ｽｴ隴・ｽｰ邵ｺ蜷ｶ・玖怎・ｦ騾・・
// 騾包ｽｻ鬮ｱ・｢闕ｳ莨∃壹・蛹ｻ繝ｻ郢晢ｽｬ郢ｧ・､郢晢ｽ､郢晢ｽｼ邵ｺ譴ｧ蛻､隰ｦ繝ｻ・�郢ｧ繝ｻ笘・ｸｺ繝ｻ・ｯ繝ｻ蟲・・蟲ｨﾂｰ郢ｧ蟲ｨﾎ帷ｹ晢ｽｳ郢昶ぎ郢晉ｸｺ・ｫ隹ｺ・｡邵ｺ・ｮ驕假ｽｻ陷榊供繝ｻ郢ｧ蜻茨ｽｱ・ｺ郢ｧ竏壺穐邵ｺ蜷ｶ竄ｬ繝ｻ
void Boss::SelectNewTarget() {
    // Top half boundary: X between 100 and 1180, Y between 80 and 260
    m_targetX = 100.0f + static_cast<float>(rand() % 1080);
    m_targetY = 80.0f + static_cast<float>(rand() % 180);
}

// 郢晄㈱縺帷ｸｺ・ｮ雎亥ｼｱ繝ｵ郢晢ｽｬ郢晢ｽｼ郢晉ｸｺ・ｮ隴厄ｽｴ隴・ｽｰ陷・ｽｦ騾・・
// 雎・ｽｻ闔�・｡雋肴ｳ後・闕ｳ・ｭ邵ｺ・ｪ郢ｧ謌托ｽｸ鄙ｫ竊鍋ｹ晁ｼ斐♂郢晢ｽｼ郢晏ｳｨ縺・ｹｧ・ｦ郢晏現・�邵ｲ竏ｫ蜃ｽ陝・・ｽｸ・ｭ邵ｺ・ｪ郢ｧ蟲ｨ縺｡郢晢ｽｼ郢ｧ・ｲ郢昴・繝ｨ陟趣ｽｧ隶灘生竊楢惺莉｣ﾂｰ邵ｺ・｣邵ｺ・ｦ驕假ｽｻ陷崎ｼ費ｼ�邵ｺ・ｪ邵ｺ蠕鯉ｽ芽�托ｽｾ陝ｷ霈費ｽ定ｬｦ繝ｻ笆�邵ｺ・ｾ邵ｺ蜷ｶ竄ｬ繝ｻ
void Boss::Update() {
    if (m_isDying) {
        m_deathTimer--;
        mvPosition.y -= 1.0f; // Move upwards while dying
        mvPosition = VGet(mvPosition.x, mvPosition.y, 0.0f);
        if (m_deathTimer <= 0) {
            Kill();
        }
        return; // Skip normal behavior
    }

    if (m_invincibleTimer > 0) {
        m_invincibleTimer--;
    }

    // 隴帚ぎ驍ｨ繧・・郢ｧ・ｹ繝ｻ蛹ｻ縺｡郢ｧ・､郢昴・繝ｻ蟲ｨ繝ｻ邵ｺ・ｿ邵ｲ繝ｻ驕俶慣・ｼ繝ｻ00郢晁ｼ釆樒ｹ晢ｽｼ郢昴・蟲ｨ笙邵ｺ髦ｪ竊・驕伜ｸ昜ｿ｣繝ｻ繝ｻ20郢晁ｼ釆樒ｹ晢ｽｼ郢昴・閾･笏瑚ｬｨ・ｵ邵ｺ・ｫ邵ｺ・ｪ郢ｧ繝ｻ
    if (m_bossType == 3) {
        m_invincibleCycleTimer++;
        if (m_invincibleCycleTimer >= 300) {
            m_invincibleTimer = 120; // 2 seconds invincibility
            m_invincibleCycleTimer = 0;
            
            // 霎滂ｽ｡隰ｨ・ｵ陋ｹ謔ｶ竊定惺譴ｧ蜃ｾ邵ｺ・ｫ陷ｿ謔ｶ・願淦・ｻ邵ｺ髦ｪ・定愾・ｬ陜溘・
            new Enemy(mvPosition.x - 60.0f, mvPosition.y + 60.0f, 1);
            new Enemy(mvPosition.x + 60.0f, mvPosition.y + 60.0f, 1);
        }
    } else {
        m_invincibleTimer = 0;
        m_invincibleCycleTimer = 0;
    }

    // Move towards current target
    float dx = m_targetX - mvPosition.x;
    float dy = m_targetY - mvPosition.y;
    float dist = std::sqrt(dx * dx + dy * dy);

    if (dist < 15.0f) {
        SelectNewTarget();
    } else {
        mvPosition.x += (dx / dist) * m_speed * Utility::TimeScale;
        mvPosition.y += (dy / dist) * m_speed * Utility::TimeScale;
    }

    mvPosition = VGet(mvPosition.x, mvPosition.y, 0.0f);

    if (mpCollider) {
        mpCollider->mvPosition = mvPosition;
        mpCollider->mvPosition2 = mvPosition;
    }

    // 隰ｾ・ｻ隰ｦ繝ｻ笏髫輔・
    m_attackTimer++;
    if (m_bossType == 1) {
        if (m_attackTimer >= 60) {
            m_attackTimer = 0;
            ShootSimpleBarrage();
        }
    } else if (m_bossType == 2) {
        if (m_attackTimer >= 120) {
            m_attackTimer = 0;
            ShootBouncingBarrage();
        }
    } else {
        if (m_attackTimer >= 100) { // 騾具ｽｺ陝・・菫｣鬮ｫ譁撰ｽ帝￥・ｭ邵ｺ謫ｾ・ｼ繝ｻ00 -> 40繝ｻ迚呻ｽｼ・ｾ陝ｷ蜍溷密
            m_attackTimer = 0;
            
            // 繧ｹ繝・・繧ｸ3縺ｮ蝣ｴ蜷医・遒ｺ邇・〒繧ｹ繝壹Ν繧ｫ繝ｼ繝臥匱蜍・
            bool usedSpellCard = false;
            if (GameScene::s_currentStage == 3) {
                if ((rand() % 100) < 20) { // 20%縺ｮ遒ｺ邇・
                    ShootSpellCardBarrage();
                    usedSpellCard = true;
                }
            }
            
            if (!usedSpellCard) {
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
}

// 陷茨ｽｨ隴・ｽｹ闖ｴ讎奇ｽｼ・ｾ陝ｷ霈費ｽ定ｬｦ繝ｻ笆ｽ陷・ｽｦ騾・・・ｼ蛹ｻ縺帷ｹ晏｣ｹﾎ晉ｹｧ・ｫ郢晢ｽｼ郢晁崟・｢・ｨ繝ｻ螢ｽ・ｸ・ｦ陝ｾ・ｻ邵ｺ讎奇ｽｼ・ｾ陝ｷ蛹・ｽｼ繝ｻ
void Boss::ShootRadialBarrage() {
    const float PI = 3.14159265f;
    const int bulletCount = 36; // 陟托ｽｾ隰ｨ・ｰ郢ｧ雋樞ぎ讎奇ｽ｢繝ｻ
    static float spiralAngle = 0.0f;
    spiralAngle += 0.15f; // 騾具ｽｺ陝・・・・ｸｺ・ｨ邵ｺ・ｨ髫苓ｲ橸ｽｺ・ｦ郢ｧ蛛ｵ笘・ｹｧ蟲ｨ・�邵ｺ・ｦ雋ゑｽｦ陝ｾ・ｻ邵ｺ髦ｪ竊鍋ｸｺ蜷ｶ・・

    bool reflect = (m_lives == 2);
    for (int i = 0; i < bulletCount; i++) {
        float angle = spiralAngle + (i * 2.0f * PI) / bulletCount;
        float dx = std::cos(angle);
        float dy = std::sin(angle);
        new EnemyBullet(mvPosition.x, mvPosition.y, dx, dy, 2.5f, reflect); // 陟托ｽｾ鬨ｾ貅假ｽ帝梨・ｽ邵ｺ・ｨ邵ｺ蜉ｱ窶ｻ鬩包ｽｿ邵ｺ莉｣・・ｸｺ蜷ｶ・･
    }
}

// 隰・・諞ｾ陟托ｽｾ陝ｷ霈費ｽ定ｬｦ繝ｻ笆ｽ陷・ｽｦ騾・・・ｼ蛹ｻ縺帷ｹ晏｣ｹﾎ晉ｹｧ・ｫ郢晢ｽｼ郢晁崟・｢・ｨ繝ｻ螢ｼ・､螢ｼ・ｱ・､闔�・､陝ｾ・ｮ陟托ｽｾ陝ｷ蛹・ｽｼ繝ｻ
void Boss::ShootFanBarrage() {
    const float PI = 3.14159265f;
    const int bulletCount = 15;
    bool reflect = (m_lives == 2);
    // 騾ｵ貊会ｽｸ荵晢ｽ定叉・ｭ陟｢繝ｻ竊楢�弱・・ｯ繝ｻ蟲・ｸｺ・ｫ隰ｦ繝ｻ笆ｽ
    float baseAngle = PI / 2.0f;
    
    // 2陞ｻ・､邵ｺ・ｮ鬨ｾ貅ｷ・ｺ・ｦ邵ｺ遒・ｼ・ｸｺ繝ｻ・ｼ・ｾ陝ｷ霈費ｽ定惺譴ｧ蜃ｾ邵ｺ・ｫ隰ｦ繝ｻ笆ｽ
    for (int layer = 0; layer < 4; layer++) {
        float speed = 2.0f + layer * 1.5f; // 鬩輔・・櫁�托ｽｾ邵ｺ・ｨ鬨ｾ貅假ｼ櫁�托ｽｾ
        for (int i = -bulletCount/2; i <= bulletCount/2; i++) {
            float angle = baseAngle + (i * 8.0f * PI / 180.0f);
            float dx = std::cos(angle);
            float dy = std::sin(angle);
            new EnemyBullet(mvPosition.x, mvPosition.y, dx, dy, speed, reflect);
        }
    }
}

// 髢ｾ・ｪ隶匁ｺｽ貍∫ｸｺ繝ｻ・ｼ・ｾ陝ｷ霈費ｽ定ｬｦ繝ｻ笆ｽ陷・ｽｦ騾・・
// 郢晏干ﾎ樒ｹｧ・､郢晢ｽ､郢晢ｽｼ邵ｺ・ｮ霑ｴ・ｾ陜ｨ・ｨ闖ｴ蜥ｲ・ｽ・ｮ郢ｧ螳夲ｽｨ閧ｲ・ｮ蜉ｱ・�邵ｲ竏壺落邵ｺ阮吮・陷ｷ莉｣ﾂｰ邵ｺ・｣邵ｺ・ｦ3WAY邵ｺ・ｮ陟托ｽｾ郢ｧ蝣､蛹ｱ陝・・・�邵ｺ・ｾ邵ｺ蜷ｶ竄ｬ繝ｻ
void Boss::ShootTargetedBarrage() {
    const float PI = 3.14159265f;
    Player* player = dynamic_cast<Player*>(Master::sceneManager->GetCurrentScene()->GetObjectManager()->GetObject2DByTag(Tag2D_Player));
    float targetX = mvPosition.x;
    float targetY = mvPosition.y + 200.0f; // Default targeted direction (downwards)

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
    } else {
        dx = 0.0f;
        dy = 1.0f;
    }

    float baseAngle = std::atan2(dy, dx);

    // 陝・・竊・WAY髢ｾ・ｪ隶匁ｺｽ貍∫ｸｺ繝ｻ
    for (int i = -2; i <= 2; i++) {
        float angle = baseAngle + (i * 5.0f * PI / 180.0f);
        new EnemyBullet(mvPosition.x, mvPosition.y, std::cos(angle), std::sin(angle), 3.5f);
    }
    // 陝・ｻ｣・�鬩輔・・櫁�弱・・∫ｸｺ・ｮ3WAY郢ｧ繧九裟邵ｺ・ｭ郢ｧ繝ｻ
    for (int i = -1; i <= 1; i++) {
        float angle = baseAngle + (i * 12.0f * PI / 180.0f);
        new EnemyBullet(mvPosition.x, mvPosition.y, std::cos(angle), std::sin(angle), 2.5f);
    }
}

void Boss::ShootSimpleBarrage() {
    const float PI = 3.14159265f;
    
    // 郢晢ｽｩ郢晢ｽｳ郢昶ぎ郢晉ｸｺ・ｪ陜難ｽｺ雋・・・ｧ蛛ｵﾂｰ郢ｧ蟲ｨ竄ｬ竏晏ｱ∬ｭ・ｽｹ繝ｻ莠･繝ｻ隴・ｽｹ闖ｴ謳ｾ・ｼ蟲ｨ竊・騾具ｽｺ邵ｺ・ｮ陟托ｽｾ郢ｧ蝣､蛹ｱ陝・・笘・ｹｧ繝ｻ
    // 60郢晁ｼ釆樒ｹ晢ｽｼ郢昴・繝ｻ驕伜ｸ昜ｿ｣繝ｻ蟲ｨ繝ｻ邵ｺ譏ｴ繝ｻ邵ｺ・ｾ邵ｺ・ｾ騾ｶ・ｴ鬨ｾ・ｲ邵ｺ蜉ｱ竄ｬ竏壺落邵ｺ・ｮ陟輔・20郢晁ｼ釆樒ｹ晢ｽｼ郢昴・繝ｻ驕伜ｸ昜ｿ｣繝ｻ蟲ｨ繝ｻ郢晢ｽｬ郢ｧ・､郢晢ｽ､郢晢ｽｼ郢ｧ螳夲ｽｿ・ｽ陝・ｽｾ邵ｺ蜷ｶ・・
    float baseAngle = static_cast<float>(rand() % 360) * PI / 180.0f;
    for (int i = 0; i < 5; i++) {
        float angle = baseAngle + (i * 360.0f / 5.0f * PI / 180.0f);
        float bx = std::cos(angle);
        float by = std::sin(angle);
        // speed: 3.5f, canReflect: false, stun: false, homingFrames: 120, homingDelayFrames: 60
        new EnemyBullet(mvPosition.x, mvPosition.y, bx, by, 3.5f, false, false, 120, 60);
    }
}

void Boss::ShootBouncingBarrage() {
    const float PI = 3.14159265f;
    for (int i = 0; i < 6; i++) {
        float angle = (i * 2.0f * PI) / 6.0f;
        float dx = std::cos(angle);
        float dy = std::sin(angle);
        // pass canReflect = true
        new EnemyBullet(mvPosition.x, mvPosition.y, dx, dy, 4.5f, true);
    }
}

void Boss::ShootSpellCardBarrage() {
    const float PI = 3.14159265f;
    // 蟾ｨ螟ｧ縺ｪ蠑ｾ繧貞・蠖｢縺ｫ螟ｧ驥上↓謾ｾ縺｡縲√＆繧峨↓縺昴ｌ縺悟渚蟆・☆繧具ｼ医せ繝壹Ν繧ｫ繝ｼ繝臥ｴ壹・髮｣譏灘ｺｦ・・
    for (int i = 0; i < 24; i++) {
        float angle = (i * 2.0f * PI) / 24.0f;
        float dx = std::cos(angle);
        float dy = std::sin(angle);
        new EnemyBullet(mvPosition.x, mvPosition.y, dx, dy, 2.0f, true); // 蜿榊ｰ・☆繧矩≦縺・ｼｾ
    }
    // 譎る俣蟾ｮ縺ｧ騾溘＞蠑ｾ繧呈叛縺､
    for (int i = 0; i < 12; i++) {
        float angle = (i * 2.0f * PI) / 12.0f + 0.5f;
        float dx = std::cos(angle);
        float dy = std::sin(angle);
        new EnemyBullet(mvPosition.x, mvPosition.y, dx, dy, 5.0f, false);
    }
}

// 郢昶ぎ郢晢ｽ｡郢晢ｽｼ郢ｧ・ｸ郢ｧ雋槫･ｳ邵ｺ莉｣・玖怎・ｦ騾・・
// 郢晏干ﾎ樒ｹｧ・､郢晢ｽ､郢晢ｽｼ邵ｺ・ｮ隰ｾ・ｻ隰ｦ繝ｻ竊定�冶侭笳・ｸｺ・｣邵ｺ貊・怙邵ｺ・ｫ陷ｻ・ｼ邵ｺ・ｰ郢ｧ蠕娯ぎ・蘖郢ｧ蜻茨ｽｸ蟶呻ｽ臥ｸｺ蜉ｱ竏ｪ邵ｺ蜷ｶ竄ｬ繝ｻ闔会ｽ･闕ｳ荵昶・邵ｺ・ｪ邵ｺ・｣邵ｺ貅假ｽ芽ｱ・ｽｻ闔�・｡雋肴ｳ後・(m_isDying)郢ｧ蟶晏ｹ戊沂荵晢ｼ�邵ｺ・ｾ邵ｺ蜷ｶ竄ｬ繝ｻ
void Boss::TakeDamage(int damage) {
    if (m_isDying || m_invincibleTimer > 0) return;

    // m_lives 邵ｺ・ｮ隰・唱陌夊ｲょｸ幢ｽｰ莉｣ﾎ溽ｹｧ・ｸ郢昴・縺醍ｹｧ雋樒ｎ鬮ｯ・､邵ｺ蜉ｱ竄ｬ繝ｻ邵ｺ・ｫ邵ｺ・ｪ邵ｺ・｣邵ｺ貊灘・邵ｺ・ｮ邵ｺ・ｿ陋ｻ・､陞ｳ繝ｻ

    m_hp -= damage;
    if (m_hp <= 0) {
        m_hp = 0;
        m_lives--;
        
        // 繝懊せ縺ｮ蜷・ｽ｢諷九ｒ蛟偵＠縺滂ｼ医≠繧九＞縺ｯ螳悟・縺ｫ蛟偵＠縺滂ｼ画凾縺ｫ縺吶∋縺ｦ縺ｮ謨ｵ蠑ｾ繧呈ｶ医☆
        std::vector<Object2D*> bullets = Master::sceneManager->GetCurrentScene()->GetObjectManager()->GetObject2DListByTag(Tag2D_EnemyBullet);
        for (auto* b : bullets) {
            b->SetDeleteFlag(true);
        }
        
        if (m_lives > 0) {
            // Heal back to max and become invincible for a while
            m_hp = m_maxHp;
            m_invincibleTimer = 180; // 3 seconds invincibility on phase change
        } else {
            m_isDying = true;
            SoundManager::GetInstance()->PlaySE("Resource/se_boss_die.wav");
            m_deathTimer = 180; // 3 seconds flash and fly up
            if (mpCollider) {
                mpCollider->SetDeleteFlag(true); // Disable collision
            }
            
            // Clear all enemy bullets
            Scene* currentScene = Master::sceneManager->GetCurrentScene();
            if (currentScene) {
                auto bullets = currentScene->GetObjectManager()->GetObject2DListByTag(Tag2D_EnemyBullet);
                for (auto* b : bullets) {
                    b->SetDeleteFlag(true);
                }
                // Heal player
                Player* p = dynamic_cast<Player*>(currentScene->GetObjectManager()->GetObject2DByTag(Tag2D_Player));
                if (p) p->Heal(3);
            }    mpCollider = nullptr;

            GameScene* gs = dynamic_cast<GameScene*>(Master::sceneManager->GetCurrentScene());
            if (gs != nullptr) {
                gs->AddScreenShake(180, 20.0f);
                gs->AddHitStop(30);
            }

            for(int i = 0; i < 40; i++) {
                float angle = static_cast<float>(rand() % 360) * 3.14159f / 180.0f;
                float speed = 3.0f + static_cast<float>(rand() % 50) / 10.0f;
                int life = 60 + (rand() % 60);
                float size = 15.0f + static_cast<float>(rand() % 40);
                int color = GetColor(255, 100 + rand() % 155, 0);
                new ExplosionParticle(mvPosition.x, mvPosition.y, speed, angle, color, life, size);
            }
        }
    }
}

// 陞ｳ謔溘・邵ｺ・ｫ雎ｸ蝓滂ｽｻ繝ｻ・・ｸｺ蟶呻ｽ玖怎・ｦ騾・・
// 雎・ｽｻ闔�・｡雋肴ｳ後・邵ｺ讙趣ｽｵ繧・ｽ冗ｸｺ・｣邵ｺ貅ｷ・ｾ蠕娯・陷ｻ・ｼ邵ｺ・ｰ郢ｧ蠕個竏壹＃郢晢ｽｼ郢晢ｿｽ郢ｧ・ｯ郢晢ｽｪ郢ｧ・｢繝ｻ繝ｻesultScene邵ｺ・ｸ邵ｺ・ｮ驕假ｽｻ髯ｦ魃会ｽｼ蟲ｨ・堤ｹ晏現ﾎ懃ｹｧ・ｬ郢晢ｽｼ邵ｺ蜉ｱ竏ｪ邵ｺ蜷ｶﾂ繝ｻ
void Boss::Kill() {
    m_isActive = false;
    SetDeleteFlag(true);
    if (mpCollider) {
        mpCollider->SetDeleteFlag(true);
    }
    // Transition to victory result screen only if it's the phase 3 boss
    if (m_bossType == 3) {
        ResultScene::s_isVictory = true;
          GameScene::s_isTimeAttackActive = false;
        Master::sceneManager->SetNextScene(SceneManager::SCENE_RESULT);
    }
}

// 闔画じ繝ｻ郢ｧ・ｪ郢晄じ縺夂ｹｧ・ｧ郢ｧ・ｯ郢晏現竊帝ｩ･髦ｪ竊醍ｸｺ・｣邵ｺ・ｦ邵ｺ繝ｻ・玖ｭ弱ｅ繝ｻ陷・ｽｦ騾・・・ｼ莠･・ｽ阮吮螺郢ｧ髮∵・陞ｳ螢ｹ縺・ｹ晏生ﾎｦ郢晁肩・ｼ繝ｻ
// 郢晏干ﾎ樒ｹｧ・､郢晢ｽ､郢晢ｽｼ邵ｺ・ｮ陟托ｽｾ繝ｻ逎ｯﾂ螢ｼ・ｸ・ｸ陟托ｽｾ邵ｲ竏ｬ・ｿ隨ｬ逎∫ｸｲ竏晢ｽｿ繝ｻ・ｮ・ｺ隰堋繝ｻ蟲ｨ竊定�冶侭笳・ｸｺ・｣邵ｺ貅ｷ・ｽ・ｴ陷ｷ蛹ｻ竊鍋ｸｲ竏ｬ繝ｻ髴・ｽｫ邵ｺ・ｮTakeDamage郢ｧ雋樔ｻ也ｸｺ・ｳ陷・ｽｺ邵ｺ蜉ｱ竏ｪ邵ｺ蜷ｶﾂ繝ｻ
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
                    } else {
                        PlayerHomingBullet* phb = dynamic_cast<PlayerHomingBullet*>(parent);
                        if (phb != nullptr) {
                            damage = phb->GetDamage();
                            phb->Kill();
                        }
                    }
                }
            }
            TakeDamage(damage);
        }
    }
}

// 隰�蜀怜愛陷・ｽｦ騾・・
// 郢晄㈱縺帷ｸｺ・ｮ騾包ｽｻ陷剃ｸ奇ｽ定ｬ�蜀怜愛邵ｺ蜉ｱ竏ｪ邵ｺ蜷ｶﾂ繧茨ｽｭ・ｻ闔�・｡雋肴ｳ後・闕ｳ・ｭ邵ｺ・ｯ郢昶・縺咲ｹ昶・縺咲ｸｺ・ｨ霓､・ｹ雋翫・・・ｸｺ蟶卍竏ｬ諱ｭ髫ｱ讒ｭ繝ｻ郢晢ｽ｡郢昴・縺晉ｹ晢ｽｼ郢ｧ・ｸ郢ｧ螳夲ｽ｡・ｨ驕会ｽｺ邵ｺ蜉ｱ竏ｪ邵ｺ蜷ｶﾂ繝ｻ
void Boss::Draw() {
    if (!m_isActive) return;

    int s_bossGraphHandle = ResourceManager::GetInstance()->GetGraph("Resource/boss.png");

    if (s_bossGraphHandle != -1) {
        if (!m_isDying || (m_deathTimer / 5) % 2 == 0) {
            if (m_invincibleTimer > 0) {
                // 辟｡謨ｵ繝舌Μ繧｢縺ｮ謠冗判
                SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100 + (m_invincibleTimer % 20) * 5);
                DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 110, GetColor(200, 50, 255), TRUE); // 蝪励ｊ縺､縺ｶ縺・
                SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
                DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 110, GetColor(255, 150, 255), FALSE); // 邵∝叙繧・
                DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 107, GetColor(255, 255, 255), FALSE); // 蜀・・縺ｮ邵∝叙繧・
                
                // 繝懊せ譛ｬ菴薙・騾城℃
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
