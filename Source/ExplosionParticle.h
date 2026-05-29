#pragma once
#include "Object2D.h"

// 爆発エフェクトの破片（パーティクル）クラス
// 敵の撃破時などに生成され、指定された方向に飛散したのち寿命(LifeTime)で消滅する
class ExplosionParticle : public Object2D {
private:
    float m_vx;         // X方向の移動速度ベクトル
    float m_vy;         // Y方向の移動速度ベクトル
    int m_lifeTime;     // パーティクルの現在の残り寿命（フレーム数）
    int m_maxLife;      // パーティクルの最大寿命（初期値）
    int m_color;        // パーティクルの色（DxLibのカラーコードなど）
    float m_size;       // パーティクルの描画サイズ（半径など）

public:
    // [入力] x, y: 発生座標, speed: 飛散速度, angle: 飛散する角度(ラジアン等), color: 描画色, lifeTime: 消滅までのフレーム数, size: パーティクルの大きさ
    // [出力] なし
    // [副作用] 角度と速度からXYの移動ベクトル(m_vx, m_vy)を計算し、各種パラメータを初期化する
    ExplosionParticle(float x, float y, float speed, float angle, int color, int lifeTime, float size);
    virtual ~ExplosionParticle();

    // [入力] なし
    // [出力] なし
    // [副作用] 速度ベクトルに基づき座標を更新し、寿命(m_lifeTime)を減らす。寿命が尽きたら削除フラグを立てる
    virtual void Update() override;

    // [入力] なし
    // [出力] なし
    // [副作用] 残り寿命に応じてサイズを縮小させる、または透明度を下げるなどの計算を行い、パーティクルを描画する
    virtual void Draw() override;
};