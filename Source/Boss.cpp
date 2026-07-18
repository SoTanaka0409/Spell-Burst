#include "Boss.h"
#include "ObjectManager.h"
#include "CapsuleCollider.h"
#include "Bullet.h"
#include "MeleeAttack.h"
#include "SpecialBullet.h"
#include "Player.h"
#include "EnemyBullet.h"
#include "Math.h"
#include "BulletManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Master.h"
#include "ResultScene.h"
#include "GameScene.h"
#include "Enemy.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include <cmath>
#include <cstdlib>
#include "ResourceManager.h"
#include "Utility.h"
#include "BulletFactory.h"
#include "EffectManager.h"
#include "GameScene.h"
#include "ExplosionParticle.h"
#include "PlayerHomingBullet.h"
#include "SoundManager.h"
#include "BossStateAttack.h"
#include "Barrier.h"


Boss::Boss(float x, float y, int boss_type_)
    : Character(Vector2(x, y), 150, 2.5f)
{
    SetTag(kTag2dEnemy);
    this->boss_type_ = boss_type_;

    if (boss_type_ == 1)
    {
        speed_ = 1.5f;
        max_hp_ = 60;
    }
    else if (boss_type_ == 2)
    {
        speed_ = 2.0f;
        max_hp_ = 80;
    }
    else
    {
        speed_ = 2.5f;
        max_hp_ = 150;
    }

    if (GameScene::current_stage_ == 2)
    {
        max_hp_ = static_cast<int>(max_hp_ * 1.3f);
    }
    else if (GameScene::current_stage_ == 3)
    {
        max_hp_ = static_cast<int>(max_hp_ * 1.5f);
    }

    hp_ = max_hp_;
    attack_timer_ = 0;
    pattern_index_ = 0;
    is_dying_ = false;

    if (boss_type_ == 3)
    {
        lives_ = 3;
    }
    else
    {
        lives_ = 1;
    }
    invincible_timer_ = 0;
    invincible_cycle_timer_ = 0;
    death_timer_ = 0;

    if (collider_) delete collider_;
    collider_ = new CapsuleCollider(this, position_, position_, 80.0f);
    SelectNewTarget();

    if (boss_type_ == 2)
    {
        auto bar = ObjectManager::Instantiate<Barrier>(position_.x, position_.y, 100.0f, Object2D::kTag2dBarrierEnemy);
        if (auto locked = bar.lock())
        {
            locked->SetDeployInterval(360.0f);
            locked->SetActiveDuration(60.0f);
        }
        barrier_ = bar;
    }

    if (this->boss_type_ == 1)
    {
        state_ = std::make_unique<BossStateSimple>();
    }
    else if (this->boss_type_ == 2)
    {
        state_ = std::make_unique<BossStateBouncing>();
    }
    else
    {
        state_ = std::make_unique<BossStateFinal>();
    }
}

Boss::~Boss()
{
}

void Boss::SelectNewTarget()
{
    target_x_ = 100.0f + static_cast<float>(rand() % 1080);
    target_y_ = 80.0f + static_cast<float>(rand() % 180);
}

void Boss::Update()
{
    Character::Update();

    if (stun_timer_ > 0) return;

    if (invincible_timer_ > 0)
    {
        invincible_timer_--;
    }

    if (is_dying_)
    {
        UpdateDeath();
        return;
    }

    Vector2 target(target_x_, target_y_);
    float dist = position_.DistanceTo(target);
    if (dist < 15.0f)
    {
        SelectNewTarget();
    }
    else
    {
        position_ += (target - position_).Normalized() * (speed_ * Utility::time_scale_);
    }

    if (boss_type_ != 1)
    {
        if (auto bar = barrier_.lock())
        {
            bar->SetPosition(position_);
        }
    }

    if (state_)
    {
        state_->Update(this);
    }
}

void Boss::ShootRadialBarrage()
{
    const float PI = 3.14159265f;
    const int bulletCount = 36;
    static float spiralAngle = 0.0f;
    spiralAngle += 0.15f;

    bool reflect = (lives_ == 2);
    BulletFactory::SpawnCircleBullets(position_, spiralAngle, bulletCount, 2.5f, reflect);
}

void Boss::ShootFanBarrage()
{
    const float PI = 3.14159265f;
    const int bulletCount = 15;
    bool reflect = (lives_ == 2);
    float baseAngle = PI / 2.0f;
    for (int layer = 0; layer < 4; layer++)
    {
        float speed_ = 2.0f + layer * 1.5f;
        BulletFactory::SpawnNWayBullets(position_, baseAngle, bulletCount % 2 == 0 ? bulletCount + 1 : bulletCount, (bulletCount - 1) * 8.0f * DX_PI_F / 180.0f, speed_, reflect);
    }
}

void Boss::ShootTargetedBarrage()
{
    const float PI = 3.14159265f;
    Player* player = dynamic_cast<Player*>(Master::sceneManager->GetCurrentScene()->GetObjectManager()->GetObject2DByTag(kTag2dPlayer).get());
    Vector2 targetPos(position_.x, position_.y + 200.0f);
    if (player != nullptr)
    {
        targetPos = Vector2(player->GetX(), player->GetY());
    }
    Vector2 dir = (targetPos - position_).Normalized();
    if (dir.MagnitudeSq() == 0.0f) dir = Vector2(0.0f, 1.0f);
    float baseAngle = Vector2(1, 0).AngleTo(dir);
    BulletFactory::SpawnNWayBullets(position_, baseAngle, 5, 20.0f * DX_PI_F / 180.0f, 3.5f);
    BulletFactory::SpawnNWayBullets(position_, baseAngle, 3, 24.0f * DX_PI_F / 180.0f, 2.5f);
}

