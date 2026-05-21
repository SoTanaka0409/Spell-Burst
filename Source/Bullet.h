#pragma once
#include "Object2D.h"

class CapsuleCollider;

// プレイヤーが発射する通常の弾を管理するクラス
class Bullet : public Object2D
{
public:
    Bullet(float x, float y,float damage);
    virtual ~Bullet() override;
    void Draw() override;
    void Update() override;
    bool IsActive() { return m_isActive; }

    // Collision helper
    float GetX() { return m_x; }
    float GetY() { return m_y; }
    float GetRadius() const { return 10.0f; }
    int GetDamage() const { return m_damage; }
    void Kill();

    virtual void OnTrigger(Collider* collider, Collider* check) override;

private:
    float m_x, m_y;       // 弾の座標
    float m_speed;        // 弾の移動速度
    bool m_isActive;      // 弾が有効かどうか
    int m_damage;         // 弾が与えるダメージ量
    CapsuleCollider* mpCollider;
};
