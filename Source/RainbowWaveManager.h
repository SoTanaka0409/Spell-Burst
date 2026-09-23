#pragma once
#include "Object2D.h"

/// @brief 虹色の波状弾を一定時間生成する管理オブジェクト
class RainbowWaveManager : public Object2D
{
private:
    int life_timer_;     ///< 残り寿命フレーム数
    int spawn_interval_; ///< 弾を生成する間隔
    int spawn_timer_;    ///< 次の生成までのタイマー

public:
    /// @brief 虹色弾生成マネージャを生成する
    /// @param x 初期X座標
    /// @param y 初期Y座標
    RainbowWaveManager(float x, float y);

    /// @brief 虹色弾生成マネージャを破棄する
    virtual ~RainbowWaveManager() override;

    /// @brief 寿命と弾生成を更新する
    virtual void Update() override;

    /// @brief 管理オブジェクトの描画処理を行う
    virtual void Draw() override;

    /// @brief 他コライダーとの接触処理を行う
    /// @param collider 自身のコライダー
    /// @param check 接触相手のコライダー
    virtual void OnTrigger(Collider* collider, Collider* check) override;
};