#pragma once
#include "Object2D.h"

class CapsuleCollider;

// プレイヤーが発射する通常の弾を管理するクラス
class Bullet : public Object2D
{
public:
    Bullet(float x, float y, int damage);
    virtual ~Bullet() override;
    void Draw() override;
    void Update() override;
    bool IsActive() { return m_isActive; }

    // Collision helper
    float GetX() { return mvPosition.x; }
    float GetY() { return mvPosition.y; }
    float GetRadius() const { return 10.0f; }
    int GetDamage() const { return m_damage; }
    void Kill();

	void AddReceivedDamage() { m_recivedDamage++; }

    virtual void OnTrigger(Collider* collider, Collider* check) override;

private:
    float m_speed;          // 弾の進行速度
    bool m_isActive;        // 弾が画面内に存在し有効かどうかのフラグ
    int m_damage;           // 敵に与えるダメージ量
	int m_recivedDamage;    // ダメージを受けた回数  
	int m_MaxrecivedDamage; // この弾が与えられる最大ダメージ上限（貫通制限）
    CapsuleCollider* mpCollider; // 当たり判定用コライダー
};