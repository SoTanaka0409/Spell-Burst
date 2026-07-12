#include "Vector2.h"
#include <cmath> // std::sqrt, std::atan2, std::cos, std::sin

Vector2::Vector2() : x(0.0f), y(0.0f) {}
Vector2::Vector2(float x, float y) : x(x), y(y) {}

Vector2 Vector2::operator+(const Vector2& other) const { return Vector2(x + other.x, y + other.y); }
Vector2 Vector2::operator-(const Vector2& other) const { return Vector2(x - other.x, y - other.y); }
Vector2 Vector2::operator*(float scalar) const { return Vector2(x * scalar, y * scalar); }

// ゼロチェックを外し、逆数（インバース）の掛け算にすることで高速化
Vector2 Vector2::operator/(float scalar) const {
    float inv = 1.0f / scalar;
    return Vector2(x * inv, y * inv);
}

Vector2& Vector2::operator+=(const Vector2& other) { x += other.x; y += other.y; return *this; }
Vector2& Vector2::operator-=(const Vector2& other) { x -= other.x; y -= other.y; return *this; }
Vector2& Vector2::operator*=(float scalar) { x *= scalar; y *= scalar; return *this; }

Vector2& Vector2::operator/=(float scalar) {
    float inv = 1.0f / scalar;
    x *= inv; y *= inv;
    return *this;
}

// 速度重視なら std::sqrt を使用
float Vector2::Magnitude() const { return std::sqrt(x * x + y * y); }
float Vector2::MagnitudeSq() const { return x * x + y * y; }

// 2重のゼロチェックを解消
Vector2 Vector2::Normalized() const {
    float mag = Magnitude();
    if (mag > 0.0f) {
        float invMag = 1.0f / mag;
        return Vector2(x * invMag, y * invMag);
    }
    return Vector2(0.0f, 0.0f);
}

void Vector2::Normalize() {
    float mag = Magnitude();
    if (mag > 0.0f) {
        float invMag = 1.0f / mag;
        x *= invMag;
        y *= invMag;
    }
}

float Vector2::DistanceTo(const Vector2& other) const { return (*this - other).Magnitude(); }
float Vector2::DistanceSqTo(const Vector2& other) const { return (*this - other).MagnitudeSq(); }

// 2つのベクトルの「なす角」にする場合
float Vector2::AngleTo(const Vector2& other) const {
    return std::atan2(x * other.y - y * other.x, Dot(other));
}

float Vector2::Dot(const Vector2& other) const { return x * other.x + y * other.y; }

Vector2 Vector2::FromAngle(float radians, float length) {
    return Vector2(std::cos(radians) * length, std::sin(radians) * length);
}

float Vector2::Distance(const Vector2& a, const Vector2& b) { return a.DistanceTo(b); }