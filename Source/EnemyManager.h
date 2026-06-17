#pragma once
#include <vector>

class Enemy;
class Boss;

// 敵キャラクターの生成・進行フェーズを統括する管理クラス
// ボス出現条件の監視や、現在のフェーズ（ウェーブ）に応じた敵のスポーンを制御する
class EnemyManager {
private:
    int m_spawnTimer;              // 敵を出現（スポーン）させる間隔を計るタイマー
    int m_defeatedCount;           // プレイヤーが倒した敵の累計数（フェーズ進行の条件判定に使用）
    bool m_bossSpawned;            // 現在のフェーズでボスが既に出現したかどうかのフラグ

    int m_currentPhase;            // 現在の進行フェーズ（ウェーブ）番号
    int m_requiredKills;           // 次のフェーズへの移行、またはボス出現に必要な敵の討伐数
    Boss* m_currentBoss;           // 現在出現しているボスオブジェクトへのポインタ（未出現時はnullptr）

public:
    // コンストラクタ / デストラクタ
    // [入力] なし
    // [出力] なし
    // [副作用] オブジェクトの生成・破棄を行う
    EnemyManager();
    ~EnemyManager();

    // [入力] なし
    // [出力] なし
    // [副作用] フェーズや討伐数、タイマーなどの進行状況を初期化（リセット）する
    void Initialize();

    // [入力] なし
    // [出力] なし
    // [副作用] タイマーに応じた敵の生成、ボスの出現判定、フェーズ移行処理などを行う
    void Update();

    // [入力] なし
    // [出力] なし
    // [副作用] 画面上に次のフェーズまでの要討伐数や、ボス出現時の警告UIなどを描画する
    void Draw();

    // [入力] なし
    // [出力] なし
    // [副作用] オブジェクトリストを巡回し、死亡状態（キル処理済み）の敵を安全にメモリから削除する
    void DeleteEnemy();

    // [入力] x, y: 生成座標
    // [出力] なし
    // [副作用] 指定された座標に基本的な敵オブジェクトを生成し、ゲームシーン（リスト等）に登録する
    void SpawnEnemy(float x, float y);

    // [入力] x, y: 生成基準座標, spawnnum: 生成する数
    // [出力] なし
    // [副作用] プレイヤーを追尾するタイプ、または特定パターンで動く敵を複数生成しシーンに登録する
    void SpawnEnemy_Target(float x, float y, int spawnnum);

    // --- ゲッター・セッター群 ---

    // [入力] なし
    // [出力] int: 中ボス（特定タイプの敵）が現在画面上にいる数
    // [副作用] なし
    int GetMidBossCount() const;

    // [入力] なし
    // [出力] なし
    // [副作用] 敵を倒したカウント(m_defeatedCount)を1加算する（敵の死亡時に呼ばれる想定）
    void AddDefeatedCount() { m_defeatedCount++; }

    int GetDefeatedCount() const { return m_defeatedCount; }   // 現在の敵討伐数を取得
    int GetRequiredKills() const { return m_requiredKills; }   // ボス出現等に必要な目標討伐数を取得
    bool IsBossSpawned() const { return m_bossSpawned; }       // ボスが既に出現しているかを取得
    int GetCurrentPhase() const { return m_currentPhase; }     // 現在のフェーズ番号を取得
};