#include "EnemyManager.h"
#include "Enemy.h"
#include "Boss.h"
#include "Player.h"
#include "Master.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ObjectManager.h"
#include <DxLib.h>
#include <cstdlib>

EnemyManager::EnemyManager() {
    m_spawnTimer = 0;
    m_defeatedCount = 0;
    m_bossSpawned = false;
}

EnemyManager::~EnemyManager() {
    m_enemies.clear();
}

void EnemyManager::Initialize() {
    m_spawnTimer = 0;
    m_defeatedCount = 0;
    m_bossSpawned = false;
}

void EnemyManager::Update() {
    // Spawning logic
    if (!m_bossSpawned) {
        if (m_defeatedCount >= 10) {
            // Spawn Boss at the top center, slightly off-screen Y
            new Boss(640.0f, -80.0f);
            m_bossSpawned = true;
        } else {
            m_spawnTimer++;
            if (m_spawnTimer >= 90) { // Spawn every 90 frames
                m_spawnTimer = 0;
                // Spawn at random X coordinate off screen top (vertical scrolling)
                float spawnX = 80.0f + static_cast<float>(rand() % 1120);
                float spawnY = -50.0f;
                SpawnEnemy(spawnX, spawnY);
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
    Enemy* enemy = new Enemy(x, y);
    m_enemies.push_back(enemy);
}

void EnemyManager::Draw() {
}
