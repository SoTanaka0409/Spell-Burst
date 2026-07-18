#pragma once
#include <vector>
#include <memory>

class Enemy;
class Boss;

// 敵の出現、ウェーブ進行、ボスへの移行をまとめて管理するクラス
class EnemyManager
{
private:
	int spawn_timer_;                  // 次の敵を出現させるまでのタイマー
	int defeated_count_;               // 現在フェーズで倒した敵の数
	bool boss_spawned_;                // 現在フェーズでボスが出現済みか

	int current_phase_;                // 現在のウェーブ・フェーズ番号
	int required_kills_;               // 次フェーズやボス出現に必要な撃破数
	std::weak_ptr<Boss> current_boss_; // 現在出現しているボスへの弱参照

public:
	EnemyManager();
	~EnemyManager();

	/*
	 * 敵管理の状態を初期化する。
	 * [入力] なし
	 * [出力] なし
	 * [副作用] ウェーブ進行度、討伐数、ボス出現状態をリセットする
	 */
	void Initialize();

	/*
	 * 敵のスポーンとウェーブ進行を更新する。
	 * [入力] なし
	 * [出力] なし
	 * [副作用] 敵生成、ボス移行、フェーズ更新を行う
	 */
	void Update();

	/*
	 * 敵管理に関する表示を行う。
	 * [入力] なし
	 * [出力] なし
	 * [副作用] 必要に応じてデバッグ情報などを描画する
	 */
	void Draw();

	/*
	 * 画面上の通常敵を削除する。
	 * [入力] なし
	 * [出力] なし
	 * [副作用] 敵オブジェクトへ削除フラグを立てる
	 */
	void DeleteEnemy();

private:
	void SpawnPhaseEnemies();

	void HandleBossTransition();

	void HandleMidBossSpawn();

public:
	/*
	 * フェーズに応じた敵を指定座標へ生成する。
	 * [入力] x, y: スポーン座標
	 * [出力] なし
	 * [副作用] 抽選された敵をObjectManagerへ登録する
	 */
	void SpawnEnemy(float x, float y);

	/*
	 * 指定タイプの敵を指定座標へ生成する。
	 * [入力] x, y: スポーン座標, spawnnum: 敵タイプ
	 * [出力] なし
	 * [副作用] 指定された敵をObjectManagerへ登録する
	 */
	void SpawnEnemy_Target(float x, float y, int spawnnum);

	/*
	 * 現在出現している中ボスの数を取得する。
	 * [入力] なし
	 * [出力] 中ボスの数
	 * [副作用] なし
	 */
	int GetMidBossCount() const;

	void AddDefeatedCount() { defeated_count_++; }

	int GetDefeatedCount() const { return defeated_count_; }
	int GetRequiredKills() const { return required_kills_; }
	bool IsBossSpawned() const { return boss_spawned_; }
	int GetCurrentPhase() const { return current_phase_; }
};