void Boss::ShootSimpleBarrage()
{
    const float PI = 3.14159265f;
    float baseAngle = static_cast<float>(rand() % 360) * PI / 180.0f;
    BulletFactory::SpawnCircleBullets(position_, baseAngle, 5, 3.5f, false, false, 120, 60);
}

void Boss::ShootBouncingBarrage()
{
    const float PI = 3.14159265f;
    BulletFactory::SpawnCircleBullets(position_, 0.0f, 6, 4.5f, true);
}

void Boss::ShootSpellCardBarrage()
{
    const float PI = 3.14159265f;
    BulletFactory::SpawnCircleBullets(position_, 0.0f, 24, 2.0f, true);
    BulletFactory::SpawnCircleBullets(position_, 0.5f, 12, 5.0f, false);
}

void Boss::TakeDamage(int damage)
{
    if (is_dying_ || invincible_timer_ > 0) return;

    hp_ = std::clamp(hp_ - damage, 0, max_hp_);

    GameScene* scene = dynamic_cast<GameScene*>(Master::sceneManager->GetCurrentScene());
    if (scene != nullptr)
    {
        // scene->AddHitStop(3);
        // scene->AddScreenShake(5, 4.0f);
        // scene->AddDamageFlash(8, GetColor(255, 255, 200));
    }

    if (hp_ <= 0)
    {
        OnDeath();
    }
}

void Boss::OnDeath()
{
    lives_--;
    auto bullets = Master::sceneManager->GetCurrentScene()->GetObjectManager()->GetObject2DListByTag(kTag2dEnemyBullet);
    for (auto& b : bullets)
    {
        b->SetDeleteFlag(true);
    }

    if (lives_ > 0)
    {
        hp_ = max_hp_;
        invincible_timer_ = 180;
    }
    else
    {
        is_dying_ = true;
        SoundManager::GetInstance()->PlaySE("Resource/SE/se_destroy_glass01.mp3");
        death_timer_ = 180;

        if (collider_)
        {
            collider_->SetDeleteFlag(true);
        }

        Scene* current_scene_ = Master::sceneManager->GetCurrentScene();
        if (current_scene_)
        {
            auto bList = current_scene_->GetObjectManager()->GetObject2DListByTag(kTag2dEnemyBullet);
            for (auto& b : bList)
            {
                b->SetDeleteFlag(true);
            }

            Player* p = dynamic_cast<Player*>(current_scene_->GetObjectManager()->GetObject2DByTag(kTag2dPlayer).get());
            if (p) p->Heal(3);
        }
        collider_ = nullptr;

        GameScene* gs = dynamic_cast<GameScene*>(Master::sceneManager->GetCurrentScene());
        if (gs != nullptr)
        {
            gs->AddScreenShake(180, 20.0f);
            gs->AddHitStop(30);
        }

        for (int i = 0; i < 40; i++)
        {
            float angle = static_cast<float>(rand() % 360) * 3.14159f / 180.0f;
            float speed_ = 3.0f + static_cast<float>(rand() % 50) / 10.0f;
            int life = 60 + (rand() % 60);
        }
    }
}

void Boss::UpdateDeath()
{
    death_timer_--;
    position_.y -= 1.0f;
    if (death_timer_ <= 0)
    {
        Kill();
    }
}

void Boss::Kill()
{
    Character::Kill();

    if (auto bar = barrier_.lock())
    {
        bar->SetDeleteFlag(true);
    }

    if (boss_type_ == 3)
    {
        ResultScene::kIsVictory = true;
        GameScene::is_time_attack_active_ = false;
        Master::sceneManager->SetNextScene(SceneManager::kSceneResult);
    }
}

void Boss::OnTrigger(Collider* collider, Collider* check)
{
    if (is_dying_) return;
}

void Boss::DrawInvincibility()
{
    if (invincible_timer_ > 0)
    {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100 + (invincible_timer_ % 20) * 5);
        DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 110, GetColor(200, 50, 255), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
        DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 110, GetColor(255, 150, 255), FALSE);
        DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 107, GetColor(255, 255, 255), FALSE);
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128 + (invincible_timer_ % 20) * 5);
    }
}

void Boss::DrawHealthBar()
{
}

void Boss::Draw()
{
    if (!is_active_) return;

    int bossGraphHandle = ResourceManager::GetInstance()->GetGraph("Resource/boss.png");

    if (bossGraphHandle != -1)
    {
        if (!is_dying_ || (death_timer_ / 5) % 2 == 0)
        {
            DrawInvincibility();

            DrawExtendGraph(
                static_cast<int>(position_.x - 80.0f),
                static_cast<int>(position_.y - 80.0f),
                static_cast<int>(position_.x + 80.0f),
                static_cast<int>(position_.y + 80.0f),
                bossGraphHandle,
                TRUE
            );

            if (invincible_timer_ > 0)
            {
                SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
            }
        }
    }
    else
    {
        if (!is_dying_ || (death_timer_ / 5) % 2 == 0)
        {
            unsigned int color_ = GetColor(255, 0, 0);
            if (invincible_timer_ > 0 && (invincible_timer_ / 5) % 2 == 0)
            {
                color_ = GetColor(255, 255, 0);
            }
            DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 80, color_, TRUE);
        }
    }

    if (is_dying_)
    {
        DrawString(static_cast<int>(position_.x) - 150, static_cast<int>(position_.y) + 90, "I will be waiting for you in the next stage...!", GetColor(255, 100, 100));
    }
}
