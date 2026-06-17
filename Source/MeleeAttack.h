#pragma once
#include "Object2D.h"

class CapsuleCollider;

// プレイヤーによる近接攻撃判定（斬撃など）を管理するクラス
class MeleeAttack : public Object2D {
private:
    int m_lifetime; 
    int m_damage;   
    CapsuleCollider* mpCollider;

public:
    MeleeAttack(float x, float y);
    virtual ~MeleeAttack() override;

    // [入力] なし
    // [出力] なし
    // [副作用] 寿命タイマーを更新し、一定時間経過後に自身を破棄(Kill)する
    virtual void Update() override;

    // [入力] なし
    // [出力] なし
    // [副作用] 攻撃範囲を示す斬撃エフェクトを描画する
    virtual void Draw() override;

    int GetDamage() const { return m_damage; }
    void Kill();

    // [入力] collider: 自身のコライダー, check: 相手のコライダー
    // [出力] なし
    // [副作用] 衝突相手が敵キャラクターの場合、ダメージを与える
    virtual void OnTrigger(Collider* collider, Collider* check) override;
};