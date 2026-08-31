#include "ExplosionParticle.h"
#include "ObjectManager.h"
#include "Utility.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include <cmath>

/// @brief ExplosionParticle を生成する
/// @param x x の値
/// @param y y の値
/// @param speed_ speed_ の値
/// @param angle angle の値
/// @param color_ color_ の値
/// @param life_time_ life_time_ の値
/// @param size_ size_ の値
ExplosionParticle::ExplosionParticle(float x, float y, float speed_, float angle, int color_, int life_time_, float size_)
	: Object2D(Vector2(x, y))
{
	vx_ = std::cos(angle) * speed_;
	vy_ = std::sin(angle) * speed_;
	this->life_time_ = life_time_;
	this->max_life_ = life_time_;
	this->color_ = color_;
	this->size_ = size_;
}

/// @brief 破棄処理を行う
ExplosionParticle::~ExplosionParticle()
{
}

/// @brief 毎フレームの更新処理を行う
void ExplosionParticle::Update()
{
	position_.x += vx_ * Utility::time_scale_;
	position_.y += vy_ * Utility::time_scale_;

	vx_ *= 0.95f;
	vy_ *= 0.95f;

	life_time_--;
	if (life_time_ <= 0)
	{
		SetDeleteFlag(true);
	}
}

/// @brief 描画処理を行う
void ExplosionParticle::Draw()
{
	int alpha = static_cast<int>(255.0f * (static_cast<float>(life_time_) / max_life_));
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	float currentSize = size_ * (static_cast<float>(life_time_) / max_life_) + 1.0f;

	DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), static_cast<int>(currentSize), color_, TRUE);
	DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), static_cast<int>(currentSize * 0.5f), GetColor(255, 255, 255), TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
