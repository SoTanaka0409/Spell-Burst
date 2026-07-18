#pragma once
#include "Character.h"
#include "BossState.h"
#include "Barrier.h"
#include <memory>

class CapsuleCollider;

// ボス本体の移動、HP段階、無敵状態、弾幕パターンを管理するクラス
class Boss : public Character
{
private:
	int boss_type_;               // ボスの種類・行動パターンID
	float target_x_;              // 移動先のX座標
	float target_y_;              // 移動先のY座標

	int attack_timer_;            // 攻撃間隔を管理するタイマー
	int pattern_index_;           // 現在の弾幕パターン番号

	bool is_dying_;               // 死亡演出中かどうか
	int death_timer_;             // 死亡演出の残りフレーム数

	int lives_;                   // ボスの残りHP段階数
	int invincible_timer_;        // 被弾後などの一時無敵タイマー
	int invincible_cycle_timer_;  // 周期的な無敵処理用タイマー

	std::unique_ptr<BossState> state_; // ボスの状態処理
	std::weak_ptr<Barrier> barrier_;   // ボスが使用するバリア

public:
	Boss(float x, float y, int bossType = 3);
	virtual ~Boss() override;

	virtual void Update() override;
	virtual void Draw() override;

	int GetLives() const { return lives_; }

	/*
	 * ボスにダメージを与える。
	 * [入力] damage: 受けるダメージ量
	 * [出力] なし
	 * [副作用] HPや残機を減らし、必要に応じて死亡演出へ移行する
	 */
	virtual void TakeDamage(int damage) override;
	virtual void Kill() override;

	float GetRadius() const { return 80.0f; }

	virtual void OnTrigger(Collider* collider, Collider* check) override;

	virtual void OnDeath() override;

	void UpdateDeath();
	void DrawInvincibility();
	void DrawHealthBar();

	// ボスの各種弾幕パターン
	void ShootRadialBarrage();
	void ShootFanBarrage();
	void ShootTargetedBarrage();
	void ShootSimpleBarrage();
	void ShootBouncingBarrage();
	void ShootSpellCardBarrage();
	void SelectNewTarget();

	void SetState(BossState* newState) { state_.reset(newState); }
	int GetBossType() const { return boss_type_; }
	bool GetIsDying() const { return is_dying_; }
	int GetInvincibleTimer() const { return invincible_timer_; }
	void SetInvincibleTimer(int t) { invincible_timer_ = t; }
};