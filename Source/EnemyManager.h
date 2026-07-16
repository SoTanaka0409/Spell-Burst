#pragma once
#include <vector>
#include <memory>

class Enemy;
class Boss;

// 設計ルール：ゲームのウェーブ（フェーズ）進行、ザコ敵のスパーン条件、およびボスの出現・生存監視を統括する進行管理クラス
class EnemyManager
{
private:
	int spawn_timer_;                // ザコ敵が過密状態になるのを防ぎ、一定時間ごとに湧かせるためのスポーンインターバルタイマー
	int defeated_count_;             // 次のフェーズ移行やボス出現トリガーの判定基準となる、現在の累計撃破アクター数
	bool boss_spawned_;              // 同一フェーズ内でボスが重複して出現するバグ（多重生成）を防止するための出現完了フラグ

	int current_phase_;              // 難易度テーブル（ザコ出現密度や敵ステータス倍率）を参照するための現在の進行ウェーブ番号
	int required_kills_;             // プレイヤーが次のフェーズへ進む、またはボスを引きずり出すために必要な最低討伐ノルマ数
	std::weak_ptr<Boss> current_boss_; // ボス消滅時のダングリングポインタ（不正参照クラッシュ）を防止し、生存を安全に検知する弱参照ポインタ

public:
	EnemyManager();
	~EnemyManager();

	// 入力：なし
	// 出力：なし
	// 副作用：討伐カウンターのリセット、フェーズ1の初期化、スポーンタイマーの開始
	void Initialize();

	// 入力：なし
	// 出力：なし
	// 副作用：タイマー連動のザコ敵湧き、撃破ノルマ達成時のボス出現演出（フェーズ移行）のトリガー更新
	void Update();

	// 入力：なし
	// 出力：なし
	// 副作用：画面上部へのボス警告UI、残りの必要討伐数メーター、およびデバッグ情報の描画
	void Draw();

	// 入力：なし
	// 出力：なし
	// 副作用：ステージ外へ離脱したアクター、またはHPがゼロになり死亡モーションが完了した敵インスタンスのメモリ一括解放
	void DeleteEnemy();

private:
	// 副作用：現在のフェーズに応じた配置テーブルから、画面外のランダムな座標へザコ敵を生成・配置する
	void SpawnPhaseEnemies();

	// 副作用：ボス戦専用BGMへの切り替え、およびステージ中央へのボス出現シネマティックカメラの起動
	void HandleBossTransition();

	// 副作用：ゲーム中盤のダレ場を防ぐための、中ボス（エリートエネミー）の突発スポーンとアラート演出
	void HandleMidBossSpawn();

public:
	// 入力：x, y = 発生させるワールド座標
	// 副作用：基本AIを持つ通常ザコ敵を生成し、ObjectManagerの管理リストへ追加
	void SpawnEnemy(float x, float y);

	// 入力：x, y = スポーン基準座標, spawnnum = 同時生成数
	// 入力：プレイヤーの方向へ初期ベクトルを向けた、奇襲性の高い突撃タイプ（または編隊）の敵を指定数生成する
	void SpawnEnemy_Target(float x, float y, int spawnnum);

	// 入力：なし
	// 出力：現在ステージ上に生存している中ボスの総数
	int GetMidBossCount() const;

	// 入力：なし
	// 出力：なし
	// 副作用：敵が死亡した際、アクター側からのコールバックとして撃破数を1加算
	void AddDefeatedCount() { defeated_count_++; }

	int GetDefeatedCount() const { return defeated_count_; }
	int GetRequiredKills() const { return required_kills_; }
	bool IsBossSpawned() const { return boss_spawned_; }
	int GetCurrentPhase() const { return current_phase_; }
};