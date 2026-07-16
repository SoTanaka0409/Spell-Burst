#pragma once
#include <cmath>
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"

// 設計ルール：ゲーム内の2D座標系、弾の進行ベクトル、およびノックバック等の力学計算を高速かつ直感的に記述するための2次元ベクトル構造体
struct Vector2
{
	float x;                         // 2D物理空間上における、左右（水平方向）の絶対座標または移動・速度ベクトル
	float y;                         // 2D物理空間上における、上下（垂直方向）の絶対座標または移動・速度ベクトル

	Vector2();
	Vector2(float x, float y);

	Vector2 operator+(const Vector2& other) const;
	Vector2 operator-(const Vector2& other) const;
	Vector2 operator*(float scalar) const;
	Vector2 operator/(float scalar) const;

	Vector2& operator+=(const Vector2& other);
	Vector2& operator-=(const Vector2& other);
	Vector2& operator*=(float scalar);
	Vector2& operator/=(float scalar);

	// 入力：なし
	// 出力：ベクトルの長さ（スカラー値）
	float Magnitude() const;

	// 入力：なし
	// 出力：ベクトルの二乗の長さ
	// パフォーマンス理由：平方根（sqrt）計算を回避し、距離比較の高速化（雷や弾の衝突判定処理の負荷軽減）に用いる
	float MagnitudeSq() const;

	Vector2 Normalized() const;
	void Normalize();

	float DistanceTo(const Vector2& other) const;

	// 入力：other = 比較対象となる位置ベクトル
	// 出力：自身と対象との二乗距離
	// パフォーマンス理由：sqrt処理をバイパスし、アトラクター（UFO）への生物の吸い寄せ距離判定を毎フレーム数百回高速に行うための計算
	float DistanceSqTo(const Vector2& other) const;

	float AngleTo(const Vector2& other) const;
	float Dot(const Vector2& other) const;

	static Vector2 FromAngle(float radians, float length = 1.0f);
	static float Distance(const Vector2& a, const Vector2& b);

	// 入力：なし
	// 出力：DxLib標準の3Dベクトル構造体（VECTOR）
	// 設計ルール：自作の2D計算と、DxLibが内部で要求する3D描画API（VGet等）との橋渡しをキャストだけでシームレスに行うための暗黙型変換
	operator VECTOR() const
	{
		return VGet(x, y, 0.0f);
	}
};

inline Vector2 operator*(float scalar, const Vector2& v)
{
	return v * scalar;
}