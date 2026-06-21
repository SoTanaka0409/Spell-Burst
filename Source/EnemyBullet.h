#pragma once
#include "Projectile.h"

class CapsuleCollider;

// 敵キャラクター（雑魚およびボス）が発射する弾クラス
// 直進だけでなく、反射やプレイヤーへのホーミング（追尾）などの特殊軌道もサポートする
class EnemyBullet : public Projectile {
private:
    bool m_canReflect; // 画面端で反射する仕様の弾かどうか
    bool m_hasReflected; // すでに反射を一度行ったかどうかのフラグ
    bool m_isStunBullet; // 当たった相手を行動不能（スタン）にする状態異常弾かどうか
    int m_homingTimer;   // ホーミング（追尾）処理が有効な残りフレーム数
    int m_homingDelayTimer; // 発射後、ホーミングを開始するまでの遅延タイマー

public:
    EnemyBullet(Vector2 pos, Vector2 dir, float speed, bool canReflect = false, bool isStunBullet = false, int homingFrames = 0, int homingDelayFrames = 0);
    virtual ~EnemyBullet() override;

    // [入力] なし
    // [出力] なし
    // [副作用] 弾の座標を更新し、追尾処理や画面端での反射・消滅判定を行う
    void Update() override;

    // [入力] なし
    // [出力] なし
    // [副作用] 弾の画像やエフェクト（属性に応じた色など）を描画する
    void Draw() override;

    // [入力] collider: 自身のコライダー, check: 相手のコライダー
    // [出力] なし
    // [副作用] プレイヤーやバリアとの衝突時にダメージ付与や弾消し処理を行う
    virtual void OnTrigger(Collider* collider, Collider* check) override;
};