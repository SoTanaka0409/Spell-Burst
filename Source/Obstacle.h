#pragma once
#include "Object2D.h"

class CapsuleCollider;

/// @brief 画面上部から落下する障害物クラス
class Obstacle : public Object2D
{
private:
    CapsuleCollider* collider_; ///< 障害物の当たり判定
    float fall_speed_;          ///< 落下速度

public:
    /// @brief 障害物を生成する
    /// @param x 初期X座標
    /// @param y 初期Y座標
    Obstacle(float x, float y);

    /// @brief 障害物を破棄する
    virtual ~Obstacle() override;

    /// @brief 障害物の落下と削除判定を更新する
    virtual void Update() override;

    /// @brief 障害物を描画する
    virtual void Draw() override;

    /// @brief 他コライダーとの接触中処理を行う
    /// @param collider 自身のコライダー
    /// @param check 接触相手のコライダー
    virtual void OnTrigger(Collider* collider, Collider* check) override;

    /// @brief 他コライダーとの接触開始処理を行う
    /// @param collider 自身のコライダー
    /// @param check 接触相手のコライダー
    virtual void OnEnter(Collider* collider, Collider* check) override;
};