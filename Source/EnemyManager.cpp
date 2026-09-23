#include "EnemyManager.h"
#include "ObjectManager.h"
#include "Enemy.h"
#include "Boss.h"
#include "Obstacle.h"
#include "Player.h"
#include "Master.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "Scene.h"
#include "Utility.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include <cstdlib>

/// @brief EnemyManager を生成する
EnemyManager::EnemyManager()
{
	spawn_timer_ = 0;
	defeated_count_ = 0;
	boss_spawned_ = false;
	current_phase_ = 1;
	required_kills_ = 10;
	current_boss_.reset();
}

/// @brief 破棄処理を行う
EnemyManager::~EnemyManager()
{
}

// 入力：なし
// 出力：なし
// 副作用：ウェーブ進行度、討伐ノルマ、およびボスの出現状態を初期化し、ゲーム開始時のクリーンな状態を担保する
/// @brief 初期化処理を行う
void EnemyManager::Initialize()
{
	spawn_timer_ = 0;
	defeated_count_ = 0;
	boss_spawned_ = false;
	current_phase_ = 1;
	required_kills_ = 10;
	current_boss_.reset();
}

// 入力：なし
// 出力：なし
// 副作用：討伐ノルマの監視とボス戦へのフェーズ移行、および通常ウェーブ時のザコ敵・中ボススポーン処理のディスパッチ
/// @brief 毎フレームの更新処理を行う
void EnemyManager::Update()
{
	if (!boss_spawned_)
	{
		// レベルデザイン：規定数の敵を倒した瞬間に画面内のザコを強制的に全滅させ、プレイヤーの意識を「1対1のボス戦」へとシームレスに集中させるためのメリハリ演出
		if (defeated_count_ >= required_kills_)
		{
			DeleteEnemy();
			current_boss_ = ObjectManager::Instantiate<Boss>((float)Utility::kScreenWidth / 2.0f, -80.0f, current_phase_);
			boss_spawned_ = true;
		}
		else
		{
			SpawnPhaseEnemies();
		}
	}
	else
	{
		HandleBossTransition();
		if (current_phase_ == 2)
		{
			HandleMidBossSpawn();
		}
	}
}

// 入力：なし
// 出力：なし
// 副作用：難易度（ステージ）に応じたインターバルタイマーの進行と、画面上部からのランダムな敵・障害物の動的生成
/// @brief SpawnPhaseEnemies を実行する
void EnemyManager::SpawnPhaseEnemies()
{
	spawn_timer_++;
	int interval = 45;

	// レベルデザイン：選択したステージ難易度（NORMAL/HARD/VERY HARD）に応じてスポーン間隔を段階的に短縮し、よりアグレッシブな弾幕密度と画面の圧迫感をプレイヤーに課す
	if (GameScene::current_stage_ == 2) interval = 40;
	if (GameScene::current_stage_ == 3) interval = 35;

	if (spawn_timer_ >= interval)
	{
		spawn_timer_ = 0;
		float spawnX = 80.0f + static_cast<float>(rand() % 1120);
		float spawnY = -50.0f;
		bool spawnObstacle = false;

		// レベルデザイン：後半ステージでは純粋な敵だけでなく「地形障害物（Obstacle）」を混ぜることで、単調な射撃だけでなく「移動と回避のルート取り」という空間認識の判断を要求する
		if (GameScene::current_stage_ >= 2 && (rand() % 100) < 30)
		{
			spawnObstacle = true;
		}

		if (spawnObstacle)
		{
			ObjectManager::Instantiate<Obstacle>(spawnX, spawnY);
		}
		else
		{
			SpawnEnemy(spawnX, spawnY);
		}
	}
}

// 入力：なし
// 出力：なし
// 副作用：ボスの死亡検知、次フェーズへの状態移行、および次期ウェーブに向けた討伐ノルマ（要求キル数）の段階的引き上げ
/// @brief HandleBossTransition を実行する
void EnemyManager::HandleBossTransition()
{
	// メモリ管理：ボスオブジェクトが既に破棄（Kill）されている、あるいはメモリから解放されている場合のみ安全に次フェーズの処理を回すための弱参照ロック検証
	auto boss = current_boss_.lock();
	if (boss_spawned_ && (!boss || boss->IsDeleteFlag()))
	{
		current_boss_.reset();
		boss_spawned_ = false;
		defeated_count_ = 0;
		DeleteEnemy();

		// レベルデザイン：フェーズ（ウェーブ）が進むごとに必要なキル数を倍々ゲームで増加させ、ゲーム中盤以降のプレイ時間を意図的に引き伸ばして生存の難易度を高める
		if (current_phase_ == 1)
		{
			current_phase_ = 2;
			required_kills_ = 20;
		}
		else if (current_phase_ == 2)
		{
			current_phase_ = 3;
			required_kills_ = 40;
		}
	}
}

