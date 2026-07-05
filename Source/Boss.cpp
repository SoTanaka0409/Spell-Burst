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
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include <cmath>
#include <cstdlib>
#include "ResourceManager.h"
#include "Utility.h"
#include "GameScene.h"
#include "ExplosionParticle.h"
#include "PlayerHomingBullet.h"
#include "SoundManager.h"

Boss::Boss(float x, float y, int bossType)
    : Character(Vector2(x, y), 150, 2.5f)
{
    SetTag(kTag2dEnemy);
    bossType = bossType;
    if (bossType == 1) {
        speed_ = 1.5f;
        max_hp_ = 60;
    } else if (bossType == 2) {
        speed_ = 2.0f;
        max_hp_ = 80;
    } else {
        speed_ = 2.5f;
        max_hp_ = 150;
    }

    if (GameScene::currentStage == 2) {
        max_hp_ = static_cast<int>(max_hp_ * 1.3f);
    } else if (GameScene::currentStage == 3) {
        max_hp_ = static_cast<int>(max_hp_ * 1.5f);
    }

    hp_ = max_hp_;
    attack_timer_ = 0;
    patternIndex = 0;
    isDying = false;
    if (bossType == 3) {
        lives = 3;
    } else {
        lives = 1;
    }
    invincibleTimer = 0;
    invincibleCycleTimer = 0;
    deathTimer = 0;

    if (collider_) delete collider_;
    collider_ = new CapsuleCollider(this, position_, position_, 80.0f);
    SelectNewTarget();
}

Boss::~Boss() {
}

void Boss::SelectNewTarget() {
    targetX = 100.0f + static_cast<float>(rand() % 1080);
    targetY = 80.0f + static_cast<float>(rand() % 180);
}

void Boss::Update() {
    Character::Update(); // スタン処理など

    if (stun_timer_ > 0) return;

    if (isDying) {
        deathTimer--;
        position_.y -= 1.0f;
        if (deathTimer <= 0) {
            Kill();
        }
        return;
    }

    if (invincibleTimer > 0) {
        invincibleTimer--;
    }
    if (bossType == 3) {
        invincibleCycleTimer++;
        if (invincibleCycleTimer >= 300) {
            invincibleTimer = 120;
            invincibleCycleTimer = 0;
            new Enemy(position_.x - 60.0f, position_.y + 60.0f, 1);
            new Enemy(position_.x + 60.0f, position_.y + 60.0f, 1);
        }
    } else {
        invincibleTimer = 0;
        invincibleCycleTimer = 0;
    }

    Vector2 target(targetX, targetY);
    float dist = position_.DistanceTo(target);

    if (dist < 15.0f) {
        SelectNewTarget();
    } else {
        position_ += (target - position_).Normalized() * (speed_ * Utility::TimeScale);
    }

    attack_timer_++;
    if (bossType == 1) {
        if (attack_timer_ >= 60) {
            attack_timer_ = 0;
            ShootSimpleBarrage();
        }
    } else if (bossType == 2) {
        if (attack_timer_ >= 120) {
            attack_timer_ = 0;
            ShootBouncingBarrage();
        }
    } else {
        if (attack_timer_ >= 100) {
            attack_timer_ = 0;
            bool usedSpellCard = false;
            if (GameScene::currentStage == 3) {
                if ((rand() % 100) < 20) {
                    ShootSpellCardBarrage();
                    usedSpellCard = true;
                }
            }
            
            if (!usedSpellCard) {
                if (patternIndex == 0) {
                    ShootRadialBarrage();
                } else if (patternIndex == 1) {
                    ShootFanBarrage();
                } else if (patternIndex == 2) {
                    ShootTargetedBarrage();
                }
                patternIndex = (patternIndex + 1) % 3;
            }
        }
    }
}

