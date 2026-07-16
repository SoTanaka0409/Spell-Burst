#pragma once
#include "Object2D.h"

class CapsuleCollider;

class MeleeAttack : public Object2D
{
private:
    int life_time_; 
    int damage_;   
    CapsuleCollider* collider_;

public:
    MeleeAttack(float x, float y);
    virtual ~MeleeAttack() override;

    /*
     * ライフタイマーを更新し、時間切れになったら削除する。
     * [入力] なし
     * [出力] なし
     * [副作用] life_time_が減少し、0になったらKill()を呼ぶ
     */
    virtual void Update() override;

    /*
     * 近接攻撃の範囲エフェクトを描画する。
     * [入力] なし
     * [出力] なし
     * [副作用] 画面に描画される
     */
    virtual void Draw() override;

    int GetDamage() const { return damage_; }
    void Kill();

    /*
     * 当たり判定が敵キャラクターと接触した際にダメージを与える。
     * [入力] collider: 自身のコライダー, check: 相手のコライダー
     * [出力] なし
     * [副作用] 敵にダメージが入る
     */
    virtual void OnTrigger(Collider* collider, Collider* check) override;
};
