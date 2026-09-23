#pragma once
#include "Vector2.h"

/// @brief 敵弾の生成パターンをまとめたファクトリクラス
class BulletFactory
{
public:
    /// @brief 指定した位置から全方位に円形に弾を発射する
    /// @param position 発射位置
    /// @param baseAngle 基準角度
    /// @param count 発射数
    /// @param speed 弾の速度
    /// @param canReflect 反射可能か
    /// @param isStun スタン弾か
    /// @param homingFrames 追尾フレーム数
    /// @param homingDelay 追尾開始遅延
    static void SpawnCircleBullets(Vector2 position, float baseAngle, int count, float speed, bool canReflect = false, bool isStun = false, int homingFrames = 0, int homingDelay = 0);

    /// @brief 指定した位置から扇状に弾を発射する
    /// @param position 発射位置
    /// @param baseAngle 基準角度
    /// @param count 発射数
    /// @param spreadAngle 両端の広がり角度
    /// @param speed 弾の速度
    /// @param canReflect 反射可能か
    /// @param isStun スタン弾か
    /// @param homingFrames 追尾フレーム数
    /// @param homingDelay 追尾開始遅延
    static void SpawnNWayBullets(Vector2 position, float baseAngle, int count, float spreadAngle, float speed, bool canReflect = false, bool isStun = false, int homingFrames = 0, int homingDelay = 0);
};