#pragma once

#include <windows.h>

#include "common.h"

namespace fr {

class Color {
    byte r, g, b, a;

public:
    static int rgba(byte r, byte g, byte b, byte a);
    static int bgra(byte b, byte g, byte r, byte a);
    static int rgb(byte r, byte g, byte b);

    static Color fromBgra(int bgra);

    static byte red(int rgba);
    static byte green(int rgba);
    static byte blue(int rgba);
    static byte alpha(int rgba);

    Color();
    Color(byte r, byte g, byte b, byte a = 255);
    explicit Color(int rgba);

    byte red() const;
    byte green() const;
    byte blue() const;
    byte alpha() const;

    int rgba() const;
    int bgra() const;

    COLORREF toNative() const;
};
}
