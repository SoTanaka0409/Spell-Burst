#pragma once
#include "Projectile.h"

// プレイヤーが発射する通常の弾を管理するクラス
class Bullet : public Projectile
{
public:
    Bullet(float x, float y, int damage_);
    virtual ~Bullet() override;
    
    void Draw() override;
    void Update() override;

    // Collision helper
    float GetX() { return position_.x; }
    float GetY() { return position_.y; }
    float GetRadius() const { return 10.0f; }

	void AddReceivedDamage() { recivedDamage++; }

    virtual void OnTrigger(Collider* collider_, Collider* check) override;

private:
	int recivedDamage;    // ダメージを受けた回数  
	int maxrecivedDamage; // この弾が与えられる最大ダメージ上限（貫通制限）
};