#pragma once
#include "Projectile.h"

class CapsuleCollider;

// スペルカード発動時に生成される特殊弾
class SpellCardBullet : public Projectile
{
private:
	int life_timer_;  // 爆発までの寿命タイマー
	int state_;       // 直進・停止・拡散などの状態
	int burst_count_; // 拡散弾の残り発射回数
	int burst_timer_; // 拡散弾の発射間隔タイマー

	void Explode();

public:
	SpellCardBullet(float x, float y);
	virtual ~SpellCardBullet() override;

	virtual void Update() override;

	virtual void Draw() override;

	virtual void OnTrigger(Collider* collider, Collider* check) override;
};