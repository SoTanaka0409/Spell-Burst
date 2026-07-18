#pragma once
#include "Object2D.h"

class CapsuleCollider;

// プレイヤーの近接攻撃判定と演出を管理するクラス
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
     * 寿命を更新し、時間切れになったら削除する。
     * [入力] なし
     * [出力] なし
     * [副作用] life_time_を減らし、必要に応じてKillを呼ぶ
     */
    virtual void Update() override;

    /*
     * 近接攻撃のエフェクトを描画する。
     * [入力] なし
     * [出力] なし
     * [副作用] 画面に攻撃範囲が描画される
     */
    virtual void Draw() override;

    int GetDamage() const { return damage_; }
    void Kill();

    /*
     * 攻撃判定が敵と接触したときにダメージを与える。
     * [入力] collider: 自身のコライダー, check: 相手のコライダー
     * [出力] なし
     * [副作用] 敵にダメージを与える
     */
    virtual void OnTrigger(Collider* collider, Collider* check) override;
};