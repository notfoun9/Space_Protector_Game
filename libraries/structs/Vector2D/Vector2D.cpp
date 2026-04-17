#include <Vector2D/Vector2D.hpp>

Vector2D::Vector2D(float x_, float y_) : x(x_), y(y_) {}

Vector2D& Vector2D::Add(const Vector2D& vec) noexcept {
    x += vec.x;
    y += vec.y;
    return *this;
}
Vector2D& Vector2D::Substract(const Vector2D& vec) noexcept {
    x -= vec.x;
    y -= vec.y;
    return *this;
}

Vector2D& Vector2D::operator+=(const Vector2D& rhs) {
    return Add(rhs);
}
Vector2D& Vector2D::operator-=(const Vector2D& rhs) {
    return Substract(rhs);
}
// Vector2D& Vector2D::Multiply(const Vector2D& vec) noexcept {
//     x *= vec.x;
//     y *= vec.y;
// }
// Vector2D& Vector2D::Divide(const Vector2D& vec) {
//     if (vec.x == 0 && vec.y == 0) {
//         #ifdef LOGS
//         std::cerr << "deviding by zero is not allowed";
//         #endif
//         throw("deviding by zero is not allowed");
//     }
//     x /= vec.x;
//     y /= vec.y;
// }

Vector2D operator+(const Vector2D& lhs, const Vector2D& rhs) noexcept {
    return Vector2D(lhs.x + rhs.x, lhs.y + rhs.y);
}
Vector2D operator-(const Vector2D& lhs, const Vector2D& rhs) noexcept {
    return Vector2D(lhs.x - rhs.x, lhs.y - rhs.y);
}

Vector2D operator*(const Vector2D& lhs, const float rhs) noexcept {
    return Vector2D(lhs.x * rhs, lhs.y * rhs);
}
