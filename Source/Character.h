#pragma once
#include "Object2D.h"
#include "Vector2.h"

class CapsuleCollider;
class Collider;

/// @brief 全てのキャラクター（プレイヤー、敵、ボス）の基底クラス
class Character : public Object2D
{
protected:
	int hp_;                     ///< 現在のHP
	int max_hp_;                 ///< 最大HP
	float speed_;                ///< 移動速度
	bool is_active_;             ///< 更新・描画対象として生存しているかを示すフラグ
	int stun_timer_;             ///< 行動不能の残りフレーム数
	CapsuleCollider* collider_;  ///< キャラクター共通の当たり判定

public:
	/// @brief キャラクターを初期化する
	/// @param pos 初期座標
	/// @param maxHp 最大HP
	/// @param speed 移動速度
	Character(Vector2 pos, int maxHp, float speed);

	/// @brief キャラクターを破棄する
	virtual ~Character() override;

	/// @brief キャラクターの状態を毎フレーム更新する
	virtual void Update() override;

	/// @brief キャラクターを描画する
	virtual void Draw() override;

	/// @brief 他コライダーとの接触中処理を行う
	/// @param collider 自身のコライダー
	/// @param check 接触相手のコライダー
	virtual void OnTrigger(Collider* collider, Collider* check) override;

	/// @brief 現在HPを取得する
	/// @return int 現在HP
	int GetHp() const { return hp_; }

	/// @brief 最大HPを取得する
	/// @return int 最大HP
	int GetMaxHp() const { return max_hp_; }

	/// @brief 移動速度を取得する
	/// @return float 移動速度
	float GetSpeed() const { return speed_; }

	/// @brief 生存状態を取得する
	/// @return bool 有効なキャラクターならtrue
	bool IsActive() const { return is_active_; }

	/// @brief スタン状態かを取得する
	/// @return bool スタン中ならtrue
	bool IsStunned() const { return stun_timer_ > 0; }

	/// @brief スタン残り時間を取得する
	/// @return int スタン残りフレーム数
	int GetStunTimer() const { return stun_timer_; }

	/// @brief X座標を取得する
	/// @return float X座標
	float GetX() const { return position_.x; }

	/// @brief Y座標を取得する
	/// @return float Y座標
	float GetY() const { return position_.y; }

	/// @brief 現在HPを設定する
	/// @param hp 設定するHP
	void SetHp(int hp) { hp_ = hp; }

	/// @brief 最大HPを設定する
	/// @param maxHp 設定する最大HP
	void SetMaxHp(int maxHp) { max_hp_ = maxHp; }

	/// @brief 移動速度を設定する
	/// @param speed 設定する移動速度
	void SetSpeed(float speed) { speed_ = speed; }

	/// @brief 指定フレーム数だけスタンさせる
	/// @param frames スタンさせるフレーム数
	void Stun(int frames) { stun_timer_ = frames; }

	/// @brief HPを回復する
	/// @param amount 回復量
	/// @details HPは最大HPを超えないように制限される。
	virtual void Heal(int amount);

	/// @brief ダメージを受ける
	/// @param damage 受けるダメージ量
	/// @details HPが0以下になった場合は死亡処理を呼び出す。
	virtual void TakeDamage(int damage);

	/// @brief キャラクターを死亡状態にする
	/// @details 削除フラグを立て、以後の更新・描画対象から外す。
	virtual void Kill();

	/// @brief 死亡時の追加処理を行う
	virtual void OnDeath();
};