#include "EnemyManager.h"
#include "Enemy.h"
#include "Boss.h"
#include "Obstacle.h"
#include "Player.h"
#include "Master.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "Scene.h"
#include "ObjectManager.h"
#include "Utility.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include <cstdlib>

EnemyManager::EnemyManager() {
    m_spawnTimer = 0;
    m_defeatedCount = 0;
    m_bossSpawned = false;
    m_currentPhase = 1;
    m_requiredKills = 10;
    m_currentBoss = nullptr;
}

EnemyManager::~EnemyManager() {
}

void EnemyManager::Initialize() {
    m_spawnTimer = 0;
    m_defeatedCount = 0;
    m_bossSpawned = false;
    m_currentPhase = 1;
    m_requiredKills = 10;
    m_currentBoss = nullptr;
}

void EnemyManager::Update() {
    if (!m_bossSpawned)
    {
        if (m_defeatedCount >= m_requiredKills)
        {
            DeleteEnemy();
            m_currentBoss = new Boss((float)Utility::SCREEN_WIDTH / 2.0f, -80.0f, m_currentPhase);
            m_bossSpawned = true;
        }
        else
        {
            m_spawnTimer++;
            int interval = 45;
            if (GameScene::s_currentStage == 2) interval = 40;
            if (GameScene::s_currentStage == 3) interval = 35;
            
            if (m_spawnTimer >= interval)
            {
                m_spawnTimer = 0;
                float spawnX = 80.0f + static_cast<float>(rand() % 1120);
                float spawnY = -50.0f;
                bool spawnObstacle = false;
                if (GameScene::s_currentStage >= 2 && (rand() % 100) < 30) {
                    spawnObstacle = true;
                }
                
                if (spawnObstacle) {
                    new Obstacle(spawnX, spawnY);
                } else {
                    SpawnEnemy(spawnX, spawnY);
                }
            }
        }
    }
    else
    {
        if (m_currentBoss != nullptr && m_currentBoss->IsDeleteFlag()) {
            m_currentBoss = nullptr;
            m_bossSpawned = false;
            m_defeatedCount = 0;
			DeleteEnemy();
            if (m_currentPhase == 1) {
                m_currentPhase = 2;
                m_requiredKills = 20;
            }
            else if (m_currentPhase == 2) {
                m_currentPhase = 3;
                m_requiredKills = 40;
            }
        }
        if (m_currentPhase == 2)
        {
            m_spawnTimer++;
            if (m_spawnTimer >= 10)
            {
                m_spawnTimer = 0;
                float randEnemySpawnChance = static_cast<float>(rand() % 100);
                if (randEnemySpawnChance < 10.0f)
                {
                    if (GetMidBossCount() < 5) {
                        float spawnX = 80.0f + static_cast<float>(rand() % 1120);
                        float spawnY = -50.0f;
                        SpawnEnemy_Target(spawnX, spawnY, 4);
                    }
                }
            }
        }
    }
}

void EnemyManager::SpawnEnemy(float x, float y)
{
    int enemyType = 1;
    if (m_currentPhase == 2) {
        int r = rand() % 100;
        if (r < 10 && GetMidBossCount() < 5) enemyType = 4;
        else if (r < 40) enemyType = 2;
    }
    else if (m_currentPhase >= 3) {
        int r = rand() % 100;
        if (r < 10 && GetMidBossCount() < 5) enemyType = 4;
        else if (r < 30) enemyType = 3;
        else if (r < 60) enemyType = 2;
    }
    new Enemy(x, y, enemyType);
}

void EnemyManager::SpawnEnemy_Target(float x, float y,int spawnnum)
{
    new Enemy(x, y, spawnnum);
}

void EnemyManager::Draw()
{
}

void EnemyManager::DeleteEnemy()
{
    std::vector<Object2D*> enemies = Master::sceneManager->GetCurrentScene()->GetObjectManager()->GetObject2DListByTag(Object2D::Tag2D_Enemy);
    for (Object2D* obj : enemies)
    {
        Enemy* enemy = dynamic_cast<Enemy*>(obj);
        if (enemy != nullptr)
        {
            enemy->Kill();
        }
    }
}

int EnemyManager::GetMidBossCount() const
{
    int count = 0;
    std::vector<Object2D*> enemies = Master::sceneManager->GetCurrentScene()->GetObjectManager()->GetObject2DListByTag(Object2D::Tag2D_Enemy);
    for (Object2D* obj : enemies)
    {
        Enemy* enemy = dynamic_cast<Enemy*>(obj);
        if (enemy != nullptr && enemy->GetEnemyType() == 4)
        {
            count++;
        }
    }
    return count;
}