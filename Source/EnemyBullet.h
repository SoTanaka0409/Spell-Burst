#pragma once
#include "Projectile.h"

class CapsuleCollider;

class EnemyBullet : public Projectile
{
private:
    bool can_reflect_; // 画面端で反射する仕様の弾かどうか
    bool has_reflected_; // すでに反射を一度行ったかどうかのフラグ
    bool is_stun_bullet_; // 当たった相手を行動不能（スタン）にする状態異常弾かどうか
    int homing_timer_;   // ホーミング（追尾）処理が有効な残りフレーム数
    int homing_delay_timer_; // 発射後、ホーミングを開始するまでの遅延タイマー

public:
    /*
     * 敵弾を初期化する。直進・反射・スタン・ホーミングなど多様な属性をサポートする。
     * [入力] pos: 初期座標, dir: 進行方向, speed: 速度, canReflect: 反射弾か, isStun: スタン弾か, homingFrames: 追尾フレーム数, homingDelayFrames: 追尾開始遅延
     * [出力] なし
     * [副作用] コライダーが生成される
     */
    EnemyBullet(Vector2 pos, Vector2 dir, float speed, bool canReflect = false, bool isStunBullet = false, int homingFrames = 0, int homingDelayFrames = 0);
    virtual ~EnemyBullet() override;

    /*
     * 弾の座標を更新し、追尾処理や画面端での反射・消滅判定を行う。
     * [入力] なし
     * [出力] なし
     * [副作用] 座標が更新され、必要に応じて弾が消滅する
     */
    void Update() override;

    /*
     * 弾の画像やエフェクトを描画する。
     * [入力] なし
     * [出力] なし
     * [副作用] 画面に描画される
     */
    void Draw() override;

    /*
     * プレイヤーやバリアとの衝突時にダメージ付与や弾消し処理を行う。
     * [入力] collider: 自身のコライダー, check: 相手のコライダー
     * [出力] なし
     * [副作用] 相手にダメージが入り、弾が削除される
     */
    virtual void OnTrigger(Collider* collider, Collider* check) override;
};
