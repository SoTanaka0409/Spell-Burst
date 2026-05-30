#pragma once
#include "Object2D.h"

class CapsuleCollider;

<<<<<<< HEAD
// プレイヤーの近接攻撃（ナイフや剣の振り）を管理するクラス
class MeleeAttack : public Object2D {
private:
    float m_x, m_y; // 攻撃の判定が発生している座標
    int m_lifetime; // 攻撃の持続時間（フレーム数）
    int m_damage;   // 与えるダメージ量
=======
// プレイヤーの近接攻撁E��ナイフや剣の振り）を管琁E��るクラス
class MeleeAttack : public Object2D {
private:
    int m_lifetime; // 攻撁E�E持続時間（フレーム数�E�E
    int m_damage;   // 与えるダメージ釁E
>>>>>>> main
    CapsuleCollider* mpCollider;

public:
    MeleeAttack(float x, float y);
    virtual ~MeleeAttack() override;

    virtual void Update() override;
    virtual void Draw() override;

    int GetDamage() const { return m_damage; }
    void Kill();

    virtual void OnTrigger(Collider* collider, Collider* check) override;
};
