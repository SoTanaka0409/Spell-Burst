#pragma once
#include "Object2D.h"

class CapsuleCollider;

<<<<<<< HEAD
// 敵キャラクター（雑魚やボス）が発射する弾を管理するクラス
class EnemyBullet : public Object2D {
private:
    float m_x, m_y;     // 弾の座標
    float m_dx, m_dy;   // 移動方向のベクトル
    float m_speed;      // 弾の移動速度
    bool m_isActive;    // 弾が有効かどうか
=======
// 敵キャラクター�E�雑魚やボス�E�が発封E��る弾を管琁E��るクラス
class EnemyBullet : public Object2D {
private:
    float m_dx, m_dy;   // 移動方向�Eベクトル
    float m_speed;      // 弾の移動速度
    bool m_isActive;    // 弾が有効かどぁE��
>>>>>>> main
    CapsuleCollider* mpCollider;

    bool m_canReflect;
    bool m_hasReflected;
<<<<<<< HEAD
    bool m_isStunBullet; // スタン効果を持つ弾かどうか
    int m_homingTimer;   // 追尾（ホーミング）する残りフレーム数
=======
    bool m_isStunBullet; // スタン効果を持つ弾かどぁE��
    int m_homingTimer;   // 追尾�E��Eーミング�E�する残りフレーム数
>>>>>>> main
    int m_homingDelayTimer;

public:
    EnemyBullet(float x, float y, float dx, float dy, float speed, bool canReflect = false, bool isStunBullet = false, int homingFrames = 0, int homingDelayFrames = 0);
    virtual ~EnemyBullet() override;

    void Update() override;
    void Draw() override;

<<<<<<< HEAD
=======
    void Kill();

>>>>>>> main
    virtual void OnTrigger(Collider* collider, Collider* check) override;
};
