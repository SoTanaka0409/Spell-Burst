#include "Vector2.h"

#include "ObjectManager.h"
Vector2::Vector2() : x(0.0f), y(0.0f) {}
Vector2::Vector2(float x, float y) : x(x), y(y) {}

Vector2 Vector2::operator+(const Vector2& other) const {
    return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const {
    return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator*(float scalar) const {
    return Vector2(x * scalar, y * scalar);
}

Vector2 Vector2::operator/(float scalar) const {
    if (scalar != 0.0f) {
        return Vector2(x / scalar, y / scalar);
    }
    return Vector2(0.0f, 0.0f);
}

Vector2& Vector2::operator+=(const Vector2& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector2& Vector2::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

Vector2& Vector2::operator/=(float scalar) {
    if (scalar != 0.0f) {
        x /= scalar;
        y /= scalar;
    }
    return *this;
}

float Vector2::Magnitude() const {
    // std::hypot を使用して、オーバーフローを防ぎつつ簡潔にベクトルの長さを計算
    return std::hypot(x, y);
}

float Vector2::MagnitudeSq() const {
    return x * x + y * y;
}

Vector2 Vector2::Normalized() const {
    float mag = Magnitude();
    if (mag > 0.0f) {
        return *this / mag;
    }
    return Vector2(0.0f, 0.0f);
}

void Vector2::Normalize() {
    float mag = Magnitude();
    if (mag > 0.0f) {
        *this /= mag;
    }
}

float Vector2::DistanceTo(const Vector2& other) const {
    return (*this - other).Magnitude();
}

float Vector2::DistanceSqTo(const Vector2& other) const {
    return (*this - other).MagnitudeSq();
}

float Vector2::AngleTo(const Vector2& other) const {
    return std::atan2(other.y - y, other.x - x);
}

float Vector2::Dot(const Vector2& other) const {
    return x * other.x + y * other.y;
}

Vector2 Vector2::FromAngle(float radians, float length) {
    return Vector2(std::cos(radians) * length, std::sin(radians) * length);
}

float Vector2::Distance(const Vector2& a, const Vector2& b) {
    return a.DistanceTo(b);
}
