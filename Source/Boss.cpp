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
        m_hp = 60; // è­šï½±è­E½¹é¬šï½¨ç¸ºEªç¸ºE®ç¸ºE§HPèŸå£¹EE
    } else if (m_bossType == 2) {
        m_speed = 2.0f;
        m_hp = 80;
    } else {
        m_speed = 2.5f;
        m_hp = 150;
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

// ç¹ï½©ç¹ï½³ç¹â‚¬ç¹é˜E»èœè¼”ãEç¹§E¿ç¹ï½¼ç¹§E²ç¹ãEãƒ¨è ï½§è®“å¶E’è­–ï½´è­E½°ç¸ºå¶E‹èœƒE¦é€EE
// é€•ï½»é«±E¢è³ä¼ÎšãEåŒ»ãƒ»ç¹ï½¬ç¹§E¤ç¹ï½¤ç¹ï½¼ç¸ºæ¢§åˆ¤è¬¦ãƒ»E ç¹§ãƒ»â˜E¸ºãƒ»E¯ãƒ»å³EEå³¨Â°ç¹§å³¨Î›ç¹ï½³ç¹â‚¬ç¹ç¸ºE«è°ºE¡ç¸ºE®é˜ï½»èœå‹Ÿãƒ»ç¹§å‘ˆï½±Eºç¹§âˆšâˆªç¸ºå¶â‚¬ãƒ»
void Boss::SelectNewTarget() {
    // Top half boundary: X between 100 and 1180, Y between 80 and 260
    m_targetX = 100.0f + static_cast<float>(rand() % 1080);
    m_targetY = 80.0f + static_cast<float>(rand() % 180);
}

// ç¹æ‡Šã›ç¸ºE®è±ˆå¼±ãƒµç¹ï½¬ç¹ï½¼ç¹ç¸ºE®è­–ï½´è­E½°èœE½¦é€EE
// è±E½»è E¡è²æ³ŒãEè³E­ç¸ºEªç¹§æˆ‘ï½¸ç¿«â†“ç¹è¼”ã‰ç¹ï½¼ç¹å³¨ãE¹§E¦ç¹åŒ»E ç¸²âˆ«å‡½èŸE€E½¸E­ç¸ºEªç¹§å³¨ã¡ç¹ï½¼ç¹§E²ç¹ãEãƒ¨è ï½§è®“å¶â†“èœ·ä»£Â°ç¸ºE£ç¸ºE¦é˜ï½»èœè¼”ï¼ ç¸ºEªç¸ºå¾Œï½‰è ‘ï½¾èŸ·è¼”ï½’è¬¦ãƒ»â– ç¸ºE¾ç¸ºå¶â‚¬ãƒ»
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

    // è­›â‚¬é‚¨ã‚EEç¹§E¹ãƒ»åŒ»ã¡ç¹§E¤ç¹ãEãƒ»å³¨ãƒ»ç¸ºE¿ç¸²ãƒ»é˜æŠµE¼ãƒ»00ç¹è¼”Îç¹ï½¼ç¹ãEå³¨â™€ç¸ºé˜ªâ†Eé˜å¸ä¿£ãƒ»ãƒ»20ç¹è¼”Îç¹ï½¼ç¹ãEè‡¥â”Œè¬¨Eµç¸ºE«ç¸ºEªç¹§ãƒ»
    if (m_bossType == 3) {
        m_invincibleCycleTimer++;
        if (m_invincibleCycleTimer >= 300) {
            m_invincibleTimer = 120; // 2 seconds invincibility
            m_invincibleCycleTimer = 0;
            
            // è¾Ÿï½¡è¬¨Eµè›¹æ‚¶â†’èœ·æ¢§å‡¾ç¸ºE«èœ¿æ‚¶EŠèŸ¾E»ç¸ºé˜ªE’èœ¿E¬èŸãE
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

    // è¬¾E»è¬¦ãƒ»â”€éš•ãE
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
        if (m_attackTimer >= 100) { // é€‹ï½ºèŸEEä¿£é««æ–ï½’éE­ç¸ºæ“¾E¼ãƒ»00 -> 40ãƒ»ç‰™ï½¼E¾èŸ·å‹Ÿå–§
            m_attackTimer = 0;
            
            // ã‚¹ãƒEEã‚¸3ã®å ´åˆãEç¢ºçE§ã‚¹ãƒšãƒ«ã‚«ãƒ¼ãƒ‰ç™ºå‹E
            bool usedSpellCard = false;
            if (GameScene::s_currentStage == 3) {
                if ((rand() % 100) < 20) { // 20%ã®ç¢ºçE
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

// èœˆï½¨è­E½¹è´æ¦Šï½¼E¾èŸ·è¼”ï½’è¬¦ãƒ»â–½èœE½¦é€EEE¼åŒ»ã›ç¹å£¹Îç¹§E«ç¹ï½¼ç¹è›¾E¢E¨ãƒ»å£½E¸E¦èŸ¾E»ç¸ºæ¦Šï½¼E¾èŸ·åŒE½¼ãƒ»
void Boss::ShootRadialBarrage() {
    const float PI = 3.14159265f;
    const int bulletCount = 36; // è ‘ï½¾è¬¨E°ç¹§è²â‚¬æ¦Šï½¢ãƒ»
    static float spiralAngle = 0.0f;
    spiralAngle += 0.15f; // é€‹ï½ºèŸEEEE¸ºE¨ç¸ºE¨éš—è²ï½ºE¦ç¹§åµâ˜E¹§å³¨E ç¸ºE¦è²‚ï½¦èŸ¾E»ç¸ºé˜ªâ†“ç¸ºå¶EE

    bool reflect = (m_lives == 2);
    for (int i = 0; i < bulletCount; i++) {
        float angle = spiralAngle + (i * 2.0f * PI) / bulletCount;
        float dx = std::cos(angle);
        float dy = std::sin(angle);
        new EnemyBullet(mvPosition.x, mvPosition.y, dx, dy, 2.5f, reflect); // è ‘ï½¾é¨¾æº˜ï½’é—œE½ç¸ºE¨ç¸ºåŠ±â€»é©•ï½¿ç¸ºä»£EE¸ºå¶E¥
    }
}

// è¬EEæ†¾è ‘ï½¾èŸ·è¼”ï½’è¬¦ãƒ»â–½èœE½¦é€EEE¼åŒ»ã›ç¹å£¹Îç¹§E«ç¹ï½¼ç¹è›¾E¢E¨ãƒ»å£¼E¤å£¼E±E¤è E¤èŸ¾E®è ‘ï½¾èŸ·åŒE½¼ãƒ»
void Boss::ShootFanBarrage() {
    const float PI = 3.14159265f;
    const int bulletCount = 15;
    bool reflect = (m_lives == 2);
    // é€µæ»‰ï½¸ä¹ï½’è³E­è ¢ãƒ»â†“è ãEE¯ãƒ»å³E¸ºE«è¬¦ãƒ»â–½
    float baseAngle = PI / 2.0f;
    
    // 2è»E¤ç¸ºE®é¨¾æº·EºE¦ç¸ºç¢E¼E¸ºãƒ»E¼E¾èŸ·è¼”ï½’èœ·æ¢§å‡¾ç¸ºE«è¬¦ãƒ»â–½
    for (int layer = 0; layer < 4; layer++) {
        float speed = 2.0f + layer * 1.5f; // é©•ãEEè ‘ï½¾ç¸ºE¨é¨¾æº˜ï¼è ‘ï½¾
        for (int i = -bulletCount/2; i <= bulletCount/2; i++) {
            float angle = baseAngle + (i * 8.0f * PI / 180.0f);
            float dx = std::cos(angle);
            float dy = std::sin(angle);
            new EnemyBullet(mvPosition.x, mvPosition.y, dx, dy, speed, reflect);
        }
    }
}

// é–¾Eªè®–æº½æ¼ç¸ºãƒ»E¼E¾èŸ·è¼”ï½’è¬¦ãƒ»â–½èœE½¦é€EE
// ç¹åŠ±Îç¹§E¤ç¹ï½¤ç¹ï½¼ç¸ºE®è¿´E¾è¨E¨è´å’²E½E®ç¹§å®šï½¨è‚²E®åŠ±E ç¸²âˆšâ—ç¸ºè–™âEèœ·ä»£Â°ç¸ºE£ç¸ºE¦3WAYç¸ºE®è ‘ï½¾ç¹§å ¤åŒ±èŸEEE ç¸ºE¾ç¸ºå¶â‚¬ãƒ»
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

    // èŸEEâ†EWAYé–¾Eªè®–æº½æ¼ç¸ºãƒ»
    for (int i = -2; i <= 2; i++) {
        float angle = baseAngle + (i * 5.0f * PI / 180.0f);
        new EnemyBullet(mvPosition.x, mvPosition.y, std::cos(angle), std::sin(angle), 3.5f);
    }
    // èŸE»£E é©•ãEEè ãEEç¸ºE®3WAYç¹§ã‚‹ã¾ç¸ºE­ç¹§ãƒ»
    for (int i = -1; i <= 1; i++) {
        float angle = baseAngle + (i * 12.0f * PI / 180.0f);
        new EnemyBullet(mvPosition.x, mvPosition.y, std::cos(angle), std::sin(angle), 2.5f);
    }
}

void Boss::ShootSimpleBarrage() {
    const float PI = 3.14159265f;
    
    // ç¹ï½©ç¹ï½³ç¹â‚¬ç¹ç¸ºEªè“ï½ºè²EEE§åµÂ°ç¹§å³¨â‚¬âˆå±è­E½¹ãƒ»äº¥ãƒ»è­E½¹è´æ¾E¼å³¨â†Eé€‹ï½ºç¸ºE®è ‘ï½¾ç¹§å ¤åŒ±èŸEEâ˜E¹§ãƒ»
    // 60ç¹è¼”Îç¹ï½¼ç¹ãEãƒ»é˜å¸ä¿£ãƒ»å³¨ãƒ»ç¸ºæ˜´ãƒ»ç¸ºE¾ç¸ºE¾é€¶E´é¨¾E²ç¸ºåŠ±â‚¬âˆšâ—ç¸ºE®è •ãE20ç¹è¼”Îç¹ï½¼ç¹ãEãƒ»é˜å¸ä¿£ãƒ»å³¨ãƒ»ç¹ï½¬ç¹§E¤ç¹ï½¤ç¹ï½¼ç¹§å®šï½¿E½èŸE½¾ç¸ºå¶EE
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
    // å·¨å¤§ãªå¼¾ã‚’åEå½¢ã«å¤§é‡ã«æ”¾ã¡ã€ã•ã‚‰ã«ãã‚ŒãŒåå°E™ã‚‹ï¼ˆã‚¹ãƒšãƒ«ã‚«ãƒ¼ãƒ‰ç´šãEé›£æ˜“åº¦EE
    for (int i = 0; i < 24; i++) {
        float angle = (i * 2.0f * PI) / 24.0f;
        float dx = std::cos(angle);
        float dy = std::sin(angle);
        new EnemyBullet(mvPosition.x, mvPosition.y, dx, dy, 2.0f, true); // åå°E™ã‚‹é…ãE¼¾
    }
    // æ™‚é–“å·®ã§é€Ÿã„å¼¾ã‚’æ”¾ã¤
    for (int i = 0; i < 12; i++) {
        float angle = (i * 2.0f * PI) / 12.0f + 0.5f;
        float dx = std::cos(angle);
        float dy = std::sin(angle);
        new EnemyBullet(mvPosition.x, mvPosition.y, dx, dy, 5.0f, false);
    }
}

// ç¹â‚¬ç¹ï½¡ç¹ï½¼ç¹§E¸ç¹§è²å¥³ç¸ºä»£E‹èœƒE¦é€EE
// ç¹åŠ±Îç¹§E¤ç¹ï½¤ç¹ï½¼ç¸ºE®è¬¾E»è¬¦ãƒ»â†’è –è–™â—E¸ºE£ç¸ºæ»Eœ€ç¸ºE«èœ»E¼ç¸ºE°ç¹§å¾Œâ‚¬EŸPç¹§å‘ˆï½¸å¸™ï½‰ç¸ºåŠ±âˆªç¸ºå¶â‚¬ãƒ»è‰ï½¥è³ä¹âEç¸ºEªç¸ºE£ç¸ºæº˜ï½‰è±E½»è E¡è²æ³ŒãE(m_isDying)ç¹§å¸å¹•èŸ‹ä¹ï¼ ç¸ºE¾ç¸ºå¶â‚¬ãƒ»
void Boss::TakeDamage(int damage) {
    if (m_isDying || m_invincibleTimer > 0) return;

    // m_lives ç¸ºE®è¬E¥è™šè²‚å¸›ï½°ä»£ÎŸç¹§E¸ç¹ãEã‘ç¹§è²ç‚é«¯E¤ç¸ºåŠ±â‚¬ãƒ»ç¸ºE«ç¸ºEªç¸ºE£ç¸ºæ»“åEç¸ºE®ç¸ºE¿è›»E¤è³ãƒ»

    m_hp -= damage;
    if (m_hp <= 0) {
        m_hp = 0;
        m_lives--;
        
        // ãƒœã‚¹ã®åE½¢æ…‹ã‚’å€’ã—ãŸï¼ˆã‚ã‚‹ã„ã¯å®ŒåEã«å€’ã—ãŸï¼‰æ™‚ã«ã™ã¹ã¦ã®æ•µå¼¾ã‚’æ¶ˆã™
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

// è³æ‚ŸãEç¸ºE«è±¸åŸŸï½»ãƒ»EE¸ºå¸™ï½‹èœƒE¦é€EE
// è±E½»è E¡è²æ³ŒãEç¸ºæªï½µã‚E½ç¸ºE£ç¸ºæº·E¾å¾ŒâEèœ»E¼ç¸ºE°ç¹§å¾ŒÂ€âˆšã”ç¹ï½¼ç¹ï¿½ç¹§E¯ç¹ï½ªç¹§E¢ãƒ»ãƒ»esultSceneç¸ºE¸ç¸ºE®é˜ï½»é™¦é¯‰ï½¼å³¨E’ç¹åŒ»Îœç¹§E¬ç¹ï½¼ç¸ºåŠ±âˆªç¸ºå¶Â€ãƒ»
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

// è‰æ‚¶ãƒ»ç¹§Eªç¹æ‚¶ãšç¹§E§ç¹§E¯ç¹åŒ»â†’é©¥é˜ªâ†‘ç¸ºE£ç¸ºE¦ç¸ºãƒ»E‹è­ã‚…ãƒ»èœE½¦é€EEE¼äº¥E½è–™â—†ç¹§é›æEè³å£¹ãE¹å¶Î¦ç¹èŒ¨E¼ãƒ»
// ç¹åŠ±Îç¹§E¤ç¹ï½¤ç¹ï½¼ç¸ºE®è ‘ï½¾ãƒ»ç£¯Â€å£¼E¸E¸è ‘ï½¾ç¸²âˆ¬E¿ç¬¬ç£ç¸²âˆï½¿ãƒ»E®Eºè¬šÂ€ãƒ»å³¨â†’è –è–™â—E¸ºE£ç¸ºæº·E½E´èœ·åŒ»â†“ç¸²âˆ¬ãƒ»éœE½«ç¸ºE®TakeDamageç¹§è²ä»–ç¸ºE³èœE½ºç¸ºåŠ±âˆªç¸ºå¶Â€ãƒ»
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

// è¬ å†—åˆ¤èœE½¦é€EE
// ç¹æ‡Šã›ç¸ºE®é€•ï½»èœ’ä¸Šï½’è¬ å†—åˆ¤ç¸ºåŠ±âˆªç¸ºå¶Â€ã‚ˆï½­E»è E¡è²æ³ŒãEè³E­ç¸ºE¯ç¹âEãç¹âEãç¸ºE¨è½¤E¹è²ŠãEEE¸ºå¸™Â€âˆ¬æ­éš±æ§­ãƒ»ç¹ï½¡ç¹ãEãç¹ï½¼ç¹§E¸ç¹§å®šï½¡E¨é‰ï½ºç¸ºåŠ±âˆªç¸ºå¶Â€ãƒ»
void Boss::Draw() {
    if (!m_isActive) return;

    int s_bossGraphHandle = ResourceManager::GetInstance()->GetGraph("Resource/boss.png");

    if (s_bossGraphHandle != -1) {
        if (!m_isDying || (m_deathTimer / 5) % 2 == 0) {
            if (m_invincibleTimer > 0) {
                // ç„¡æ•µãƒãƒªã‚¢ã®æç”»
                SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100 + (m_invincibleTimer % 20) * 5);
                DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 110, GetColor(200, 50, 255), TRUE); // å¡—ã‚Šã¤ã¶ãE
                SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
                DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 110, GetColor(255, 150, 255), FALSE); // ç¸å–ã‚E
                DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 107, GetColor(255, 255, 255), FALSE); // å†EEã®ç¸å–ã‚E
                
                // ãƒœã‚¹æœ¬ä½“ãEé€é
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
