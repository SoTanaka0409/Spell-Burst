#pragma once
#include "Character.h"
#include "BossState.h"
#include "Barrier.h"
#include <memory>

class CapsuleCollider;

/// @brief ボス本体の移動、HP段階、無敵状態、弾幕パターンを管理するクラス
class Boss : public Character
{
private:
	int boss_type_;                       ///< ボスの種類・行動パターンID
	float target_x_;                      ///< 移動先のX座標
	float target_y_;                      ///< 移動先のY座標
	int attack_timer_;                    ///< 攻撃間隔を管理するタイマー
	int pattern_index_;                   ///< 現在の弾幕パターン番号
	bool is_dying_;                       ///< 死亡演出中かどうかを示すフラグ
	int death_timer_;                     ///< 死亡演出の残りフレーム数
	int lives_;                           ///< ボスの残りHP段階数
	int invincible_timer_;                ///< 被弾後などの一時無敵タイマー
	int invincible_cycle_timer_;          ///< 周期的な無敵処理用タイマー
	std::unique_ptr<BossState> state_;    ///< ボスの状態処理
	std::weak_ptr<Barrier> barrier_;      ///< ボスが使用するバリア

public:
	/// @brief ボスを生成する
	/// @param x 初期X座標
	/// @param y 初期Y座標
	/// @param bossType ボス種別
	Boss(float x, float y, int bossType = 3);

	/// @brief ボスを破棄する
	virtual ~Boss() override;

	/// @brief ボスの状態を毎フレーム更新する
	virtual void Update() override;

	/// @brief ボスを描画する
	virtual void Draw() override;

	/// @brief ボスの残りHP段階数を取得する
	/// @return int 残りHP段階数
	int GetLives() const { return lives_; }

	/// @brief ボスにダメージを与える
	/// @param damage 受けるダメージ量
	/// @details HPや残機を減らし、必要に応じて死亡演出へ移行する。
	virtual void TakeDamage(int damage) override;

	/// @brief ボスを削除対象にする
	virtual void Kill() override;

	/// @brief ボスの当たり判定半径を取得する
	/// @return float 当たり判定半径
	float GetRadius() const { return 80.0f; }

	/// @brief 他コライダーとの接触中処理を行う
	/// @param collider 自身のコライダー
	/// @param check 接触相手のコライダー
	virtual void OnTrigger(Collider* collider, Collider* check) override;

	/// @brief ボス死亡時の処理を行う
	virtual void OnDeath() override;

	/// @brief 死亡演出を更新する
	void UpdateDeath();

	/// @brief 無敵状態の表示を描画する
	void DrawInvincibility();

	/// @brief ボスHPバーを描画する
	void DrawHealthBar();

	/// @brief 全方位弾幕を発射する
	void ShootRadialBarrage();

	/// @brief 扇形弾幕を発射する
	void ShootFanBarrage();

	/// @brief プレイヤー狙い弾幕を発射する
	void ShootTargetedBarrage();

	/// @brief 直線弾幕を発射する
	void ShootSimpleBarrage();

	/// @brief 反射弾幕を発射する
	void ShootBouncingBarrage();

	/// @brief スペルカード弾幕を発射する
	void ShootSpellCardBarrage();

	/// @brief 新しい移動目標を選ぶ
	void SelectNewTarget();

	/// @brief ボス状態を切り替える
	/// @param newState 新しい状態オブジェクト
	void SetState(BossState* newState) { state_.reset(newState); }

	/// @brief ボス種別を取得する
	/// @return int ボス種別
	int GetBossType() const { return boss_type_; }

	/// @brief 死亡演出中かを取得する
	/// @return bool 死亡演出中ならtrue
	bool GetIsDying() const { return is_dying_; }

	/// @brief 無敵タイマーを取得する
	/// @return int 無敵残りフレーム数
	int GetInvincibleTimer() const { return invincible_timer_; }

	/// @brief 無敵タイマーを設定する
	/// @param t 無敵フレーム数
	void SetInvincibleTimer(int t) { invincible_timer_ = t; }
};