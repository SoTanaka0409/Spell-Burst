#pragma once
#include "Vector2.h"

/// @brief 爆発などの演出オブジェクト生成をまとめるクラス
class EffectManager
{
public:
    /// @brief 指定した位置に爆発パーティクルを複数生成する
    /// @param position 爆発の中心位置
    /// @param count 生成するパーティクル数
    /// @param color パーティクルの色
    /// @param size 最大サイズ
    /// @param speed 最大速度
    static void SpawnExplosion(Vector2 position, int count, int color, float size, float speed);
};