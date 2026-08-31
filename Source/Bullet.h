#pragma once
#include "Projectile.h"

/// @brief プレイヤーが発射する通常弾クラス
class Bullet : public Projectile
{
public:
	/// @brief プレイヤー弾を生成する
	/// @param x 初期X座標
	/// @param y 初期Y座標
	/// @param damage ダメージ量
	Bullet(float x, float y, int damage);

	/// @brief プレイヤー弾を破棄する
	virtual ~Bullet() override;

	/// @brief 弾を描画する
	void Draw() override;

	/// @brief 弾の移動と状態を更新する
	void Update() override;

	/// @brief X座標を取得する
	/// @return float X座標
	float GetX() { return position_.x; }

	/// @brief Y座標を取得する
	/// @return float Y座標
	float GetY() { return position_.y; }

	/// @brief 弾の当たり判定半径を取得する
	/// @return float 当たり判定半径
	float GetRadius() const { return 10.0f; }

	/// @brief このフレームで受けたヒット数を加算する
	void AddReceivedDamage() { received_damage_++; }

	/// @brief 敵や障害物との接触処理を行う
	/// @param collider 自身のコライダー
	/// @param check 接触相手のコライダー
	virtual void OnTrigger(Collider* collider, Collider* check) override;

private:
	int received_damage_;      ///< 同一フレーム内の多重ヒットを抑えるためのカウンター
	int max_received_damage_;  ///< 貫通弾が一度に処理できる最大ヒット数
};