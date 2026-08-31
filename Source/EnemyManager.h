#pragma once
#include <vector>
#include <memory>

class Enemy;
class Boss;

/// @brief 敵の出現、ウェーブ進行、ボスへの移行をまとめて管理するクラス
class EnemyManager
{
private:
	int spawn_timer_;                  ///< 次の敵を出現させるまでのタイマー
	int defeated_count_;               ///< 現在フェーズで倒した敵の数
	bool boss_spawned_;                ///< 現在フェーズでボスが出現済みかを示すフラグ
	int current_phase_;                ///< 現在のウェーブ・フェーズ番号
	int required_kills_;               ///< 次フェーズやボス出現に必要な撃破数
	std::weak_ptr<Boss> current_boss_; ///< 現在出現しているボスへの弱参照

public:
	/// @brief 敵管理クラスを生成する
	EnemyManager();

	/// @brief 敵管理クラスを破棄する
	~EnemyManager();

	/// @brief 敵管理の状態を初期化する
	/// @details ウェーブ進行度、討伐数、ボス出現状態をリセットする。
	void Initialize();

	/// @brief 敵のスポーンとウェーブ進行を更新する
	/// @details 敵生成、ボス移行、フェーズ更新を行う。
	void Update();

	/// @brief 敵管理に関する表示を行う
	void Draw();

	/// @brief 画面上の通常敵を削除する
	void DeleteEnemy();

private:
	/// @brief 現在フェーズに応じた敵を生成する
	void SpawnPhaseEnemies();

	/// @brief ボス出現や撃破後のフェーズ移行を処理する
	void HandleBossTransition();

	/// @brief 中ボスの出現を処理する
	void HandleMidBossSpawn();

public:
	/// @brief フェーズに応じた敵を指定座標へ生成する
	/// @param x スポーンX座標
	/// @param y スポーンY座標
	void SpawnEnemy(float x, float y);

	/// @brief 指定タイプの敵を指定座標へ生成する
	/// @param x スポーンX座標
	/// @param y スポーンY座標
	/// @param spawnnum 敵タイプ
	void SpawnEnemy_Target(float x, float y, int spawnnum);

	/// @brief 現在出現している中ボスの数を取得する
	/// @return int 中ボスの数
	int GetMidBossCount() const;

	/// @brief 撃破数を1加算する
	void AddDefeatedCount() { defeated_count_++; }

	/// @brief 現在フェーズの撃破数を取得する
	/// @return int 撃破数
	int GetDefeatedCount() const { return defeated_count_; }

	/// @brief 次フェーズに必要な撃破数を取得する
	/// @return int 必要撃破数
	int GetRequiredKills() const { return required_kills_; }

	/// @brief ボスが出現済みかを取得する
	/// @return bool 出現済みならtrue
	bool IsBossSpawned() const { return boss_spawned_; }

	/// @brief 現在フェーズを取得する
	/// @return int 現在フェーズ
	int GetCurrentPhase() const { return current_phase_; }
};