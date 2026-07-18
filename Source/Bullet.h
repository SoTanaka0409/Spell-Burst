#pragma once
#include "Projectile.h"

// プレイヤーが発射する通常弾クラス
class Bullet : public Projectile
{
public:
	Bullet(float x, float y, int damage);
	virtual ~Bullet() override;

	void Draw() override;
	void Update() override;

	float GetX() { return position_.x; }
	float GetY() { return position_.y; }

	float GetRadius() const { return 10.0f; }

	void AddReceivedDamage() { received_damage_++; }

	virtual void OnTrigger(Collider* collider, Collider* check) override;

private:
	int received_damage_;     // 同一フレーム内の多重ヒットを抑えるためのカウンター
	int max_received_damage_; // 貫通弾が一度に処理できる最大ヒット数
};