#pragma once
#include "Object2D.h"

class CapsuleCollider;

// 敵キャラクター（雑魚やボス）が発射する弾を管理するクラス
class EnemyBullet : public Object2D {
private:
    float m_x, m_y;     // 弾の座標
    float m_dx, m_dy;   // 移動方向のベクトル
    float m_speed;      // 弾の移動速度
    bool m_isActive;    // 弾が有効かどうか
    CapsuleCollider* mpCollider;

    bool m_canReflect;
    bool m_hasReflected;
    bool m_isStunBullet; // スタン効果を持つ弾かどうか

public:
    EnemyBullet(float x, float y, float dx, float dy, float speed, bool canReflect = false, bool isStunBullet = false);
    virtual ~EnemyBullet() override;

    void Update() override;
    void Draw() override;

    virtual void OnTrigger(Collider* collider, Collider* check) override;
};
