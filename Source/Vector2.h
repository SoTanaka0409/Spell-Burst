#pragma once
#include <cmath>
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"

// 2D座標や速度を扱うためのベクトル構造体
struct Vector2
{
	float x; // X座標またはX方向成分
	float y; // Y座標またはY方向成分

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

	float Magnitude() const;

	float MagnitudeSq() const;

	Vector2 Normalized() const;
	void Normalize();

	float DistanceTo(const Vector2& other) const;

	float DistanceSqTo(const Vector2& other) const;

	float AngleTo(const Vector2& other) const;
	float Dot(const Vector2& other) const;

	static Vector2 FromAngle(float radians, float length = 1.0f);
	static float Distance(const Vector2& a, const Vector2& b);

	operator VECTOR() const
	{
		return VGet(x, y, 0.0f);
	}
};

inline Vector2 operator*(float scalar, const Vector2& v)
{
	return v * scalar;
}