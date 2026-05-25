#include "SoundManager.h"
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
#include "ResourceManager.h"

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
        m_hp = 60; // HP 螟壹a
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

// 繝繝ｳ繝繝遘ｻ蜍輔、繧ｿ繝ｼ繧ｲ繝、YO蠎ｧ讓吶r譖ｴ譁ｰ縺吶k蜃ｦ逅・
// 逕髱「荳?・MEDICINE・?繧、繝、繝ｼ縺梧文謦・＠繧・☆縺・ｯ・峇・
void Boss::SelectNewTarget() {
    // Top half boundary: X between 100 and 1180, Y between 80 and 260
    m_targetX = 100.0f + static_cast<float>(rand() % 1080);
    m_targetY = 80.0f + static_cast<float>(rand() % 180);
}

// If you're a weak person, you're bound to see a story.
// 豁莠。 
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

    // 譛邨yu・繧ｽ・治繧、繝・・?・?ｿ縲・性ｼ・00繝輔Ξ繝ｼ繝
    if (m_bossType == 3) {
        m_invincibleCycleTimer++;
        if (m_invincibleCycleTimer >= 300) {
            m_invincibleTimer = 120; // 2 seconds invincibility
            m_invincibleCycleTimer = 0;
            
            // 辟。
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

    // Satisfaction・─Meteor・
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
        if (m_attackTimer >= 100) { // 00 -> 40 Recruitment
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

// The story of a ghost 
void Boss::ShootRadialBarrage() {
    const float PI = 3.14159265f;
    const int bulletCount = 36; // Sakaki "・
    static float spiralAngle = 0.0f;
    spiralAngle += 0.15f; // 逋ｺ蟆・＃縺ｨ縺ｫ隗正ｦ繧detective★繧?＠縺ｦ貂ｦ蟾ｯ縺山↓縺吶k

    bool reflect = (m_lives == 2);
    for (int i = 0; i < bulletCount; i++) {
        float angle = spiralAngle + (i * 2.0f * PI) / bulletCount;
        float dx = std::cos(angle);
        float dy = std::sin(angle);
        new EnemyBullet(m_x, m_y, dx, dy, 2.5f, reflect); // 蠑?騾溘r關ｽ縺ｨ縺?※驕ｿ縺代d縺吶￥
    }
}

// 謇・?蠑ｾ蟷輔r謦・▽?者・ｼ?繝壹Ν繧ｫ繝ｼ繝繝子``ｨ・壼、?IA、莠、蟾蠑?蟷?・
void Boss::ShootFanBarrage() {
    const float PI = 3.14159265f;
    const int bulletCount = 15;
    bool reflect = (m_lives == 2);
    // 逵滉9荳ｭ萢・↓蠎・ｯ・峇?ｫ覦・▽
    float baseAngle = PI / 2.0f;
    
    // 2 Go & String 2
    for (int layer = 0; layer < 4; layer++) {
        float speed = 2.0f + layer * 1.5f; // Arrogance＞蠑辺縺騾溘＞蠑Se
        for (int i = -bulletCount/2; i <= bulletCount/2; i++) {
            float angle = baseAngle + (i * 8.0f * PI / 180.0f);
            float dx = std::cos(angle);
            float dy = std::sin(angle);
            new EnemyBullet(m_x, m_y, dx, dy, speed, reflect);
        }
    }
}

// Threshold fishing line・Shisemansuker・▽Encounter・
// Encouragement, encouragement
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

    // Toad・↑5WAY threshold fishing line・
    for (int i = -2; i <= 2; i++) {
        float angle = baseAngle + (i * 5.0f * PI / 180.0f);
        new EnemyBullet(m_x, m_y, std::cos(angle), std::sin(angle), 3.5f);
    }
    // 蟆代＠驕・＞蠎・a?ｮ3WAY ??ｭ繧・
    for (int i = -1; i <= 1; i++) {
        float angle = baseAngle + (i * 12.0f * PI / 180.0f);
        new EnemyBullet(m_x, m_y, std::cos(angle), std::sin(angle), 2.5f);
    }
}

void Boss::ShootSimpleBarrage() {
    const float PI = 3.14159265f;
    
    // Confession
    // 60 繝輔Ξ繝ｼ繝・・遘Teimata・?・縺sub・縺縺子ｾ逶鴨?縺?√◎縺
    float baseAngle = static_cast<float>(rand() % 360) * PI / 180.0f;
    for (int i = 0; i < 5; i++) {
        float angle = baseAngle + (i * 360.0f / 5.0f * PI / 180.0f);
        float bx = std::cos(angle);
        float by = std::sin(angle);
        // speed: 3.5f, canReflect: false, stun: false, homingFrames: 120, homingDelayFrames: 60
        new EnemyBullet(m_x, m_y, bx, by, 3.5f, false, false, 120, 60);
    }
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

// 繝繝。
// EncouragementΞ繧、繝、繝ｼ縺ｮ?謦・→薙◆縺"縺滄圀縺ｫ蜻ｼ縺ｰ繧after?
void Boss::TakeDamage(int damage) {
    if (m_isDying || m_invincibleTimer > 0) return;

    // m_lives ?ｮｮ ?文 vain ? 縛ｰ代Ο繧ｹ繝・KE繧悧??、??・?ｫ縺ｪ縺”??凾縺ｮ縺ｿ蛻、螳・

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
            SoundManager::GetInstance()->PlaySE("Resource/se_boss_death.wav");
            m_deathTimer = 180; // 3 seconds flash and fly up
            if (mpCollider) {
                mpCollider->SetDeleteFlag(true); // Disable collision
                mpCollider = nullptr;
            }
        }
    }
}

// 螳?・?ｫ豸?・＆?帙k蜃ｦ逅・
// 豁芽莠｡貍secretion、?檎?縺』After the thread ↓ After the spider thread √ Go into the thread 
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

// 繧ｧ繧繧繹Physician→Musaka↑縺”縺ｦ縺・k 
// EncouragementΞ繧、繝、繝ｼ縺ｮ蠑?、磯壼く蠑ｾ縲∬ｿ st porcelain 縲∝ｿｿｯｚｚ・?→蠖?◆
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

// Encounter with a friend
// If you want to keep your clothes closed, I encourage you to write your own sentences.
void Boss::Draw() {
    if (!m_isActive) return;

    int s_bossGraphHandle = ResourceManager::GetInstance()->GetGraph("Resource/boss.png");

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
