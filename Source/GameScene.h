#include <memory>
#pragma once
#include "Scene.h"

class EnemyManager;

/// @brief メインゲーム中の更新、描画、演出を管理するシーン
class GameScene : public Scene
{
private:
	/// @brief 背景を描画する
	void DrawBackground();

	/// @brief タイムアタック用タイマーを描画する
	void DrawTimeAttackTimer();

	/// @brief 画面効果を描画する
	void DrawEffects();

	std::unique_ptr<EnemyManager> enemy_manager_; ///< 敵とウェーブ進行の管理クラス
	int cutin_timer_;                             ///< カットイン表示の残りフレーム数
	int cutin_image_handle_;                      ///< カットイン画像ハンドル
	int screen_handle_;                           ///< 揺れ演出用の描画先スクリーンハンドル
	int shake_timer_;                             ///< 画面揺れの残りフレーム数
	float shake_magnitude_;                       ///< 画面揺れの強さ
	int hit_stop_timer_;                          ///< ヒットストップの残りフレーム数
	int damage_flash_timer_;                      ///< ダメージフラッシュの残りフレーム数
	unsigned int damage_flash_color_;             ///< ダメージフラッシュ色

public:
	static int current_stage_;          ///< 現在のステージ番号
	static int play_frame_count_;       ///< プレイ開始からの経過フレーム数
	static bool is_time_attack_active_; ///< タイムアタック中かを示すフラグ

	/// @brief ゲームシーンを生成する
	GameScene();

	/// @brief ゲームシーンを破棄する
	virtual ~GameScene() override;

	/// @brief ゲームシーンを初期化する
	void Initialize() override;

	/// @brief ゲームシーンを更新する
	void Update() override;

	/// @brief ゲームシーンを描画する
	void Draw() override;

	/// @brief ゲームシーンを終了処理する
	void Finalize() override;

	/// @brief カットイン演出を開始する
	void TriggerCutin();

	/// @brief 敵管理クラスを取得する
	/// @return EnemyManager* 敵管理クラス
	EnemyManager* GetEnemyManager() const { return enemy_manager_.get(); }

	/// @brief 画面揺れを追加する
	/// @param duration 揺れ時間
	/// @param magnitude 揺れの強さ
	void AddScreenShake(int duration, float magnitude);

	/// @brief ヒットストップを追加する
	/// @param duration 停止時間
	void AddHitStop(int duration);

	/// @brief ダメージフラッシュを追加する
	/// @param duration 表示時間
	/// @param color 表示色
	void AddDamageFlash(int duration, unsigned int color);
};