void Boss::ShootRadialBarrage() {
    const float PI = 3.14159265f;
    const int bulletCount = 36;
    static float spiralAngle = 0.0f;
    spiralAngle += 0.15f;

    bool reflect = (lives == 2);
    for (int i = 0; i < bulletCount; i++) {
        float angle = spiralAngle + (i * 2.0f * PI) / bulletCount;
        new EnemyBullet(position_, Vector2::FromAngle(angle), 2.5f, reflect);
    }
}
void Boss::ShootFanBarrage() {
    const float PI = 3.14159265f;
    const int bulletCount = 15;
    bool reflect = (lives == 2);
    float baseAngle = PI / 2.0f;
    for (int layer = 0; layer < 4; layer++) {
        float speed_ = 2.0f + layer * 1.5f;
        for (int i = -bulletCount/2; i <= bulletCount/2; i++) {
            float angle = baseAngle + (i * 8.0f * PI / 180.0f);
            new EnemyBullet(position_, Vector2::FromAngle(angle), speed_, reflect);
        }
    }
}
void Boss::ShootTargetedBarrage() {
    const float PI = 3.14159265f;
    Player* player = dynamic_cast<Player*>(Master::sceneManager->GetCurrentScene()->GetObjectManager()->GetObject2DByTag(kTag2dPlayer));
    Vector2 targetPos(position_.x, position_.y + 200.0f);
    if (player != nullptr) {
        targetPos = Vector2(player->GetX(), player->GetY());
    }
    Vector2 dir = (targetPos - position_).Normalized();
    if (dir.MagnitudeSq() == 0.0f) dir = Vector2(0.0f, 1.0f);
    float baseAngle = Vector2(0,0).AngleTo(dir);
    for (int i = -2; i <= 2; i++) {
        float angle = baseAngle + (i * 5.0f * PI / 180.0f);
        new EnemyBullet(position_, Vector2::FromAngle(angle), 3.5f);
    }
    for (int i = -1; i <= 1; i++) {
        float angle = baseAngle + (i * 12.0f * PI / 180.0f);
        new EnemyBullet(position_, Vector2::FromAngle(angle), 2.5f);
    }
}

void Boss::ShootSimpleBarrage() {
    const float PI = 3.14159265f;
    float baseAngle = static_cast<float>(rand() % 360) * PI / 180.0f;
    for (int i = 0; i < 5; i++) {
        float angle = baseAngle + (i * 360.0f / 5.0f * PI / 180.0f);
        new EnemyBullet(position_, Vector2::FromAngle(angle), 3.5f, false, false, 120, 60);
    }
}

void Boss::ShootBouncingBarrage() {
    const float PI = 3.14159265f;
    for (int i = 0; i < 6; i++) {
        float angle = (i * 2.0f * PI) / 6.0f;
        new EnemyBullet(position_, Vector2::FromAngle(angle), 4.5f, true);
    }
}

void Boss::ShootSpellCardBarrage() {
    const float PI = 3.14159265f;
    for (int i = 0; i < 24; i++) {
        float angle = (i * 2.0f * PI) / 24.0f;
        new EnemyBullet(position_, Vector2::FromAngle(angle), 2.0f, true);
    }
    for (int i = 0; i < 12; i++) {
        float angle = (i * 2.0f * PI) / 12.0f + 0.5f;
        new EnemyBullet(position_, Vector2::FromAngle(angle), 5.0f, false);
    }
}

