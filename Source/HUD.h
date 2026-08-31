#pragma once

class Player;
class Boss;
class EnemyManager;

/// @brief プレイヤーやボスの状態を画面に表示するHUDクラス
class HUD
{
public:
	/// @brief HUD表示用の値を初期化する
	static void Initialize();

	/// @brief HUD表示用の補間値を更新する
	/// @param player プレイヤー
	/// @param enemyManager 敵管理クラス
	/// @param boss ボス
	static void Update(Player* player, EnemyManager* enemyManager, Boss* boss);

	/// @brief HUD全体を描画する
	/// @param player プレイヤー
	/// @param enemyManager 敵管理クラス
	/// @param boss ボス
	/// @param cutinTimer カットイン残り時間
	/// @param cutinImageHandle カットイン画像ハンドル
	static void Draw(Player* player, EnemyManager* enemyManager, Boss* boss, int cutinTimer, int cutinImageHandle);

private:
	static float display_hp_ratio_;      ///< 表示用HP比率
	static float display_xp_ratio_;      ///< 表示用経験値比率
	static float display_spell_ratio_;   ///< 表示用スペルゲージ比率
	static float display_barrier_ratio_; ///< 表示用バリア比率
	static float boss_hp_ratio_;         ///< 表示用ボスHP比率

	/// @brief プレイヤー状態を描画する
	/// @param player プレイヤー
	static void DrawPlayerStatus(Player* player);

	/// @brief ボス状態を描画する
	/// @param boss ボス
	static void DrawBossStatus(Boss* boss);

	/// @brief 敵撃破進行度を描画する
	/// @param enemyManager 敵管理クラス
	static void DrawEnemyProgress(EnemyManager* enemyManager);

	/// @brief カットインを描画する
	/// @param cutinTimer カットイン残り時間
	/// @param cutinImageHandle カットイン画像ハンドル
	static void DrawCutin(int cutinTimer, int cutinImageHandle);
};