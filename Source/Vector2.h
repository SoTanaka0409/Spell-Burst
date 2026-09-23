#pragma once
#include <cmath>
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"

/// @brief 2D座標や速度を扱うためのベクトル構造体
struct Vector2
{
	float x; ///< X座標またはX方向成分
	float y; ///< Y座標またはY方向成分

	/// @brief ゼロベクトルを生成する
	Vector2();

	/// @brief 指定成分でベクトルを生成する
	/// @param x X成分
	/// @param y Y成分
	Vector2(float x, float y);

	/// @brief ベクトル同士を加算する
	/// @param other 加算するベクトル
	/// @return Vector2 加算結果
	Vector2 operator+(const Vector2& other) const;

	/// @brief ベクトル同士を減算する
	/// @param other 減算するベクトル
	/// @return Vector2 減算結果
	Vector2 operator-(const Vector2& other) const;

	/// @brief ベクトルにスカラーを乗算する
	/// @param scalar 乗算する値
	/// @return Vector2 乗算結果
	Vector2 operator*(float scalar) const;

	/// @brief ベクトルをスカラーで除算する
	/// @param scalar 除算する値
	/// @return Vector2 除算結果
	Vector2 operator/(float scalar) const;

	/// @brief ベクトルを加算代入する
	/// @param other 加算するベクトル
	/// @return Vector2& 自身の参照
	Vector2& operator+=(const Vector2& other);

	/// @brief ベクトルを減算代入する
	/// @param other 減算するベクトル
	/// @return Vector2& 自身の参照
	Vector2& operator-=(const Vector2& other);

	/// @brief スカラーを乗算代入する
	/// @param scalar 乗算する値
	/// @return Vector2& 自身の参照
	Vector2& operator*=(float scalar);

	/// @brief スカラーを除算代入する
	/// @param scalar 除算する値
	/// @return Vector2& 自身の参照
	Vector2& operator/=(float scalar);

	/// @brief ベクトルの長さを取得する
	/// @return float 長さ
	float Magnitude() const;

	/// @brief ベクトルの長さの二乗を取得する
	/// @return float 長さの二乗
	float MagnitudeSq() const;

	/// @brief 正規化したベクトルを取得する
	/// @return Vector2 正規化後のベクトル
	Vector2 Normalized() const;

	/// @brief 自身を正規化する
	void Normalize();

	/// @brief 他ベクトルとの距離を取得する
	/// @param other 比較対象のベクトル
	/// @return float 距離
	float DistanceTo(const Vector2& other) const;

	/// @brief 他ベクトルとの距離の二乗を取得する
	/// @param other 比較対象のベクトル
	/// @return float 距離の二乗
	float DistanceSqTo(const Vector2& other) const;

	/// @brief 他ベクトルへの角度を取得する
	/// @param other 比較対象のベクトル
	/// @return float 角度（ラジアン）
	float AngleTo(const Vector2& other) const;

	/// @brief 内積を取得する
	/// @param other 比較対象のベクトル
	/// @return float 内積
	float Dot(const Vector2& other) const;

	/// @brief 角度と長さからベクトルを生成する
	/// @param radians 角度（ラジアン）
	/// @param length 長さ
	/// @return Vector2 生成されたベクトル
	static Vector2 FromAngle(float radians, float length = 1.0f);

	/// @brief 2点間の距離を取得する
	/// @param a 点A
	/// @param b 点B
	/// @return float 距離
	static float Distance(const Vector2& a, const Vector2& b);

	/// @brief DxLibのVECTORへ変換する
	/// @return VECTOR DxLib用ベクトル
	operator VECTOR() const
	{
		return VGet(x, y, 0.0f);
	}
};

/// @brief スカラーとベクトルを乗算する
/// @param scalar 乗算する値
/// @param v 対象ベクトル
/// @return Vector2 乗算結果
inline Vector2 operator*(float scalar, const Vector2& v)
{
	return v * scalar;
}