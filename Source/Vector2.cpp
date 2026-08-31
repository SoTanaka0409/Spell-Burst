#include "Vector2.h"
#include <cmath>

Vector2::Vector2() : x(0.0f), y(0.0f) {}
Vector2::Vector2(float x, float y) : x(x), y(y) {}

Vector2 Vector2::operator+(const Vector2& other) const { return Vector2(x + other.x, y + other.y); }
Vector2 Vector2::operator-(const Vector2& other) const { return Vector2(x - other.x, y - other.y); }
Vector2 Vector2::operator*(float scalar) const { return Vector2(x * scalar, y * scalar); }

/// @brief 演算子処理を行う
/// @param scalar scalar の値
/// @return Vector2 戻り値
Vector2 Vector2::operator/(float scalar) const
{
	float inv = 1.0f / scalar;
	return Vector2(x * inv, y * inv);
}

Vector2& Vector2::operator+=(const Vector2& other) { x += other.x; y += other.y; return *this; }
Vector2& Vector2::operator-=(const Vector2& other) { x -= other.x; y -= other.y; return *this; }
Vector2& Vector2::operator*=(float scalar) { x *= scalar; y *= scalar; return *this; }

/// @brief 演算子処理を行う
/// @param scalar scalar の値
/// @return Vector2& 戻り値
Vector2& Vector2::operator/=(float scalar)
{
	float inv = 1.0f / scalar;
	x *= inv; y *= inv;
	return *this;
}

float Vector2::Magnitude() const { return std::sqrt(x * x + y * y); }
float Vector2::MagnitudeSq() const { return x * x + y * y; }

/// @brief Normalized を実行する
/// @return Vector2 戻り値
Vector2 Vector2::Normalized() const
{
	float mag = Magnitude();
	if (mag > 0.0f)
	{
		float invMag = 1.0f / mag;
		return Vector2(x * invMag, y * invMag);
	}
	return Vector2(0.0f, 0.0f);
}

/// @brief Normalize を実行する
void Vector2::Normalize()
{
	float mag = Magnitude();
	if (mag > 0.0f)
	{
		float invMag = 1.0f / mag;
		x *= invMag;
		y *= invMag;
	}
}

float Vector2::DistanceTo(const Vector2& other) const { return (*this - other).Magnitude(); }

float Vector2::DistanceSqTo(const Vector2& other) const { return (*this - other).MagnitudeSq(); }

/// @brief AngleTo を実行する
/// @param other other の値
/// @return float 戻り値
float Vector2::AngleTo(const Vector2& other) const
{
	return std::atan2(x * other.y - y * other.x, Dot(other));
}

float Vector2::Dot(const Vector2& other) const { return x * other.x + y * other.y; }

/// @brief FromAngle を実行する
/// @param radians radians の値
/// @param length length の値
/// @return Vector2 戻り値
Vector2 Vector2::FromAngle(float radians, float length)
{
	return Vector2(std::cos(radians) * length, std::sin(radians) * length);
}

float Vector2::Distance(const Vector2& a, const Vector2& b) { return a.DistanceTo(b); }