void Boss::TakeDamage(int damage_) {
    if (isDying || invincibleTimer > 0) return;

    Character::TakeDamage(damage_);

    if (hp_ <= 0) {
        lives--;
        std::vector<Object2D*> bullets = Master::sceneManager->GetCurrentScene()->GetObjectManager()->GetObject2DListByTag(kTag2dEnemyBullet);
        for (auto* b : bullets) {
            b->SetDeleteFlag(true);
        }
        
        if (lives > 0) {
            hp_ = max_hp_;
            invincibleTimer = 180;
        } else {
            isDying = true;
            SoundManager::GetInstance()->PlaySE("Resource/se_boss_die.wav");
            deathTimer = 180;
            if (collider_) {
                collider_->SetDeleteFlag(true);
            }

            Scene* current_scene_ = Master::sceneManager->GetCurrentScene();
            if (current_scene_) {
                auto bullets = current_scene_->GetObjectManager()->GetObject2DListByTag(kTag2dEnemyBullet);
                for (auto* b : bullets) {
                    b->SetDeleteFlag(true);
                }

                Player* p = dynamic_cast<Player*>(current_scene_->GetObjectManager()->GetObject2DByTag(kTag2dPlayer));
                if (p) p->Heal(3);
            }
            collider_ = nullptr;

            GameScene* gs = dynamic_cast<GameScene*>(Master::sceneManager->GetCurrentScene());
            if (gs != nullptr) {
                gs->AddScreenShake(180, 20.0f);
                gs->AddHitStop(30);
            }

            for(int i = 0; i < 40; i++) {
                float angle = static_cast<float>(rand() % 360) * 3.14159f / 180.0f;
                float speed_ = 3.0f + static_cast<float>(rand() % 50) / 10.0f;
                int life = 60 + (rand() % 60);
                float size_ = 15.0f + static_cast<float>(rand() % 40);
                int color_ = GetColor(255, 100 + rand() % 155, 0);
                new ExplosionParticle(position_.x, position_.y, speed_, angle, color_, life, size_);
            }
        }
    }
}

void Boss::Kill() {
    Character::Kill();

    if (bossType == 3) {
        ResultScene::kIsVictory = true;
        GameScene::isTimeAttackActive = false;
        Master::sceneManager->SetNextScene(SceneManager::SCENE_RESULT);
    }
}

void Boss::OnTrigger(Collider* collider_, Collider* check) {
    if (isDying) return;

    if (check != nullptr && check->GetParentObject() != nullptr) {
        Object2D* parent = check->GetParentObject();
        if (parent->GetTag() == kTag2dPlayerBullet) {
            int damage_ = 1;
            Bullet* b = dynamic_cast<Bullet*>(parent);
            if (b != nullptr) {
                damage_ = b->GetDamage();
                b->Kill();
            } else {
                MeleeAttack* m = dynamic_cast<MeleeAttack*>(parent);
                if (m != nullptr) {
                    damage_ = m->GetDamage();
                } else {
                    SpecialBullet* s = dynamic_cast<SpecialBullet*>(parent);
                    if (s != nullptr) {
                        damage_ = s->GetDamage();
                    } else {
                        PlayerHomingBullet* phb = dynamic_cast<PlayerHomingBullet*>(parent);
                        if (phb != nullptr) {
                            damage_ = phb->GetDamage();
                            phb->Kill();
                        }
                    }
                }
            }
            TakeDamage(damage_);
        }
    }
}

void Boss::Draw() {
    if (!is_active_) return;

    int bossGraphHandle = ResourceManager::GetInstance()->GetGraph("Resource/boss.png");

    if (bossGraphHandle != -1) {
        if (!isDying || (deathTimer / 5) % 2 == 0) {
            if (invincibleTimer > 0) {
                SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100 + (invincibleTimer % 20) * 5);
                DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 110, GetColor(200, 50, 255), TRUE);
                SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
                DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 110, GetColor(255, 150, 255), FALSE);
                DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 107, GetColor(255, 255, 255), FALSE);
                SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128 + (invincibleTimer % 20) * 5);
            }
            DrawExtendGraph(
                static_cast<int>(position_.x - 80.0f), 
                static_cast<int>(position_.y - 80.0f), 
                static_cast<int>(position_.x + 80.0f), 
                static_cast<int>(position_.y + 80.0f), 
                bossGraphHandle, 
                TRUE
            );
            if (invincibleTimer > 0) {
                SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
            }
        }
    } else {
        if (!isDying || (deathTimer / 5) % 2 == 0) {
            unsigned int color_ = GetColor(255, 0, 0);
            if (invincibleTimer > 0 && (invincibleTimer / 5) % 2 == 0) {
                color_ = GetColor(255, 255, 0);
            }
            DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 80, color_, TRUE);
        }
    }

    if (isDying) {
        DrawString(static_cast<int>(position_.x) - 150, static_cast<int>(position_.y) + 90, "I will be waiting for you in the next stage...!", GetColor(255, 100, 100));
    }
}