// 入力：なし
// 出力：なし
// 副作用：フェーズ2特有の、中ボス（Type4）の限定的なスポーン抽選と生成
/// @brief HandleMidBossSpawn を実行する
void EnemyManager::HandleMidBossSpawn()
{
	spawn_timer_++;
	if (spawn_timer_ >= 10)
	{
		spawn_timer_ = 0;
		float randEnemySpawnChance = static_cast<float>(rand() % 100);
		if (randEnemySpawnChance < 10.0f)
		{
			// レベルデザイン：中ボス（Type4）は巨大な当たり判定と激しい弾幕を持つため、画面内に同時に存在できる数を「最大5体」に制限し、回避不能な理不尽な詰み状況（弾幕の壁）の発生を防ぐ
			if (GetMidBossCount() < 5)
			{
				float spawnX = 80.0f + static_cast<float>(rand() % 1120);
				float spawnY = -50.0f;
				SpawnEnemy_Target(spawnX, spawnY, 4);
			}
		}
	}
}

// 入力：x, y = スポーン座標
// 出力：なし
// 副作用：現在のフェーズ進行度と乱数テーブルに基づく、敵タイプ（1?4）の抽選およびインスタンス生成
/// @brief SpawnEnemy を実行する
/// @param x x の値
/// @param y y の値
void EnemyManager::SpawnEnemy(float x, float y)
{
	int enemy_type_ = 1;

	// レベルデザイン：フェーズ進行に応じて強力な敵タイプ（2?4）が抽選テーブルに混ざるように確率を調整し、ゲーム進行に合わせて段階的に視覚的変化と戦闘のバリエーションを提供する
	if (current_phase_ == 2)
	{
		int r = rand() % 100;
		if (r < 10 && GetMidBossCount() < 5) enemy_type_ = 4;
		else if (r < 40) enemy_type_ = 2;
	}
	else if (current_phase_ >= 3)
	{
		int r = rand() % 100;
		if (r < 10 && GetMidBossCount() < 5) enemy_type_ = 4;
		else if (r < 30) enemy_type_ = 3;
		else if (r < 60) enemy_type_ = 2;
	}
	ObjectManager::Instantiate<Enemy>(x, y, enemy_type_);
}

// 入力：x, y = スポーン座標, spawnnum = 指定する敵タイプID
// 出力：なし
// 副作用：指定された特定の敵タイプを狙い撃ちでインスタンス生成
/// @brief SpawnEnemy_Target を実行する
/// @param x x の値
/// @param y y の値
/// @param spawnnum spawnnum の値
void EnemyManager::SpawnEnemy_Target(float x, float y, int spawnnum)
{
	ObjectManager::Instantiate<Enemy>(x, y, spawnnum);
}

/// @brief 描画処理を行う
void EnemyManager::Draw()
{
}

// 入力：なし
// 出力：なし
// 副作用：現在画面に存在するすべてのザコ敵オブジェクトに対し、即死（Kill）シグナルを一斉送信する
/// @brief DeleteEnemy を実行する
void EnemyManager::DeleteEnemy()
{
	auto enemies = Master::sceneManager->GetCurrentScene()->GetObjectManager()->GetObject2DListByTag(Object2D::kTag2dEnemy);
	for (auto& obj : enemies)
	{
		// アーキテクチャ設計：ObjectManagerから取得した基底クラス（Object2D）をEnemy型へ安全にダウンキャストし、対象が確実に敵アクターである場合のみ一括削除ルーチンを叩く
		Enemy* enemy = dynamic_cast<Enemy*>(obj.get());
		if (enemy != nullptr)
		{
			enemy->Kill();
		}
	}
}

// アーキテクチャ設計：ObjectManagerが管理する全EntityからEnemyへの動的キャストを行い、現在アクティブな中ボスの数をリアルタイムに集計するステート・クエリ
/// @brief GetMidBossCount を実行する
/// @return int 戻り値
int EnemyManager::GetMidBossCount() const
{
	int count = 0;
	auto enemies = Master::sceneManager->GetCurrentScene()->GetObjectManager()->GetObject2DListByTag(Object2D::kTag2dEnemy);
	for (auto& obj : enemies)
	{
		Enemy* enemy = dynamic_cast<Enemy*>(obj.get());
		if (enemy != nullptr && enemy->GetEnemyType() == 4)
		{
			count++;
		}
	}
	return count;
}
