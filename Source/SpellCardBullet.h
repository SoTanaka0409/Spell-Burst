#pragma once
#include "Projectile.h"

class CapsuleCollider;

/// @brief スペルカード発動時に生成される特殊弾
class SpellCardBullet : public Projectile
{
private:
	int life_timer_;  ///< 爆発までの寿命タイマー
	int state_;       ///< 直進・停止・拡散などの状態
	int burst_count_; ///< 拡散弾の残り発射回数
	int burst_timer_; ///< 拡散弾の発射間隔タイマー

	/// @brief 弾を爆発させ、拡散弾を生成する
	void Explode();

public:
	/// @brief スペルカード弾を生成する
	/// @param x 初期X座標
	/// @param y 初期Y座標
	SpellCardBullet(float x, float y);

	/// @brief スペルカード弾を破棄する
	virtual ~SpellCardBullet() override;

	/// @brief スペルカード弾の状態を更新する
	virtual void Update() override;

	/// @brief スペルカード弾を描画する
	virtual void Draw() override;

	/// @brief 他コライダーとの接触処理を行う
	/// @param collider 自身のコライダー
	/// @param check 接触相手のコライダー
	virtual void OnTrigger(Collider* collider, Collider* check) override;
};