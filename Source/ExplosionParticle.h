#pragma once
#include "Object2D.h"

// 設計ルール：敵やオブジェクト破壊時に、メモリ負荷をかけず画面を賑やかに演出するための軽量な2Dドロー系パーティクルクラス
class ExplosionParticle : public Object2D
{
private:
	float vx_;         // 毎フレームのベクトル加算を高速化するため、極座標（角度・速度）から事前分解したX軸方向の増分
	float vy_;         // 毎フレームのベクトル加算を高速化するため、極座標（角度・速度）から事前分解したY軸方向の増分
	int life_time_;    // 画面外に出ていないパーティクルを確実に消去（回収）するための生存残フレーム数
	int max_life_;     // アルファ値（透明度）や縮小率の減衰傾斜を正確に計算するための初期最大寿命フレーム数
	int color_;        // DXライブラリの GetColor() で生成された描画色（RGBバッファ）のキャッシュ値
	float size_;       // 爆発の勢いや種類（大爆発・小火花）に応じて初速度と同期させる初期描画半径

public:
	// 入力：x, y=発生座標, speed_=初速度, angle=飛散方向（ラジアン）, color_=描画色, life_time_=生存フレーム数, size_=初期半径
	// 副作用：極座標から直交座標（vx_, vy_）への方向ベクトル変換・格納
	ExplosionParticle(float x, float y, float speed_, float angle, int color_, int life_time_, float size_);
	virtual ~ExplosionParticle();

	// 入力：なし
	// 出力：なし
	// 副作用：位置座標の更新、寿命タイマーの減算、および寿命尽き（ゼロ以下）時の消去要求フラグ（is_active_）の書き換え
	virtual void Update() override;

	// 入力：なし
	// 出力：なし
	// 副作用：寿命の減少度合いに応じたサイズ縮小、および不透明度を徐々に下げるフェードアウト描画の実行
	virtual void Draw() override;
};