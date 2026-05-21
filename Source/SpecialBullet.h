#pragma once
#include "Object2D.h"

class CapsuleCollider;

// プレイヤーの必殺技（貫通弾や強力な攻撃）を管理するクラス
class SpecialBullet : public Object2D {
private:
    float m_x, m_y;     // 必殺技弾の座標
    float m_speed;      // 弾の移動速度
    int m_damage;       // 与えるダメージ量
    bool m_isActive;    // 弾が有効かどうか
    CapsuleCollider* mpCollider;

public:
    SpecialBullet(float x, float y);
    virtual ~SpecialBullet() override;

    virtual void Update() override;
    virtual void Draw() override;

    int GetDamage() const { return m_damage; }
    void Kill();

    virtual void OnTrigger(Collider* collider, Collider* check) override;
};
