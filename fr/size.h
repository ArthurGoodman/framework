#pragma once

#include <windows.h>

namespace fr {

class Size {
    int _width, _height;

public:
    Size();
    Size(int width, int height);

    int width() const;
    void setWidth(int width);

    int height() const;
    void setHeight(int height);

    Size operator+(const Size &size) const;
    Size operator-(const Size &size) const;
    Size operator*(int f) const;
    Size operator/(int f) const;
    Size operator*(double f) const;
    Size operator/(double f) const;

    SIZE toNative() const;
};
}
