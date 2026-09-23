#pragma once
#include "Object2D.h"

class CapsuleCollider;

/// @brief プレイヤーのスペルカード演出で使う攻撃パーティクル
class PlayerSpellParticle : public Object2D
{
private:
	Vector2 dir;                 ///< 進行方向
	float speed_;                ///< 速度
	int damage_;                 ///< ダメージ量
	bool is_active_;             ///< 有効状態を示すフラグ
	int life_timer_;             ///< 残り寿命フレーム数
	CapsuleCollider* collider_;  ///< 当たり判定

public:
	/// @brief スペルパーティクルを生成する
	/// @param pos 初期座標
	/// @param dir 進行方向
	/// @param speed_ 速度
	PlayerSpellParticle(Vector2 pos, Vector2 dir, float speed_);

	/// @brief スペルパーティクルを破棄する
	virtual ~PlayerSpellParticle() override;

	/// @brief スペルパーティクルを更新する
	virtual void Update() override;

	/// @brief スペルパーティクルを描画する
	virtual void Draw() override;

	/// @brief 他コライダーとの接触処理を行う
	/// @param collider 自身のコライダー
	/// @param check 接触相手のコライダー
	virtual void OnTrigger(Collider* collider, Collider* check) override;

	/// @brief スペルパーティクルを削除対象にする
	void Kill();
};