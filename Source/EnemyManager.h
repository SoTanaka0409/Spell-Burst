#pragma once
#include <vector>

class Enemy;
class Boss;

class EnemyManager {
private:
    std::vector<Enemy*> m_enemies; // Enemy list
    int m_spawnTimer;              // Spawn timer
    int m_defeatedCount;           // Defeated enemies count
    bool m_bossSpawned;            // Flag if boss is spawned

    // For phase management
    int m_currentPhase;            // Current phase (1-3)
    int m_requiredKills;           // Number of enemies defeated required for boss to appear
    Boss* m_currentBoss;           // Pointer of emerging boss

public:
    EnemyManager();
    ~EnemyManager();

    void Initialize();
    void Update();
    void Draw();

    void SpawnEnemy(float x, float y);

    const std::vector<Enemy*>& GetEnemies() const { return m_enemies; }
    int GetDefeatedCount() const { return m_defeatedCount; }
    int GetRequiredKills() const { return m_requiredKills; }
    bool IsBossSpawned() const { return m_bossSpawned; }
};
