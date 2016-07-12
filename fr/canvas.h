#pragma once

#include <windef.h>

#include "size.h"
#include "color.h"

namespace fr {

class Canvas {
public:
    virtual ~Canvas();

    virtual HDC begin();
    virtual void end();

    virtual int getPixel(int x, int y) const = 0;
    virtual void setPixel(int x, int y, int rgba) = 0;

    virtual void setPixel(int x, int y, const Color &color);

    virtual int width() const = 0;
    virtual int height() const = 0;

    Size size() const;
};
}
