#pragma once
#include "Projectile.h"

class CapsuleCollider;

/// @brief プレイヤーの特殊攻撃弾クラス
class SpecialBullet : public Projectile
{
public:
    /// @brief 特殊弾を生成する
    /// @param x 初期X座標
    /// @param y 初期Y座標
    SpecialBullet(float x, float y);

    /// @brief 特殊弾を破棄する
    virtual ~SpecialBullet() override;

    /// @brief 特殊弾を更新する
    virtual void Update() override;

    /// @brief 特殊弾を描画する
    virtual void Draw() override;

    /// @brief 特殊弾を削除対象にする
    virtual void Kill() override;

    /// @brief 他コライダーとの接触処理を行う
    /// @param collider 自身のコライダー
    /// @param check 接触相手のコライダー
    virtual void OnTrigger(Collider* collider, Collider* check) override;
};