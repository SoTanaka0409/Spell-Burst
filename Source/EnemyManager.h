#pragma once
#include <vector>

class Enemy;

class EnemyManager {
private:
    std::vector<Enemy*> m_enemies; // Enemy list
    int m_spawnTimer;              // Spawn timer
    int m_defeatedCount;           // Defeated enemies count
    bool m_bossSpawned;            // Flag if boss is spawned

public:
    EnemyManager();
    ~EnemyManager();

    void Initialize();
    void Update();
    void Draw();

    void SpawnEnemy(float x, float y);

    const std::vector<Enemy*>& GetEnemies() const { return m_enemies; }
    int GetDefeatedCount() const { return m_defeatedCount; }
    bool IsBossSpawned() const { return m_bossSpawned; }
};
