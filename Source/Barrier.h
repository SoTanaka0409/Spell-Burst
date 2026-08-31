#pragma once
#include "Object2D.h"

class Collider;

/// @brief 一定周期で展開され、敵弾を防ぐバリアクラス
class Barrier : public Object2D
{
public:
	/// @brief バリアを生成する
	/// @param x 初期X座標
	/// @param y 初期Y座標
	/// @param radius バリア半径
	/// @param obj 所有者を表すタグ
	Barrier(float x, float y, float radius, Object2D::Tag2D obj);

	/// @brief バリアを破棄する
	virtual ~Barrier();

	/// @brief 展開タイマーとコライダー状態を更新する
	virtual void Update() override;

	/// @brief 展開中のバリアエフェクトを描画する
	virtual void Draw() override;

	/// @brief 弾との接触処理を行う
	/// @param collider 自身のコライダー
	/// @param check 接触相手のコライダー
	virtual void OnTrigger(Collider* collider, Collider* check) override;

	/// @brief 被弾回数を取得する
	/// @return int 被弾回数
	int GetHitCount() const { return hit_count_; }

	/// @brief バリアが展開中かを取得する
	/// @return bool 展開中ならtrue
	bool IsDeployed() const { return is_deployed_; }

	/// @brief 再展開までの間隔を設定する
	/// @param v 展開間隔
	void SetDeployInterval(float v) { deploy_interval_ = v; }

	/// @brief 展開している時間を設定する
	/// @param v 展開時間
	void SetActiveDuration(float v) { active_duration_ = v; }

	/// @brief バリアの座標を設定する
	/// @param pos 設定する座標
	void SetPosition(Vector2 pos) { position_ = pos; }

private:
	float deploy_interval_;  ///< 再展開までの待機時間
	float active_duration_;  ///< 展開を維持する時間
	float timer_;            ///< 展開周期を管理するタイマー
	float radius_;           ///< バリアの半径
	bool is_deployed_;       ///< 現在バリアが展開中かを示すフラグ
	Collider* collider_;     ///< バリアの当たり判定
	int hit_count_;          ///< バリアが弾を受けた回数
};