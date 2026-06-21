#pragma once
#include "Projectile.h"

// プレイヤーが発射する通常の弾を管理するクラス
class Bullet : public Projectile
{
public:
    Bullet(float x, float y, int damage);
    virtual ~Bullet() override;
    
    void Draw() override;
    void Update() override;

    // Collision helper
    float GetX() { return mvPosition.x; }
    float GetY() { return mvPosition.y; }
    float GetRadius() const { return 10.0f; }

	void AddReceivedDamage() { m_recivedDamage++; }

    virtual void OnTrigger(Collider* collider, Collider* check) override;

private:
	int m_recivedDamage;    // ダメージを受けた回数  
	int m_MaxrecivedDamage; // この弾が与えられる最大ダメージ上限（貫通制限）
};