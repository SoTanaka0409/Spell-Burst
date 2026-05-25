#include "EnemyManager.h"
#include "Enemy.h"
#include "Boss.h"
#include "Player.h"
#include "Master.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ObjectManager.h"
#include "Utility.h"
#include <DxLib.h>
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
    m_enemies.clear();
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
    // Spawning logic
    if (!m_bossSpawned) {
        if (m_defeatedCount >= m_requiredKills) {
            // Spawn Boss at the top center, slightly off-screen Y
            m_currentBoss = new Boss((float)Utility::SCREEN_WIDTH / 2.0f, -80.0f, m_currentPhase);
            m_bossSpawned = true;
        } else {
            m_spawnTimer++;
            if (m_spawnTimer >= 45) { // Spawn every 45 frames (increased enemy count)
                m_spawnTimer = 0;
                // Spawn at random X coordinate off screen top (vertical scrolling)
                float spawnX = 80.0f + static_cast<float>(rand() % 1120);
                float spawnY = -50.0f;
                SpawnEnemy(spawnX, spawnY);
            }
        }
    } else {
        // Check if boss was defeated
        if (m_currentBoss != nullptr && m_currentBoss->IsDeleteFlag()) {
            m_currentBoss = nullptr;
            m_bossSpawned = false;
            m_defeatedCount = 0;
            
            if (m_currentPhase == 1) {
                m_currentPhase = 2;
                m_requiredKills = 20; // Request twice as many enemies
            } else if (m_currentPhase == 2) {
                m_currentPhase = 3;
                m_requiredKills = 40; // Request twice as many enemies
            }
        }
    }

    // Clean up inactive / deleted enemies from the manager list to avoid dangling pointers
    for (auto it = m_enemies.begin(); it != m_enemies.end(); ) {
        if (*it == nullptr || (*it)->IsDeleteFlag() || !(*it)->IsActive()) {
            if (*it != nullptr && (*it)->GetHp() <= 0) {
                m_defeatedCount++;
                // Grant XP to the player for defeating an enemy
                Player* player = dynamic_cast<Player*>(
                    Master::sceneManager->GetCurrentScene()->GetObjectManager()->GetObject2DByTag(Object2D::Tag2D_Player)
                );
                if (player != nullptr) {
                    player->AddXp(1);
                }
            }
            it = m_enemies.erase(it);
        } else {
            it++;
        }
    }
}

void EnemyManager::SpawnEnemy(float x, float y) {
    int enemyType = 1;
    if (m_currentPhase == 2) {
        int r = rand() % 100;
        if (r < 10) enemyType = 4; // 10% chance of becoming a medium boss (type 4)
        else if (r < 40) enemyType = 2; // 30% chance of type 2
    } else if (m_currentPhase >= 3) {
        int r = rand() % 100;
        if (r < 10) enemyType = 4; // 10% chance of becoming a medium boss (type 4)
        else if (r < 30) enemyType = 3; // 20% chance of Type 3 (stun)
        else if (r < 60) enemyType = 2; // 30% chance of type 2
    }
    
    Enemy* enemy = new Enemy(x, y, enemyType);
    m_enemies.push_back(enemy);
}

void EnemyManager::Draw() {
}
