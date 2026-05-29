#pragma once
#include "Object2D.h"

class CapsuleCollider;

// 虹色の特殊弾クラス
// プレイヤーまたは敵が発射する、色が変化する（または虹色で描画される）特殊な弾
class RainbowBullet : public Object2D {
private:
    CapsuleCollider* mpCollider;    // 当たり判定（カプセル型コライダー）のポインタ
    float m_speed;                  // 弾の移動速度
    int m_damage;                   // 命中した対象（敵または自機）に与えるダメージ量
    int m_colorHue;                 // 弾の描画に使用する色相（毎フレーム変化させて虹色を表現するための変数）

public:
    // [入力] x, y: 弾の発射初期座標
    // [出力] なし
    // [副作用] 速度、ダメージ量、初期の色相などのパラメータを設定し、コライダーを生成する
    RainbowBullet(float x, float y);
    virtual ~RainbowBullet() override;

    // [入力] なし
    // [出力] なし
    // [副作用] 弾を直進（または特定の軌道で移動）させ、m_colorHueを更新して色を変化させる。画面外判定も行う
    virtual void Update() override;

    // [入力] なし
    // [出力] なし
    // [副作用] 現在の m_colorHue を用いて、弾の画像を描画する
    virtual void Draw() override;

    // [入力] collider: 自機のコライダー, check: 衝突相手のコライダー
    // [出力] なし
    // [副作用] 衝突相手が敵（または敵の弾）の場合、ダメージ処理を行い自身を消去する
    virtual void OnTrigger(Collider* collider, Collider* check) override;
};