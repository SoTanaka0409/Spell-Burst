#pragma once
#include "Vector2.h"

class EffectManager
{
public:
    /*
     * 指定した位置に爆発パーティクルを複数生成する。
     * [入力] position: 爆発の中心位置, count: 生成するパーティクルの数, color: パーティクルの色(DXLibのColor), size: 最大サイズ, speed: 最大速度
     * [出力] なし
     * [副作用] ObjectManager経由で複数のExplosionParticleが生成される
     */
    static void SpawnExplosion(Vector2 position, int count, int color, float size, float speed);
};
