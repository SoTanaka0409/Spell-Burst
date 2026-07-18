#pragma once
#include "Object2D.h"
#include "Vector2.h"

class CapsuleCollider;
class Collider;

// 全てのキャラクター（プレイヤー、敵、ボス）の基底クラス
class Character : public Object2D
{
protected:
	int hp_;                     // 現在のHP
	int max_hp_;                 // 最大HP
	float speed_;                // 移動速度
	bool is_active_;             // 更新・描画対象として生存しているか
	int stun_timer_;             // 行動不能の残りフレーム数
	CapsuleCollider* collider_;  // キャラクター共通の当たり判定

public:
	/*
	 * キャラクターの初期化を行う。
	 * [入力] pos: 初期座標, maxHp: 最大体力, speed: 移動速度
	 * [出力] なし
	 * [副作用] キャラクターのパラメータが設定される
	 */
	Character(Vector2 pos, int maxHp, float speed);
	virtual ~Character() override;

	virtual void Update() override;
	virtual void Draw() override;
	virtual void OnTrigger(Collider* collider, Collider* check) override;

	// --- ゲッター ---
	int GetHp() const { return hp_; }
	int GetMaxHp() const { return max_hp_; }
	float GetSpeed() const { return speed_; }
	bool IsActive() const { return is_active_; }
	bool IsStunned() const { return stun_timer_ > 0; }
	int GetStunTimer() const { return stun_timer_; }
	float GetX() const { return position_.x; }
	float GetY() const { return position_.y; }

	// --- セッター・操作 ---
	void SetHp(int hp) { hp_ = hp; }
	void SetMaxHp(int maxHp) { max_hp_ = maxHp; }
	void SetSpeed(float speed) { speed_ = speed; }
	void Stun(int frames) { stun_timer_ = frames; }

	/*
	 * キャラクターのHPを回復する。
	 * [入力] amount: 回復量
	 * [出力] なし
	 * [副作用] HPを回復し、最大値を超えないように制限する
	 */
	virtual void Heal(int amount);

	/*
	 * キャラクターにダメージを与える。
	 * [入力] damage: 受けるダメージ量
	 * [出力] なし
	 * [副作用] HPを減らし、0以下になったら死亡処理などを呼ぶ
	 */
	virtual void TakeDamage(int damage);

	/*
	 * キャラクターを死亡させる。
	 * [入力] なし
	 * [出力] なし
	 * [副作用] キャラクターを死亡状態にし、削除フラグを立てる
	 */
	virtual void Kill();

	virtual void OnDeath();
};