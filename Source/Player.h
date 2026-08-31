#pragma once
#include "Character.h"
#include <memory>
#include "Barrier.h"

class SpecialBullet;

/// @brief プレイヤーの移動、攻撃、成長、バリアを管理するキャラクタークラス
class Player : public Character
{
public:
	static int kSelectedCharacterType;  ///< タイトル・選択画面で選ばれたキャラクター種別

	/// @brief プレイヤーの攻撃モード
	enum AttackMode
	{
		kAttackModeMelee,   ///< 近接攻撃モード
		kAttackModeSpecial  ///< 特殊攻撃モード
	};

private:
	float attack_power_;             ///< 攻撃力
	float attack_timer_{};           ///< 通常攻撃の経過タイマー
	float attack_interval_{};        ///< 通常攻撃の間隔
	float attack_timer2_{};          ///< 近接・特殊攻撃の経過タイマー
	float attack_interval2_{};       ///< 近接・特殊攻撃の間隔
	float barrier_count_{};          ///< バリア使用間隔の管理カウンター
	AttackMode attack_mode_;         ///< 現在の攻撃モード
	int special_cooldown_;           ///< 特殊攻撃のクールダウン
	std::weak_ptr<Barrier> barrier_; ///< プレイヤーが使用するバリア
	int level_;                      ///< 現在レベル
	int xp_;                         ///< 現在経験値
	int xp_needed_;                  ///< 次レベルに必要な経験値
	int level_up_timer_;             ///< レベルアップ表示用タイマー
	int spell_gauge_;                ///< スペルカードゲージ
	int max_spell_gauge_;            ///< スペルカードゲージ最大値

public:
	/// @brief プレイヤーを生成する
	Player();

	/// @brief プレイヤーを破棄する
	virtual ~Player() override;

	/// @brief バリアを取得する
	/// @return std::shared_ptr<Barrier> バリアの共有ポインタ
	std::shared_ptr<Barrier> GetBarrier() const { return barrier_.lock(); }

	/// @brief プレイヤーを初期化する
	/// @details ステータス、攻撃間隔、バリア、経験値などを初期状態にする。
	void Initialize();

	/// @brief 入力、移動、攻撃、クールダウンを毎フレーム更新する
	void Update() override;

	/// @brief プレイヤー本体と演出を描画する
	void Draw() override;

	/// @brief 現在の攻撃モードに応じて攻撃する
	void Attack();

	/// @brief バリア攻撃を実行する
	void RunBarrierAttack();

	/// @brief 現在の攻撃モードを取得する
	/// @return AttackMode 現在の攻撃モード
	AttackMode GetAttackMode() const { return attack_mode_; }

	/// @brief 特殊攻撃のクールダウンを取得する
	/// @return int クールダウン残りフレーム数
	int GetSpecialCooldown() const { return special_cooldown_; }

	/// @brief 現在レベルを取得する
	/// @return int 現在レベル
	int GetLevel() const { return level_; }

	/// @brief 現在経験値を取得する
	/// @return int 現在経験値
	int GetXp() const { return xp_; }

	/// @brief 次レベルに必要な経験値を取得する
	/// @return int 必要経験値
	int GetXpNeeded() const { return xp_needed_; }

	/// @brief レベルアップ表示タイマーを取得する
	/// @return int 残り表示フレーム数
	int GetLevelUpTimer() const { return level_up_timer_; }

	/// @brief スペルゲージを取得する
	/// @return int 現在のスペルゲージ
	int GetSpellGauge() const { return spell_gauge_; }

	/// @brief スペルゲージ最大値を取得する
	/// @return int スペルゲージ最大値
	int GetMaxSpellGauge() const { return max_spell_gauge_; }

	/// @brief 経験値を加算し、必要量に達したらレベルアップする
	/// @param amount 加算する経験値
	void AddXp(int amount);

	/// @brief プレイヤーにダメージを与える
	/// @param damage 受けるダメージ量
	virtual void TakeDamage(int damage) override;

	/// @brief プレイヤー死亡時の処理を行う
	virtual void OnDeath() override;

	/// @brief 他コライダーに接触した瞬間の処理を行う
	/// @param collider 自身のコライダー
	/// @param check 接触相手のコライダー
	virtual void OnEnter(Collider* collider, Collider* check) override;

	/// @brief 他コライダーとの接触中処理を行う
	/// @param collider 自身のコライダー
	/// @param check 接触相手のコライダー
	virtual void OnTrigger(Collider* collider, Collider* check) override;

	/// @brief 他コライダーから離れた瞬間の処理を行う
	/// @param collider 自身のコライダー
	/// @param check 接触相手のコライダー
	virtual void OnExit(Collider* collider, Collider* check) override;

private:
	/// @brief 移動入力を処理する
	void HandleMovement();

	/// @brief 通常弾を発射する
	void ShootNormalBullets();

	/// @brief デバッグ用攻撃入力を処理する
	/// @param mouseInput マウス入力状態
	void HandleDebugAttacks(int mouseInput);

	/// @brief スペルカードを使用する
	void UseSpellCard();

	/// @brief 攻撃や特殊行動のクールダウンを更新する
	void UpdateCooldowns();

	/// @brief 近接攻撃と特殊攻撃を処理する
	/// @param mouseInput マウス入力状態
	void HandleMeleeAndSpecialAttacks(int mouseInput);

	/// @brief バリアのオーラ演出を描画する
	void DrawBarrierAura();

	/// @brief スタン中の演出を描画する
	void DrawStunEffect();

	/// @brief プレイヤースプライトを描画する
	void DrawPlayerSprite();
};