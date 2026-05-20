#include "EnemyManager.h"
#include "Enemy.h"
#include <DxLib.h>
#include <cstdlib>

EnemyManager::EnemyManager() {
    m_spawnTimer = 0;
}

EnemyManager::~EnemyManager() {
    for (auto enemy : m_enemies) {
        delete enemy;
    }
    m_enemies.clear();
}

void EnemyManager::Initialize() {
    m_spawnTimer = 0;
}

void EnemyManager::Update() {
    m_spawnTimer++;
    if (m_spawnTimer >= 60) {
        float spawnX = (float)(rand() % 1200 + 40);
        float spawnY = -50.0f;
        m_enemies.push_back(new Enemy(spawnX, spawnY));
        m_spawnTimer = 0;
    }

   

    for (auto it = m_enemies.begin(); it != m_enemies.end(); ) {
        if (!(*it)->IsActive()) {
            delete *it;
            it = m_enemies.erase(it);
        } else {
            it++;
        }
    }
}

void EnemyManager::Draw() {
   
}
