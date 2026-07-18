#pragma once
#include "Vector2.h"

class BulletFactory
{
public:
    /*
     * 指定した位置から全方位に円形に弾を発射する。
     * [入力] position: 発射位置, baseAngle: 基準角度, count: 発射数, speed: 弾の速度, canReflect: 反射可能か, isStun: スタン弾か, homingFrames: 追尾フレーム数, homingDelay: 追尾開始遅延
     * [出力] なし
     * [副作用] ObjectManager経由で複数のEnemyBulletが生成される
     */
    static void SpawnCircleBullets(Vector2 position, float baseAngle, int count, float speed, bool canReflect = false, bool isStun = false, int homingFrames = 0, int homingDelay = 0);

    /*
     * 指定した位置から扇状（N-Way）に弾を発射する。
     * [入力] position: 発射位置, baseAngle: 基準角度, count: 発射数, spreadAngle: 両端の広がり角度, speed: 弾の速度, canReflect: 反射可能か, isStun: スタン弾か, homingFrames: 追尾フレーム数, homingDelay: 追尾開始遅延
     * [出力] なし
     * [副作用] ObjectManager経由で複数のEnemyBulletが生成される
     */
    static void SpawnNWayBullets(Vector2 position, float baseAngle, int count, float spreadAngle, float speed, bool canReflect = false, bool isStun = false, int homingFrames = 0, int homingDelay = 0);
};
