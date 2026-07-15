#pragma once
#include "Projectile.h"

class CapsuleCollider;

// 敵キャラクター（雑魚およびボス）が発射する弾クラス
// 直進だけでなく、反射やプレイヤーへのホーミング（追尾）などの特殊軌道もサポートする
class EnemyBullet : public Projectile
{
private:
    bool can_reflect_; // 画面端で反射する仕様の弾かどうか
    bool has_reflected_; // すでに反射を一度行ったかどうかのフラグ
    bool is_stun_bullet_; // 当たった相手を行動不能（スタン）にする状態異常弾かどうか
    int homing_timer_;   // ホーミング（追尾）処理が有効な残りフレーム数
    int homing_delay_timer_; // 発射後、ホーミングを開始するまでの遅延タイマー

public:
    EnemyBullet(Vector2 pos, Vector2 dir, float speed_, bool can_reflect_ = false, bool is_stun_bullet_ = false, int homingFrames = 0, int homingDelayFrames = 0);
    virtual ~EnemyBullet() override;

    // [入力] なし
    // [出力] なし
    // [副作用] 弾の座標を更新し、追尾処理や画面端bでの反射・消滅判定を行う
    void Update() override;

    // [入力] なし
    // [出力] なし
    // [副作用] 弾の画像やエフェクト（属性に応じた色など）を描画する
    void Draw() override;

    // [入力] collider_: 自身のコライダー, check: 相手のコライダー
    // [出力] なし
    // [副作用] プレイヤーやバリアとの衝突時にダメージ付与や弾消し処理を行う
    virtual void OnTrigger(Collider* collider_, Collider* check) override;
};
