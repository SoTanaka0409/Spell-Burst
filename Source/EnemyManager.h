#pragma once
#include <vector>

// 前方宣言
class Enemy;

class EnemyManager {
private:
    std::vector<Enemy*> m_enemies; // 敵のリスト
    int m_spawnTimer;              // 敵を出すためのタイマー

public:
    EnemyManager();
    ~EnemyManager();

    void Initialize();
    void Update();
    void Draw();

    // 当たり判定用に敵のリストを取得する関数
    const std::vector<Enemy*>& GetEnemies() const { return m_enemies; }
};
