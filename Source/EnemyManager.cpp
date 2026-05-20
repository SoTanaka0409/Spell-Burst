#include "EnemyManager.h"
#include "Enemy.h"
#include <DxLib.h>
#include <cstdlib>

EnemyManager::EnemyManager() {
    m_spawnTimer = 0;
}

EnemyManager::~EnemyManager() {
    // Note: Do not delete enemies here, because ObjectManager owns and deletes them.
    m_enemies.clear();
}

void EnemyManager::Initialize() {
    m_spawnTimer = 0;
}

void EnemyManager::Update() {
    m_spawnTimer++;
    if (m_spawnTimer >= 90) { // Spawn every 90 frames (approx. 1.5 seconds)
        m_spawnTimer = 0;
        // Spawn at random Y coordinate off screen right (horizontal scrolling)
        float spawnX = 1330.0f;
        float spawnY = 50.0f + static_cast<float>(rand() % 620);
        SpawnEnemy(spawnX, spawnY);
    }

    // Clean up inactive / deleted enemies from the manager list to avoid dangling pointers
    for (auto it = m_enemies.begin(); it != m_enemies.end(); ) {
        if (*it == nullptr || (*it)->IsDeleteFlag() || !(*it)->IsActive()) {
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
