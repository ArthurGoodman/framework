#pragma once

namespace fr {

class Size {
    int _width, _height;

public:
    Size();
    Size(int width, int height);

    int width() const;
    int height() const;

    Size operator+(const Size &size) const;
    Size operator-(const Size &size) const;
    Size operator*(int f) const;
    Size operator/(int f) const;
};
}
