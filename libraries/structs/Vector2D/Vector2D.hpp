#pragma once
#include <game/game.hpp>
#include <cmath>

struct Vector2D {
    Vector2D() = default;
    Vector2D(float x, float y);
    Vector2D(const Vector2D& rhs) = default;  
    Vector2D(Vector2D&& rhs) = default;
    ~Vector2D() = default;

    Vector2D& operator=(const Vector2D& rhs) = default;
    Vector2D& operator=(Vector2D&& rhs) = default;
    bool operator==(const Vector2D& rhs) const = default;
    bool operator!=(const Vector2D& rhs) const = default;

    Vector2D& operator+=(const Vector2D& rhs);
    Vector2D& operator-=(const Vector2D& rhs);

    Vector2D& Add(const Vector2D& vec) noexcept;
    Vector2D& Substract(const Vector2D& vec) noexcept;
    float Mod() { return std::sqrt(x * x + y * y); }

    friend Vector2D operator+(const Vector2D& lhs, const Vector2D& rhs) noexcept;
    friend Vector2D operator-(const Vector2D& lhs, const Vector2D& rhs) noexcept;
    friend Vector2D operator*(const Vector2D& lhs, const Vector2D& rhs) noexcept;
    friend Vector2D operator*(const Vector2D& lhs, const float rhs) noexcept;
    friend Vector2D operator/(const Vector2D& lhs, const Vector2D& rhs);

    float x = 0.0f;
    float y = 0.0f;
} ;
