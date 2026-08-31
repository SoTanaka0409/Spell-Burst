#pragma once
#include "Projectile.h"

class CapsuleCollider;

/// @brief 虹色に変化しながら進むプレイヤー弾クラス
class RainbowBullet : public Projectile
{
private:
    int color_hue_; ///< 描画色の色相

public:
    /// @brief 虹色弾を生成する
    /// @param x 初期X座標
    /// @param y 初期Y座標
    RainbowBullet(float x, float y);

    /// @brief 虹色弾を破棄する
    virtual ~RainbowBullet() override;

    /// @brief 弾の移動と色相を更新する
    virtual void Update() override;

    /// @brief 虹色弾を描画する
    virtual void Draw() override;

    /// @brief 他コライダーとの接触処理を行う
    /// @param collider 自身のコライダー
    /// @param check 接触相手のコライダー
    virtual void OnTrigger(Collider* collider, Collider* check) override;
};