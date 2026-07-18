#pragma once
#include "Character.h"
#include <memory>
#include "Barrier.h"

class SpecialBullet;

// プレイヤーの移動、攻撃、成長、バリアを管理するキャラクタークラス
class Player : public Character
{
public:
	static int kSelectedCharacterType; // タイトル・選択画面で選ばれたキャラクター種別

	enum AttackMode
	{
		kAttackModeMelee,
		kAttackModeSpecial
	};

private:
	float attack_power_;       // 攻撃力

	float attack_timer_{};     // 通常攻撃の経過タイマー
	float attack_interval_{};  // 通常攻撃の間隔

	float attack_timer2_{};    // 近接・特殊攻撃の経過タイマー
	float attack_interval2_{}; // 近接・特殊攻撃の間隔

	float barrier_count_{};    // バリア使用間隔の管理カウンター
	AttackMode attack_mode_;   // 現在の攻撃モード
	int special_cooldown_;     // 特殊攻撃のクールダウン

	std::weak_ptr<Barrier> barrier_; // プレイヤーが使用するバリア

	int level_;                // 現在レベル
	int xp_;                   // 現在経験値

	int xp_needed_;            // 次レベルに必要な経験値
	int level_up_timer_;       // レベルアップ表示用タイマー

	int spell_gauge_;          // スペルカードゲージ
	int max_spell_gauge_;      // スペルカードゲージ最大値

public:
	Player();

	virtual ~Player() override;

	std::shared_ptr<Barrier> GetBarrier() const { return barrier_.lock(); }

	/*
	 * プレイヤーの初期化を行う。
	 * [入力] なし
	 * [出力] なし
	 * [副作用] ステータス、攻撃間隔、バリア、経験値などを初期状態にする
	 */
	void Initialize();

	/*
	 * 入力、移動、攻撃、クールダウンを毎フレーム更新する。
	 * [入力] なし
	 * [出力] なし
	 * [副作用] プレイヤー状態と関連オブジェクトを更新する
	 */
	void Update() override;

	/*
	 * プレイヤー本体と演出を描画する。
	 * [入力] なし
	 * [出力] なし
	 * [副作用] 画面にプレイヤー関連の表示を行う
	 */
	void Draw() override;

	void Attack();

	void RunBarrierAttack();

	AttackMode GetAttackMode() const { return attack_mode_; }
	int GetSpecialCooldown() const { return special_cooldown_; }
	int GetLevel() const { return level_; }
	int GetXp() const { return xp_; }
	int GetXpNeeded() const { return xp_needed_; }
	int GetLevelUpTimer() const { return level_up_timer_; }
	int GetSpellGauge() const { return spell_gauge_; }
	int GetMaxSpellGauge() const { return max_spell_gauge_; }

	/*
	 * 経験値を加算し、必要量に達したらレベルアップする。
	 * [入力] amount: 加算する経験値
	 * [出力] なし
	 * [副作用] 経験値、レベル、攻撃力などが変化する
	 */
	void AddXp(int amount);

	virtual void TakeDamage(int damage) override;

	virtual void OnDeath() override;

	virtual void OnEnter(Collider* collider, Collider* check) override;

	virtual void OnTrigger(Collider* collider, Collider* check) override;

	virtual void OnExit(Collider* collider, Collider* check) override;

private:
	void HandleMovement();

	void ShootNormalBullets();

	void HandleDebugAttacks(int mouseInput);

	void UseSpellCard();

	void UpdateCooldowns();

	void HandleMeleeAndSpecialAttacks(int mouseInput);

	void DrawBarrierAura();

	void DrawStunEffect();

	void DrawPlayerSprite();
};