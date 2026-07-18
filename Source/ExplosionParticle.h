#pragma once
#include "Object2D.h"

// 敵撃破時などに表示する爆発パーティクル
class ExplosionParticle : public Object2D
{
private:
	float vx_;         // X方向の速度
	float vy_;         // Y方向の速度
	int life_time_;    // 残り寿命フレーム数
	int max_life_;     // 初期寿命フレーム数
	int color_;        // 描画色
	float size_;       // 描画サイズ

public:
	ExplosionParticle(float x, float y, float speed_, float angle, int color_, int life_time_, float size_);
	virtual ~ExplosionParticle();

	virtual void Update() override;

	virtual void Draw() override;
};