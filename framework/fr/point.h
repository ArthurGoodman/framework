#pragma once

namespace fr {

class Point {
    int _x, _y;

public:
    Point();
    Point(int x, int y);

    int x() const;
    int y() const;

    int &rx();
    int &ry();

    Point operator+(const Point &p) const;
    Point operator-(const Point &p) const;
    Point operator*(int f) const;
    Point operator/(int f) const;
};
}
