#pragma once
#include <cmath>
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"

struct Vector2 {
    float x;
    float y;

    Vector2();
    Vector2(float x, float y);

    // Operator overloads
    Vector2 operator+(const Vector2& other) const;
    Vector2 operator-(const Vector2& other) const;
    Vector2 operator*(float scalar) const;
    Vector2 operator/(float scalar) const;

    Vector2& operator+=(const Vector2& other);
    Vector2& operator-=(const Vector2& other);
    Vector2& operator*=(float scalar);
    Vector2& operator/=(float scalar);

    // Utility methods
    float Magnitude() const;
    float MagnitudeSq() const; // Squared magnitude (faster)
    Vector2 Normalized() const;
    void Normalize();

    float DistanceTo(const Vector2& other) const;
    float DistanceSqTo(const Vector2& other) const;

    float AngleTo(const Vector2& other) const; // Returns angle in radians
    float Dot(const Vector2& other) const;

    // Static utilities
    static Vector2 FromAngle(float radians, float length = 1.0f);
    static float Distance(const Vector2& a, const Vector2& b);

    operator VECTOR() const {
        return VGet(x, y, 0.0f);
    }
};

// Global operator for scalar * Vector2
inline Vector2 operator*(float scalar, const Vector2& v) {
    return v * scalar;
}