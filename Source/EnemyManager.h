#pragma once
#include <vector>

class Enemy;
class Boss;

class EnemyManager {
private:
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

	void DeleteEnemy();

    void SpawnEnemy(float x, float y);
	void SpawnEnemy_Target(float x, float y,int spawnnum);   

    int GetMidBossCount() const;
    void AddDefeatedCount() { m_defeatedCount++; }

    int GetDefeatedCount() const { return m_defeatedCount; }
    int GetRequiredKills() const { return m_requiredKills; }
    bool IsBossSpawned() const { return m_bossSpawned; }
    int GetCurrentPhase() const { return m_currentPhase; }
};
