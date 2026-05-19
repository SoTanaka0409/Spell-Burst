#include "EnemyManager.h"
#include "Enemy.h"
#include <DxLib.h>

EnemyManager::EnemyManager() {
    m_spawnTimer = 0;
}

EnemyManager::~EnemyManager() {
    // メモリの解放
    for (auto enemy : m_enemies) {
        delete enemy;
    }
    m_enemies.clear();
}

void EnemyManager::Initialize() {
    m_spawnTimer = 0;
}

void EnemyManager::Update() {
    // タイマーを進める
    m_spawnTimer++;

    // 60フレーム（約1秒）ごとに新しい敵を生成
    if (m_spawnTimer >= 60) {
        // X座標は 100 ～ 1180 の間でランダム、Y座標は画面上部(-50)
        float spawnX = (float)(GetRand(1080) + 100);
        float spawnY = -50.0f;
        
        m_enemies.push_back(new Enemy(spawnX, spawnY));
        m_spawnTimer = 0; // タイマーリセット
    }

    // 全ての敵を更新
    for (auto enemy : m_enemies) {
        enemy->Update();
    }

    // 生きていない（画面外に出た）敵をリストから削除する
    auto it = m_enemies.begin();
    while (it != m_enemies.end()) {
        if (!(*it)->IsActive()) {
            delete (*it); // メモリを解放
            it = m_enemies.erase(it); // リストから除外
        } else {
            ++it;
        }
    }
}

void EnemyManager::Draw() {
    // 全ての敵を描画
    for (auto enemy : m_enemies) {
        enemy->Draw();
    }
}
