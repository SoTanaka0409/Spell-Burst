#pragma once
#include "Projectile.h"

class CapsuleCollider;

/// @brief 敵が発射する弾を管理するクラス
class EnemyBullet : public Projectile
{
private:
    bool can_reflect_;       ///< バリアで反射できる弾かを示すフラグ
    bool has_reflected_;     ///< 既に反射済みかを示すフラグ
    bool is_stun_bullet_;    ///< プレイヤーをスタンさせる弾かを示すフラグ
    int homing_timer_;       ///< 追尾する残りフレーム数
    int homing_delay_timer_; ///< 追尾開始までの遅延フレーム数

public:
    /// @brief 敵弾を生成する
    /// @param pos 初期座標
    /// @param dir 進行方向
    /// @param speed 速度
    /// @param canReflect 反射可能か
    /// @param isStunBullet スタン弾か
    /// @param homingFrames 追尾時間
    /// @param homingDelayFrames 追尾開始遅延
    EnemyBullet(Vector2 pos, Vector2 dir, float speed, bool canReflect = false, bool isStunBullet = false, int homingFrames = 0, int homingDelayFrames = 0);

    /// @brief 敵弾を破棄する
    virtual ~EnemyBullet() override;

    /// @brief 弾の座標や追尾、反射・削除判定を更新する
    void Update() override;

    /// @brief 弾の画像やエフェクトを描画する
    void Draw() override;

    /// @brief プレイヤーやバリアとの衝突時の処理を行う
    /// @param collider 自身のコライダー
    /// @param check 接触相手のコライダー
    virtual void OnTrigger(Collider* collider, Collider* check) override;
};