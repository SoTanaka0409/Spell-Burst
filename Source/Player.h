#pragma once
#include "Character.h"
#include <memory>
#include "Barrier.h"

class SpecialBullet;

// 設計ルール：プレイヤーの移動・攻撃入力制御、成長システム（レベル・XP）、バリア等の防御機構を統合管理する自機アクタークラス
class Player : public Character
{
public:
	static int kSelectedCharacterType; // キャラクター選択画面から引き継いだ、見た目や基礎パラメーターテーブルを切り替えるためのID

	enum AttackMode
	{
		kAttackModeMelee,
		kAttackModeSpecial
	};

private:
	float attack_power_;             // レベルアップに伴うスキル補正やアイテム効果が乗算される、全攻撃の基準威力値
	float attack_timer_{};           // 通常ショットの連続発射を制限し、ゲームのテンポと画面内の弾数を適正に保つためのインターバルカウンタ
	float attack_interval_{};        // キャラクター固有の基本ショット速度、および装備による連射速度上昇（バフ）を反映する基準時間
	float attack_timer2_{};          // 近接攻撃やサブウェポンなど、通常ショットとは完全に独立してクールダウンを並行処理するタイマー
	float attack_interval2_{};       // 近接/サブウェポンの連続使用を防ぎ、攻撃アクションごとのメリハリを生み出すための間隔値
	float barrier_count_{};          // 一度に複数枚のバリアを展開して、無敵時間が意図せず無限に上書きされてしまうバグを防ぐための計数用
	AttackMode attack_mode_;         // 近接特化と射撃特化など、プレイヤーの操作スタイルや弾道演算の分岐を制御する攻撃モード状態
	int special_cooldown_;           // 強力な特殊スキル（ボム等）が再使用可能になるまでの、ミリ秒/フレーム単位のクールタイム残量
	std::weak_ptr<Barrier> barrier_; // バリア消滅時のダングリングポインタ（無効なメモリ参照）を防ぎ、生存時のみロックしてアクセスする弱参照

	int level_;                      // プレイヤーの総合的な強さを示し、各アビリティの最大値を規定する現在のレベル数
	int xp_;                         // 敵撃破やアイテム回収時に加算され、レベルアップテーブルの閾値（xp_needed_）と比較される現在経験値
	int xp_needed_;                  // 次のレベルへ進むために必要な累積XP（レベルごとに指数関数的に上昇する仕様）
	int level_up_timer_;             // レベルアップ時に頭上に「LEVEL UP!」エフェクトを一定時間浮かせておくための演出継続タイマー
	int spell_gauge_;                // 敵にダメージを与える・特定の牛を回収することで蓄積される、必殺技（スペルカード）発動用リソース
	int max_spell_gauge_;            // キャラクタータイプごとに個別に設定される、スペルカード発動に必要な最大ゲージ制限値

public:
	Player();
	virtual ~Player() override;

	std::shared_ptr<Barrier> GetBarrier() const { return barrier_.lock(); }
	void Initialize();

	// 入力：なし
	// 出力：なし
	// 副作用：キー入力に基づいた位置移動、弾丸生成、無敵・スタン状態などの被弾ペナルティタイマーの減算
	void Update() override;

	// 入力：なし
	// 出力：なし
	// 副作用：自機モデルのレンダリング、被弾時の赤点滅、展開中のバリアオーラ、および頭上へのスタンエフェクトの描画
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

	// 入力：amount = 増加させるXP
	// 出力：なし
	// 副作用：XP加算、閾値到達時の連続レベルアップ処理、全回復およびステータス向上、レベルアップ演出タイマーの起動
	void AddXp(int amount);

	// 入力：damage = 敵や雷トラップから受ける基準ダメージ量
	// 出力：なし
	// 副作用：バリア耐久力の減算、または無敵時間中でなければHPからダメージを引き、死亡時はOnDeathをトリガー
	virtual void TakeDamage(int damage) override;
	void OnDeath();

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