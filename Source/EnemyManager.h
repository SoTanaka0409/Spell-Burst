#pragma once
#include <vector>

class Enemy;

class EnemyManager {
private:
    std::vector<Enemy*> m_enemies; // Enemy list
    int m_spawnTimer;              // Spawn timer

public:
    EnemyManager();
    ~EnemyManager();

    void Initialize();
    void Update();
    void Draw();

    const std::vector<Enemy*>& GetEnemies() const { return m_enemies; }
};
