#pragma once

namespace fr {

class Vector2 {
    double _x, _y;

public:
    Vector2();
    Vector2(double x, double y);

    double x() const;
    double y() const;

    double &rx();
    double &ry();

    Vector2 operator+(const Vector2 &v) const;
    Vector2 operator-(const Vector2 &v) const;
    Vector2 operator*(double f) const;
    Vector2 operator/(double f) const;
};
}
