#pragma once
#include "Object2D.h"

class CapsuleCollider;

/// @brief プレイヤーの近接攻撃判定と演出を管理するクラス
class MeleeAttack : public Object2D
{
private:
    int life_time_;             ///< 残り寿命フレーム数
    int damage_;                ///< ダメージ量
    CapsuleCollider* collider_; ///< 攻撃範囲の当たり判定

public:
    /// @brief 近接攻撃を生成する
    /// @param x 初期X座標
    /// @param y 初期Y座標
    MeleeAttack(float x, float y);

    /// @brief 近接攻撃を破棄する
    virtual ~MeleeAttack() override;

    /// @brief 寿命を更新し、時間切れになったら削除する
    virtual void Update() override;

    /// @brief 近接攻撃のエフェクトを描画する
    virtual void Draw() override;

    /// @brief ダメージ量を取得する
    /// @return int ダメージ量
    int GetDamage() const { return damage_; }

    /// @brief 近接攻撃を削除対象にする
    void Kill();

    /// @brief 攻撃判定が敵と接触したときにダメージを与える
    /// @param collider 自身のコライダー
    /// @param check 接触相手のコライダー
    virtual void OnTrigger(Collider* collider, Collider* check) override;
};