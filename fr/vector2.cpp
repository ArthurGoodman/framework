#include "vector2.h"

fr::Vector2::Vector2()
    : _x(0), _y(0) {
}

fr::Vector2::Vector2(double x, double y)
    : _x(x), _y(y) {
}

double fr::Vector2::x() const {
    return _x;
}

double fr::Vector2::y() const {
    return _y;
}

double &fr::Vector2::rx() {
    return _x;
}

double &fr::Vector2::ry() {
    return _y;
}

fr::Vector2 fr::Vector2::operator+(const Vector2 &v) const {
    return Vector2(_x + v._x, _y + v._y);
}

fr::Vector2 fr::Vector2::operator-(const Vector2 &v) const {
    return Vector2(_x - v._x, _y - v._y);
}

fr::Vector2 fr::Vector2::operator*(double f) const {
    return Vector2(_x * f, _y * f);
}

fr::Vector2 fr::Vector2::operator/(double f) const {
    return Vector2(_x / f, _y / f);
}
