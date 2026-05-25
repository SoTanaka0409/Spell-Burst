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
<<<<<<< HEAD
=======
#include "Utility.h"
#include "GameScene.h"
#include "ExplosionParticle.h"
>>>>>>> main

Boss::Boss(float x, float y, int bossType)
    : Object2D(VGet(x, y, 0.0f))
    , mpCollider(nullptr)
{
    SetTag(Tag2D_Enemy);
<<<<<<< HEAD
    m_x = x;
    m_y = y;
    m_bossType = bossType;
    if (m_bossType == 1) {
        m_speed = 1.5f;
        m_hp = 60; // 東方風なのでHP多め
=======
    mvPosition.x = x;
    mvPosition.y = y;
    m_bossType = bossType;
    if (m_bossType == 1) {
        m_speed = 1.5f;
        m_hp = 60; // 譚ｱ譁ｹ鬚ｨ縺ｪ縺ｮ縺ｧHP螟壹ａ
>>>>>>> main
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

<<<<<<< HEAD
// ランダム移動�EターゲチE��座標を更新する処琁E
// 画面上部�E��Eレイヤーが攻撁E��めE��ぁE��E���E�からランダムに次の移動�Eを決めます、E
=======
<<<<<<< HEAD
// ランダム移動のターゲット座標を更新する処理
// 画面上部（プレイヤーが攻撃しやすい範囲）からランダムに次の移動先を決めます。
=======
// 繝ｩ繝ｳ繝€繝遘ｻ蜍輔・繧ｿ繝ｼ繧ｲ繝・ヨ蠎ｧ讓吶ｒ譖ｴ譁ｰ縺吶ｋ蜃ｦ逅・
// 逕ｻ髱｢荳企Κ・医・繝ｬ繧､繝､繝ｼ縺梧判謦・＠繧・☆縺・ｯ・峇・峨°繧峨Λ繝ｳ繝€繝縺ｫ谺｡縺ｮ遘ｻ蜍募・繧呈ｱｺ繧√∪縺吶€・
>>>>>>> main
>>>>>>> 240f2f277102418da5ddb286e12d12d717854dca
void Boss::SelectNewTarget() {
    // Top half boundary: X between 100 and 1180, Y between 80 and 260
    m_targetX = 100.0f + static_cast<float>(rand() % 1080);
    m_targetY = 80.0f + static_cast<float>(rand() % 180);
}

<<<<<<< HEAD
// ボスの毎フレームの更新処琁E
// 死亡演�E中なら上にフェードアウトし、生存中ならターゲチE��座標に向かって移動しながら弾幕を撁E��ます、E
=======
<<<<<<< HEAD
// ボスの毎フレームの更新処理
// 死亡演出中なら上にフェードアウトし、生存中ならターゲット座標に向かって移動しながら弾幕を撃ちます。
>>>>>>> 240f2f277102418da5ddb286e12d12d717854dca
void Boss::Update() {
    if (m_isDying) {
        m_deathTimer--;
        m_y -= 1.0f; // Move upwards while dying
        mvPosition = VGet(m_x, m_y, 0.0f);
=======
// 繝懊せ縺ｮ豈弱ヵ繝ｬ繝ｼ繝縺ｮ譖ｴ譁ｰ蜃ｦ逅・
// 豁ｻ莠｡貍泌・荳ｭ縺ｪ繧我ｸ翫↓繝輔ぉ繝ｼ繝峨い繧ｦ繝医＠縲∫函蟄倅ｸｭ縺ｪ繧峨ち繝ｼ繧ｲ繝・ヨ蠎ｧ讓吶↓蜷代°縺｣縺ｦ遘ｻ蜍輔＠縺ｪ縺後ｉ蠑ｾ蟷輔ｒ謦・■縺ｾ縺吶€・
void Boss::Update() {
    if (m_isDying) {
        m_deathTimer--;
        mvPosition.y -= 1.0f; // Move upwards while dying
        mvPosition = VGet(mvPosition.x, mvPosition.y, 0.0f);
>>>>>>> main
        if (m_deathTimer <= 0) {
            Kill();
        }
        return; // Skip normal behavior
    }

    if (m_invincibleTimer > 0) {
        m_invincibleTimer--;
    }

<<<<<<< HEAD
    // 最終�Eス�E�タイチE�E��Eみ、E秒！E00フレーム�E�おきに2秒間�E�E20フレーム�E�無敵になめE
=======
<<<<<<< HEAD
    // 最終ボス（タイプ3）のみ、5秒（300フレーム）おきに2秒間（120フレーム）無敵になる
=======
    // 譛€邨ゅ・繧ｹ・医ち繧､繝・・峨・縺ｿ縲・遘抵ｼ・00繝輔Ξ繝ｼ繝・峨♀縺阪↓2遘帝俣・・20繝輔Ξ繝ｼ繝・臥┌謨ｵ縺ｫ縺ｪ繧・
>>>>>>> main
>>>>>>> 240f2f277102418da5ddb286e12d12d717854dca
    if (m_bossType == 3) {
        m_invincibleCycleTimer++;
        if (m_invincibleCycleTimer >= 300) {
            m_invincibleTimer = 120; // 2 seconds invincibility
            m_invincibleCycleTimer = 0;
            
<<<<<<< HEAD
            // 無敵化と同時に取り巻きを召喁E
=======
<<<<<<< HEAD
            // 無敵化と同時に取り巻きを召喚
>>>>>>> 240f2f277102418da5ddb286e12d12d717854dca
            new Enemy(m_x - 60.0f, m_y + 60.0f, 1);
            new Enemy(m_x + 60.0f, m_y + 60.0f, 1);
=======
            // 辟｡謨ｵ蛹悶→蜷梧凾縺ｫ蜿悶ｊ蟾ｻ縺阪ｒ蜿ｬ蝟・
            new Enemy(mvPosition.x - 60.0f, mvPosition.y + 60.0f, 1);
            new Enemy(mvPosition.x + 60.0f, mvPosition.y + 60.0f, 1);
>>>>>>> main
        }
    } else {
        m_invincibleTimer = 0;
        m_invincibleCycleTimer = 0;
    }

    // Move towards current target
<<<<<<< HEAD
    float dx = m_targetX - m_x;
    float dy = m_targetY - m_y;
=======
    float dx = m_targetX - mvPosition.x;
    float dy = m_targetY - mvPosition.y;
>>>>>>> main
    float dist = std::sqrt(dx * dx + dy * dy);

    if (dist < 15.0f) {
        SelectNewTarget();
    } else {
<<<<<<< HEAD
        m_x += (dx / dist) * m_speed;
        m_y += (dy / dist) * m_speed;
    }

    mvPosition = VGet(m_x, m_y, 0.0f);
=======
        mvPosition.x += (dx / dist) * m_speed * Utility::TimeScale;
        mvPosition.y += (dy / dist) * m_speed * Utility::TimeScale;
    }

    mvPosition = VGet(mvPosition.x, mvPosition.y, 0.0f);
>>>>>>> main

    if (mpCollider) {
        mpCollider->mvPosition = mvPosition;
        mpCollider->mvPosition2 = mvPosition;
    }

<<<<<<< HEAD
    // 攻撁E��要E
=======
<<<<<<< HEAD
    // 攻撃感覚
=======
    // 謾ｻ謦・─隕・
>>>>>>> main
>>>>>>> 240f2f277102418da5ddb286e12d12d717854dca
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
<<<<<<< HEAD
        if (m_attackTimer >= 100) { // 発封E��隔を短く！E00 -> 40�E�弾幕化
=======
<<<<<<< HEAD
        if (m_attackTimer >= 100) { // 発射間隔を短く（100 -> 40）弾幕化
>>>>>>> 240f2f277102418da5ddb286e12d12d717854dca
            m_attackTimer = 0;
            if (m_patternIndex == 0) {
                ShootRadialBarrage();
            } else if (m_patternIndex == 1) {
                ShootFanBarrage();
            } else if (m_patternIndex == 2) {
                ShootTargetedBarrage();
            }
            m_patternIndex = (m_patternIndex + 1) % 3;
=======
        if (m_attackTimer >= 100) { // 逋ｺ蟆・俣髫斐ｒ遏ｭ縺擾ｼ・00 -> 40・牙ｼｾ蟷募喧
            m_attackTimer = 0;
            
            // ステージ3の場合は確率でスペルカード発動
            bool usedSpellCard = false;
            if (GameScene::s_currentStage == 3) {
                if ((rand() % 100) < 20) { // 20%の確率
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
>>>>>>> main
        }
    }
}

<<<<<<< HEAD
// 全方位弾幕を撁E��処琁E��スペルカード風�E�渦巻き弾幕！E
=======
<<<<<<< HEAD
// 全方位弾幕を撃つ処理（スペルカード風：渦巻き弾幕）
>>>>>>> 240f2f277102418da5ddb286e12d12d717854dca
void Boss::ShootRadialBarrage() {
    const float PI = 3.14159265f;
    const int bulletCount = 36; // 弾数を倍墁E
    static float spiralAngle = 0.0f;
<<<<<<< HEAD
    spiralAngle += 0.15f; // 発封E��とに角度をずらして渦巻きにする
=======
    spiralAngle += 0.15f; // 発射ごとに角度をずらして渦巻きにする
=======
// 蜈ｨ譁ｹ菴榊ｼｾ蟷輔ｒ謦・▽蜃ｦ逅・ｼ医せ繝壹Ν繧ｫ繝ｼ繝蛾｢ｨ・壽ｸｦ蟾ｻ縺榊ｼｾ蟷包ｼ・
void Boss::ShootRadialBarrage() {
    const float PI = 3.14159265f;
    const int bulletCount = 36; // 蠑ｾ謨ｰ繧貞€榊｢・
    static float spiralAngle = 0.0f;
    spiralAngle += 0.15f; // 逋ｺ蟆・＃縺ｨ縺ｫ隗貞ｺｦ繧偵★繧峨＠縺ｦ貂ｦ蟾ｻ縺阪↓縺吶ｋ
>>>>>>> main
>>>>>>> 240f2f277102418da5ddb286e12d12d717854dca

    bool reflect = (m_lives == 2);
    for (int i = 0; i < bulletCount; i++) {
        float angle = spiralAngle + (i * 2.0f * PI) / bulletCount;
        float dx = std::cos(angle);
        float dy = std::sin(angle);
<<<<<<< HEAD
        new EnemyBullet(m_x, m_y, dx, dy, 2.5f, reflect); // 弾速を落として避けやすく
    }
}

<<<<<<< HEAD
// 扁E��弾幕を撁E��処琁E��スペルカード風�E�多層交差弾幕！E
=======
// 扇状弾幕を撃つ処理（スペルカード風：多層交差弾幕）
=======
        new EnemyBullet(mvPosition.x, mvPosition.y, dx, dy, 2.5f, reflect); // 蠑ｾ騾溘ｒ關ｽ縺ｨ縺励※驕ｿ縺代ｄ縺吶￥
    }
}

// 謇・憾蠑ｾ蟷輔ｒ謦・▽蜃ｦ逅・ｼ医せ繝壹Ν繧ｫ繝ｼ繝蛾｢ｨ・壼､壼ｱ､莠､蟾ｮ蠑ｾ蟷包ｼ・
>>>>>>> main
>>>>>>> 240f2f277102418da5ddb286e12d12d717854dca
void Boss::ShootFanBarrage() {
    const float PI = 3.14159265f;
    const int bulletCount = 15;
    bool reflect = (m_lives == 2);
<<<<<<< HEAD
    // 真下を中忁E��庁E��E��に撁E��
=======
<<<<<<< HEAD
    // 真下を中心に広範囲に撃つ
>>>>>>> 240f2f277102418da5ddb286e12d12d717854dca
    float baseAngle = PI / 2.0f;
    
    // 2層の速度が違ぁE��幕を同時に撁E��
    for (int layer = 0; layer < 4; layer++) {
<<<<<<< HEAD
        float speed = 2.0f + layer * 1.5f; // 遁E��弾と速い弾
=======
        float speed = 2.0f + layer * 1.5f; // 遅い弾と速い弾
=======
    // 逵滉ｸ九ｒ荳ｭ蠢・↓蠎・ｯ・峇縺ｫ謦・▽
    float baseAngle = PI / 2.0f;
    
    // 2螻､縺ｮ騾溷ｺｦ縺碁＆縺・ｼｾ蟷輔ｒ蜷梧凾縺ｫ謦・▽
    for (int layer = 0; layer < 4; layer++) {
        float speed = 2.0f + layer * 1.5f; // 驕・＞蠑ｾ縺ｨ騾溘＞蠑ｾ
>>>>>>> main
>>>>>>> 240f2f277102418da5ddb286e12d12d717854dca
        for (int i = -bulletCount/2; i <= bulletCount/2; i++) {
            float angle = baseAngle + (i * 8.0f * PI / 180.0f);
            float dx = std::cos(angle);
            float dy = std::sin(angle);
<<<<<<< HEAD
            new EnemyBullet(m_x, m_y, dx, dy, speed, reflect);
=======
            new EnemyBullet(mvPosition.x, mvPosition.y, dx, dy, speed, reflect);
>>>>>>> main
        }
    }
}

<<<<<<< HEAD
// 自機狙ぁE��幕を撁E��処琁E
// プレイヤーの現在位置を計算し、そこに向かって3WAYの弾を発封E��ます、E
=======
<<<<<<< HEAD
// 自機狙い弾幕を撃つ処理
// プレイヤーの現在位置を計算し、そこに向かって3WAYの弾を発射します。
>>>>>>> 240f2f277102418da5ddb286e12d12d717854dca
void Boss::ShootTargetedBarrage() {
    const float PI = 3.14159265f;
    Player* player = dynamic_cast<Player*>(Master::sceneManager->GetCurrentScene()->GetObjectManager()->GetObject2DByTag(Tag2D_Player));
    float targetX = m_x;
    float targetY = m_y + 200.0f; // Default targeted direction (downwards)
=======
// 閾ｪ讖溽漁縺・ｼｾ蟷輔ｒ謦・▽蜃ｦ逅・
// 繝励Ξ繧､繝､繝ｼ縺ｮ迴ｾ蝨ｨ菴咲ｽｮ繧定ｨ育ｮ励＠縲√◎縺薙↓蜷代°縺｣縺ｦ3WAY縺ｮ蠑ｾ繧堤匱蟆・＠縺ｾ縺吶€・
void Boss::ShootTargetedBarrage() {
    const float PI = 3.14159265f;
    Player* player = dynamic_cast<Player*>(Master::sceneManager->GetCurrentScene()->GetObjectManager()->GetObject2DByTag(Tag2D_Player));
    float targetX = mvPosition.x;
    float targetY = mvPosition.y + 200.0f; // Default targeted direction (downwards)
>>>>>>> main

    if (player != nullptr) {
        targetX = player->GetX();
        targetY = player->GetY();
    }

<<<<<<< HEAD
    float dx = targetX - m_x;
    float dy = targetY - m_y;
=======
    float dx = targetX - mvPosition.x;
    float dy = targetY - mvPosition.y;
>>>>>>> main
    float dist = std::sqrt(dx * dx + dy * dy);
    
    if (dist > 0.0f) {
        dx /= dist;
        dy /= dist;
    } else {
        dx = 0.0f;
        dy = 1.0f;
    }

    float baseAngle = std::atan2(dy, dx);

<<<<<<< HEAD
    // 寁E��5WAY自機狙ぁE
=======
<<<<<<< HEAD
    // 密な5WAY自機狙い
>>>>>>> 240f2f277102418da5ddb286e12d12d717854dca
    for (int i = -2; i <= 2; i++) {
        float angle = baseAngle + (i * 5.0f * PI / 180.0f);
        new EnemyBullet(m_x, m_y, std::cos(angle), std::sin(angle), 3.5f);
    }
    // 少し遁E��庁E��の3WAYも重ねめE
    for (int i = -1; i <= 1; i++) {
        float angle = baseAngle + (i * 12.0f * PI / 180.0f);
        new EnemyBullet(m_x, m_y, std::cos(angle), std::sin(angle), 2.5f);
=======
    // 蟇・↑5WAY閾ｪ讖溽漁縺・
    for (int i = -2; i <= 2; i++) {
        float angle = baseAngle + (i * 5.0f * PI / 180.0f);
        new EnemyBullet(mvPosition.x, mvPosition.y, std::cos(angle), std::sin(angle), 3.5f);
    }
    // 蟆代＠驕・＞蠎・ａ縺ｮ3WAY繧る㍾縺ｭ繧・
    for (int i = -1; i <= 1; i++) {
        float angle = baseAngle + (i * 12.0f * PI / 180.0f);
        new EnemyBullet(mvPosition.x, mvPosition.y, std::cos(angle), std::sin(angle), 2.5f);
>>>>>>> main
    }
}

void Boss::ShootSimpleBarrage() {
    const float PI = 3.14159265f;
    
<<<<<<< HEAD
    // ランダムな基準角から、四方�E��E方位）に5発の弾を発封E��めE
    // 60フレーム�E�E秒間�E��Eそ�Eまま直進し、その征E20フレーム�E�E秒間�E��Eレイヤーを追尾する
=======
<<<<<<< HEAD
    // ランダムな基準角から、四方（全方位）に5発の弾を発射する
    // 60フレーム（1秒間）はそのまま直進し、その後120フレーム（2秒間）プレイヤーを追尾する
=======
    // 繝ｩ繝ｳ繝€繝縺ｪ蝓ｺ貅冶ｧ偵°繧峨€∝屁譁ｹ・亥・譁ｹ菴搾ｼ峨↓5逋ｺ縺ｮ蠑ｾ繧堤匱蟆・☆繧・
    // 60繝輔Ξ繝ｼ繝・・遘帝俣・峨・縺昴・縺ｾ縺ｾ逶ｴ騾ｲ縺励€√◎縺ｮ蠕・20繝輔Ξ繝ｼ繝・・遘帝俣・峨・繝ｬ繧､繝､繝ｼ繧定ｿｽ蟆ｾ縺吶ｋ
>>>>>>> main
>>>>>>> 240f2f277102418da5ddb286e12d12d717854dca
    float baseAngle = static_cast<float>(rand() % 360) * PI / 180.0f;
    for (int i = 0; i < 5; i++) {
        float angle = baseAngle + (i * 360.0f / 5.0f * PI / 180.0f);
        float bx = std::cos(angle);
        float by = std::sin(angle);
        // speed: 3.5f, canReflect: false, stun: false, homingFrames: 120, homingDelayFrames: 60
<<<<<<< HEAD
        new EnemyBullet(m_x, m_y, bx, by, 3.5f, false, false, 120, 60);
=======
        new EnemyBullet(mvPosition.x, mvPosition.y, bx, by, 3.5f, false, false, 120, 60);
>>>>>>> main
    }
}

void Boss::ShootBouncingBarrage() {
    const float PI = 3.14159265f;
    for (int i = 0; i < 6; i++) {
        float angle = (i * 2.0f * PI) / 6.0f;
        float dx = std::cos(angle);
        float dy = std::sin(angle);
        // pass canReflect = true
<<<<<<< HEAD
        new EnemyBullet(m_x, m_y, dx, dy, 4.5f, true);
    }
}

// ダメージを受ける処琁E
// プレイヤーの攻撁E��当たった際に呼ばれ、HPを減らします、E以下になったら死亡演�E(m_isDying)を開始します、E
void Boss::TakeDamage(int damage) {
    if (m_isDying || m_invincibleTimer > 0) return;

<<<<<<< HEAD
    // m_lives の手動減少ロジチE��を削除し、Eになった時のみ判宁E
=======
    // m_lives の手動減少ロジックを削除し、0になった時のみ判定
=======
        new EnemyBullet(mvPosition.x, mvPosition.y, dx, dy, 4.5f, true);
    }
}

void Boss::ShootSpellCardBarrage() {
    const float PI = 3.14159265f;
    // 巨大な弾を円形に大量に放ち、さらにそれが反射する（スペルカード級の難易度）
    for (int i = 0; i < 24; i++) {
        float angle = (i * 2.0f * PI) / 24.0f;
        float dx = std::cos(angle);
        float dy = std::sin(angle);
        new EnemyBullet(mvPosition.x, mvPosition.y, dx, dy, 2.0f, true); // 反射する遅い弾
    }
    // 時間差で速い弾を放つ
    for (int i = 0; i < 12; i++) {
        float angle = (i * 2.0f * PI) / 12.0f + 0.5f;
        float dx = std::cos(angle);
        float dy = std::sin(angle);
        new EnemyBullet(mvPosition.x, mvPosition.y, dx, dy, 5.0f, false);
    }
}

// 繝€繝｡繝ｼ繧ｸ繧貞女縺代ｋ蜃ｦ逅・
// 繝励Ξ繧､繝､繝ｼ縺ｮ謾ｻ謦・→蠖薙◆縺｣縺滄圀縺ｫ蜻ｼ縺ｰ繧後€？P繧呈ｸ帙ｉ縺励∪縺吶€・莉･荳九↓縺ｪ縺｣縺溘ｉ豁ｻ莠｡貍泌・(m_isDying)繧帝幕蟋九＠縺ｾ縺吶€・
void Boss::TakeDamage(int damage) {
    if (m_isDying || m_invincibleTimer > 0) return;

    // m_lives 縺ｮ謇句虚貂帛ｰ代Ο繧ｸ繝・け繧貞炎髯､縺励€・縺ｫ縺ｪ縺｣縺滓凾縺ｮ縺ｿ蛻､螳・
>>>>>>> main
>>>>>>> 240f2f277102418da5ddb286e12d12d717854dca

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
<<<<<<< HEAD
=======

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
>>>>>>> main
        }
    }
}

<<<<<<< HEAD
// 完�Eに消滁E��せる処琁E
// 死亡演�Eが終わった後に呼ばれ、ゲームクリア�E�EesultSceneへの移行）をトリガーします、E
=======
<<<<<<< HEAD
// 完全に消滅させる処理
// 死亡演出が終わった後に呼ばれ、ゲームクリア（ResultSceneへの移行）をトリガーします。
=======
// 螳悟・縺ｫ豸域ｻ・＆縺帙ｋ蜃ｦ逅・
// 豁ｻ莠｡貍泌・縺檎ｵゅｏ縺｣縺溷ｾ後↓蜻ｼ縺ｰ繧後√ご繝ｼ繝�繧ｯ繝ｪ繧｢・・esultScene縺ｸ縺ｮ遘ｻ陦鯉ｼ峨ｒ繝医Μ繧ｬ繝ｼ縺励∪縺吶・
>>>>>>> main
>>>>>>> 240f2f277102418da5ddb286e12d12d717854dca
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

<<<<<<< HEAD
// 他�Eオブジェクトと重なってぁE��時�E処琁E��当たり判定イベント！E
// プレイヤーの弾�E�通常弾、近接、忁E��技�E�と当たった場合に、�E身のTakeDamageを呼び出します、E
=======
<<<<<<< HEAD
// 他のオブジェクトと重なっている時の処理（当たり判定イベント）
// プレイヤーの弾（通常弾、近接、必殺技）と当たった場合に、自身のTakeDamageを呼び出します。
=======
// 莉悶・繧ｪ繝悶ず繧ｧ繧ｯ繝医→驥阪↑縺｣縺ｦ縺・ｋ譎ゅ・蜃ｦ逅・ｼ亥ｽ薙◆繧雁愛螳壹う繝吶Φ繝茨ｼ・
// 繝励Ξ繧､繝､繝ｼ縺ｮ蠑ｾ・磯壼ｸｸ蠑ｾ縲∬ｿ第磁縲∝ｿ・ｮｺ謚・峨→蠖薙◆縺｣縺溷�ｴ蜷医↓縲∬・霄ｫ縺ｮTakeDamage繧貞他縺ｳ蜃ｺ縺励∪縺吶・
>>>>>>> main
>>>>>>> 240f2f277102418da5ddb286e12d12d717854dca
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

<<<<<<< HEAD
// 描画処琁E
// ボスの画像を描画します。死亡演�E中はチカチカと点滁E��せ、英語�EメチE��ージを表示します、E
=======
<<<<<<< HEAD
// 描画処理
// ボスの画像を描画します。死亡演出中はチカチカと点滅させ、英語のメッセージを表示します。
=======
// 謠冗判蜃ｦ逅・
// 繝懊せ縺ｮ逕ｻ蜒上ｒ謠冗判縺励∪縺吶よｭｻ莠｡貍泌・荳ｭ縺ｯ繝√き繝√き縺ｨ轤ｹ貊・＆縺帙∬恭隱槭・繝｡繝・そ繝ｼ繧ｸ繧定｡ｨ遉ｺ縺励∪縺吶・
>>>>>>> main
>>>>>>> 240f2f277102418da5ddb286e12d12d717854dca
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
