#pragma once
#include "Object2D.h"

/// @brief 敵撃破時などに表示する爆発パーティクル
class ExplosionParticle : public Object2D
{
private:
	float vx_;       ///< X方向の速度
	float vy_;       ///< Y方向の速度
	int life_time_;  ///< 残り寿命フレーム数
	int max_life_;   ///< 初期寿命フレーム数
	int color_;      ///< 描画色
	float size_;     ///< 描画サイズ

public:
	/// @brief 爆発パーティクルを生成する
	/// @param x 初期X座標
	/// @param y 初期Y座標
	/// @param speed_ 速度
	/// @param angle 飛散角度
	/// @param color_ 描画色
	/// @param life_time_ 寿命フレーム数
	/// @param size_ 描画サイズ
	ExplosionParticle(float x, float y, float speed_, float angle, int color_, int life_time_, float size_);

	/// @brief 爆発パーティクルを破棄する
	virtual ~ExplosionParticle();

	/// @brief パーティクルの位置と寿命を更新する
	virtual void Update() override;

	/// @brief パーティクルを描画する
	virtual void Draw() override;
};