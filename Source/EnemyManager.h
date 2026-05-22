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

    // フェーズ管理用
    int m_currentPhase;            // 現在のフェーズ（1〜3）
    int m_requiredKills;           // ボス出現に必要な敵の撃破数
    Boss* m_currentBoss;           // 出現中のボスのポインタ

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
