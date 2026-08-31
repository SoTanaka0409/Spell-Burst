#pragma once
#include "Projectile.h"

class CapsuleCollider;

/// @brief 敵を追尾するプレイヤー弾クラス
class PlayerHomingBullet : public Projectile
{
private:
    int life_timer_; ///< 残り寿命フレーム数

public:
    /// @brief 追尾弾を生成する
    /// @param pos 初期座標
    /// @param dir 初期進行方向
    /// @param speed 速度
    PlayerHomingBullet(Vector2 pos, Vector2 dir, float speed);

    /// @brief 追尾弾を破棄する
    virtual ~PlayerHomingBullet() override;

    /// @brief 追尾方向と寿命を更新する
    virtual void Update() override;

    /// @brief 追尾弾を描画する
    virtual void Draw() override;

    /// @brief 他コライダーとの接触処理を行う
    /// @param collider 自身のコライダー
    /// @param check 接触相手のコライダー
    virtual void OnTrigger(Collider* collider, Collider* check) override;
};