#include "EnemyManager.h"
#include "Enemy.h"
#include "Boss.h"
#include "Player.h"
#include "Master.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ObjectManager.h"
#include "Utility.h"
#include <DxLib.h>
#include <cstdlib>

// コンストラクタ（初期化処理）
EnemyManager::EnemyManager() {
    m_spawnTimer = 0;
    m_defeatedCount = 0;
    m_bossSpawned = false;
    m_currentPhase = 1;
    m_requiredKills = 10;
    m_currentBoss = nullptr;
}

// デストラクタ（解放処理）
EnemyManager::~EnemyManager() {
}

// 初期化（ステージリセット時などに使用）
void EnemyManager::Initialize() {
    m_spawnTimer = 0;
    m_defeatedCount = 0;
    m_bossSpawned = false;
    m_currentPhase = 1;
    m_requiredKills = 10;
    m_currentBoss = nullptr;
}

// 毎フレームの更新処理
void EnemyManager::Update() {
    // 敵の出現（スポーン）ロジック
    if (!m_bossSpawned)

    {
        // 撃破数が規定数に達したらボスを出現させる
        if (m_defeatedCount >= m_requiredKills)
        {
            DeleteEnemy(); // ボスが出てきたときは他の通常敵を一度全消去する   

            // 画面の上部中央（画面外のY座標-80）にボスを生成
            m_currentBoss = new Boss((float)Utility::SCREEN_WIDTH / 2.0f, -80.0f, m_currentPhase);
            m_bossSpawned = true;
        }
        else
        {
            // 通常敵の定期出現カウンターを進める
            m_spawnTimer++;
            if (m_spawnTimer >= 45)
            { // 45フレームごとに出現（敵の数を増加）
                m_spawnTimer = 0;

                // 画面外の上部（Y座標-50）のランダムなX座標を決定（縦スクロール用）
                float spawnX = 80.0f + static_cast<float>(rand() % 1120);
                float spawnY = -50.0f;
                SpawnEnemy(spawnX, spawnY);
               
            }
        }
    }
    else
    {
        // ボスがすでに存在する場合：ボスが倒されたかどうかをチェック
        if (m_currentBoss != nullptr && m_currentBoss->IsDeleteFlag()) {
            m_currentBoss = nullptr;
            m_bossSpawned = false;
            m_defeatedCount = 0; // 撃破数をリセット

            // フェーズ（難易度）を進行させ、次の規定撃破数を設定
            if (m_currentPhase == 1) {
                m_currentPhase = 2;
                m_requiredKills = 20; // 必要な撃破数を2倍に増やす
            }
            else if (m_currentPhase == 2) {
                m_currentPhase = 3;
                m_requiredKills = 40; // さらに2倍の撃破数を要求
            }
        }
        if (m_currentPhase == 2)//fhase2のみ中ボスを出すようにする
        {
            m_spawnTimer++;
            if (m_spawnTimer >= 10)
            { // 45フレームごとに出現（敵の数を増加）
                m_spawnTimer = 0;
                float randEnemySpawnChance = static_cast<float>(rand() % 100);
                if (randEnemySpawnChance < 10.0f)
                { // 10%の確率で中ボスをスポーン
                    if (GetMidBossCount() < 5) {
                        float spawnX = 80.0f + static_cast<float>(rand() % 1120);
                        float spawnY = -50.0f;
                        SpawnEnemy_Target(spawnX, spawnY, 4); // タイプ4（中ボス）をスポーン
                    }
                }
            }
        }
    }


}

// 敵を生成する処理
void EnemyManager::SpawnEnemy(float x, float y)
{
    int enemyType = 1; // デフォルトはタイプ1（ザコ敵）

    // フェーズ2の出現割合
    if (m_currentPhase == 2) {
        int r = rand() % 100;
        if (r < 10 && GetMidBossCount() < 5) enemyType = 4;       // 10%の確率で中ボス（タイプ4）
        else if (r < 40) enemyType = 2;  // 30%の確率でタイプ2

        // フェーズ3以降の出現割合
    }
    else if (m_currentPhase >= 3) {
        int r = rand() % 100;
        if (r < 10 && GetMidBossCount() < 5) enemyType = 4;       // 10%の確率で中ボス（タイプ4）
        else if (r < 30) enemyType = 3;  // 20%の確率でタイプ3（スタン弾所持）
        else if (r < 60) enemyType = 2;  // 30%の確率でタイプ2
    }

    // 決定したタイプの敵を生成
    new Enemy(x, y, enemyType);
}

void EnemyManager::SpawnEnemy_Target(float x, float y,int spawnnum)
{
    new Enemy(x, y, spawnnum); // タイプ4（中ボス）を生成
}

// 描画処理（現状は何も行わない）
void EnemyManager::Draw()
{
}

// 現在画面内にいるすべての敵を削除する処理
void EnemyManager::DeleteEnemy()
{
    std::vector<Object2D*> enemies = Master::sceneManager->GetCurrentScene()->GetObjectManager()->GetObject2DListByTag(Object2D::Tag2D_Enemy);
    for (Object2D* obj : enemies)
    {
        Enemy* enemy = dynamic_cast<Enemy*>(obj);
        if (enemy != nullptr)
        {
            enemy->Kill();
        }
    }
}

int EnemyManager::GetMidBossCount() const
{
    int count = 0;
    std::vector<Object2D*> enemies = Master::sceneManager->GetCurrentScene()->GetObjectManager()->GetObject2DListByTag(Object2D::Tag2D_Enemy);
    for (Object2D* obj : enemies)
    {
        Enemy* enemy = dynamic_cast<Enemy*>(obj);
        if (enemy != nullptr && enemy->GetEnemyType() == 4)
        {
            count++;
        }
    }
    return count;
}