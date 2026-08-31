#pragma once
#include "Projectile.h"

class CapsuleCollider;

/// @brief プレイヤーの貫通レーザー攻撃を表すクラス
class MasterSpark : public Projectile
{
private:
	int life_timer_;   ///< 残り寿命フレーム数
	int max_life_;     ///< 初期寿命フレーム数
	float radius_;     ///< レーザーの当たり判定半径
	int color_hue_;    ///< 描画色の色相
	int attack_count_; ///< ヒット間隔を調整するカウンター

public:
	/// @brief レーザー攻撃を生成する
	/// @param x 初期X座標
	/// @param y 初期Y座標
	MasterSpark(float x, float y);

	/// @brief レーザー攻撃を破棄する
	virtual ~MasterSpark() override;

private:
	/// @brief レーザー周辺の粒子演出を描画する
	void DrawParticles();

	/// @brief レーザーの寿命と判定を更新する
	virtual void Update() override;

	/// @brief レーザーを描画する
	virtual void Draw() override;

	/// @brief レーザーを削除対象にする
	virtual void Kill() override;

	/// @brief 接触中のダメージ処理を行う
	/// @param collider 自身のコライダー
	/// @param check 接触相手のコライダー
	virtual void OnTrigger(Collider* collider, Collider* check) override;

	/// @brief 接触開始時の処理を行う
	/// @param collider 自身のコライダー
	/// @param check 接触相手のコライダー
	virtual void OnEnter(Collider* collider, Collider* check) override;
};