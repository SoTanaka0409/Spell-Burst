#pragma once
#include "Projectile.h"

class CapsuleCollider;

// 敵が発射する弾を管理するクラス
class EnemyBullet : public Projectile
{
private:
    bool can_reflect_;       // バリアで反射できる弾か
    bool has_reflected_;     // 既に反射済みか
    bool is_stun_bullet_;    // プレイヤーをスタンさせる弾か
    int homing_timer_;       // 追尾する残りフレーム数
    int homing_delay_timer_; // 追尾開始までの遅延フレーム数

public:
    /*
     * 敵弾を生成する。直進・反射・スタン・追尾などの種類を指定できる。
     * [入力] pos: 初期座標, dir: 進行方向, speed: 速度, canReflect: 反射可能か, isStunBullet: スタン弾か, homingFrames: 追尾時間, homingDelayFrames: 追尾開始遅延
     * [出力] なし
     * [副作用] コライダーが生成される
     */
    EnemyBullet(Vector2 pos, Vector2 dir, float speed, bool canReflect = false, bool isStunBullet = false, int homingFrames = 0, int homingDelayFrames = 0);
    virtual ~EnemyBullet() override;

    /*
     * 弾の座標や追尾、画面端での反射・削除判定を更新する。
     * [入力] なし
     * [出力] なし
     * [副作用] 座標や削除フラグが変化する
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
     * プレイヤーやバリアとの衝突時の処理を行う。
     * [入力] collider: 自身のコライダー, check: 相手のコライダー
     * [出力] なし
     * [副作用] ダメージ、反射、削除などを行う
     */
    virtual void OnTrigger(Collider* collider, Collider* check) override;
};