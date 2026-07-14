#include "EnemyManager.h"
#include "ObjectManager.h"
#include "Enemy.h"
#include "Boss.h"
#include "Obstacle.h"
#include "Player.h"
#include "Master.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "Scene.h"
#include "Utility.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include <cstdlib>

EnemyManager::EnemyManager() {
    spawn_timer_ = 0;
    defeated_count_ = 0;
    boss_spawned_ = false;
    current_phase_ = 1;
    required_kills_ = 10;
    current_boss_.reset();
}

EnemyManager::~EnemyManager() {
}

void EnemyManager::Initialize() {
    spawn_timer_ = 0;
    defeated_count_ = 0;
    boss_spawned_ = false;
    current_phase_ = 1;
    required_kills_ = 10;
    current_boss_.reset();
}

void EnemyManager::Update() {
    if (!boss_spawned_) {
        if (defeated_count_ >= required_kills_) {
            DeleteEnemy();
            current_boss_ = ObjectManager::Instantiate<Boss>((float)Utility::SCREEN_WIDTH / 2.0f, -80.0f, current_phase_);
            boss_spawned_ = true;
        } else {
            SpawnPhaseEnemies();
        }
    } else {
        HandleBossTransition();
        if (current_phase_ == 2) {
            HandleMidBossSpawn();
        }
    }
}

void EnemyManager::SpawnPhaseEnemies() {
    spawn_timer_++;
    int interval = 45;
    if (GameScene::currentStage == 2) interval = 40;
    if (GameScene::currentStage == 3) interval = 35;
    
    if (spawn_timer_ >= interval) {
        spawn_timer_ = 0;
        float spawnX = 80.0f + static_cast<float>(rand() % 1120);
        float spawnY = -50.0f;
        bool spawnObstacle = false;
        if (GameScene::currentStage >= 2 && (rand() % 100) < 30) {
            spawnObstacle = true;
        }
        
        if (spawnObstacle) {
            ObjectManager::Instantiate<Obstacle>(spawnX, spawnY);
        } else {
            SpawnEnemy(spawnX, spawnY);
        }
    }
}

void EnemyManager::HandleBossTransition() {
    if (auto boss = current_boss_.lock(); boss && boss->IsDeleteFlag()) {
        current_boss_.reset();
        boss_spawned_ = false;
        defeated_count_ = 0;
        DeleteEnemy();
        if (current_phase_ == 1) {
            current_phase_ = 2;
            required_kills_ = 20;
        } else if (current_phase_ == 2) {
            current_phase_ = 3;
            required_kills_ = 40;
        }
    }
}

void EnemyManager::HandleMidBossSpawn() {
    spawn_timer_++;
    if (spawn_timer_ >= 10) {
        spawn_timer_ = 0;
        float randEnemySpawnChance = static_cast<float>(rand() % 100);
        if (randEnemySpawnChance < 10.0f) {
            if (GetMidBossCount() < 5) {
                float spawnX = 80.0f + static_cast<float>(rand() % 1120);
                float spawnY = -50.0f;
                SpawnEnemy_Target(spawnX, spawnY, 4);
            }
        }
    }
}

void EnemyManager::SpawnEnemy(float x, float y)
{
    int enemy_type_ = 1;
    if (current_phase_ == 2) {
        int r = rand() % 100;
        if (r < 10 && GetMidBossCount() < 5) enemy_type_ = 4;
        else if (r < 40) enemy_type_ = 2;
    }
    else if (current_phase_ >= 3) {
        int r = rand() % 100;
        if (r < 10 && GetMidBossCount() < 5) enemy_type_ = 4;
        else if (r < 30) enemy_type_ = 3;
        else if (r < 60) enemy_type_ = 2;
    }
    ObjectManager::Instantiate<Enemy>(x, y, enemy_type_);
}

void EnemyManager::SpawnEnemy_Target(float x, float y,int spawnnum)
{
    ObjectManager::Instantiate<Enemy>(x, y, spawnnum);
}

void EnemyManager::Draw()
{
}

void EnemyManager::DeleteEnemy()
{
    auto enemies = Master::sceneManager->GetCurrentScene()->GetObjectManager()->GetObject2DListByTag(Object2D::kTag2dEnemy);
    for (auto& obj : enemies)
    {
        Enemy* enemy = dynamic_cast<Enemy*>(obj.get());
        if (enemy != nullptr)
        {
            enemy->Kill();
        }
    }
}

int EnemyManager::GetMidBossCount() const
{
    int count = 0;
    auto enemies = Master::sceneManager->GetCurrentScene()->GetObjectManager()->GetObject2DListByTag(Object2D::kTag2dEnemy);
    for (auto& obj : enemies)
    {
        Enemy* enemy = dynamic_cast<Enemy*>(obj.get());
        if (enemy != nullptr && enemy->GetEnemyType() == 4)
        {
            count++;
        }
    }
    return count;
}




