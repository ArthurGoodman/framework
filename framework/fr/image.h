#pragma once

#include <windef.h>
#include <string>
#include <fstream>

#include "canvas.h"

namespace fr {

class Image : public Canvas {
#pragma pack(push, 1)
    struct BmpHeader {
        short id = 0x4d42;
        int size;
        int unused = 0;
        int offset = 122;
    };

    struct DibHeader {
        int size = 108;
        int width;
        int height;
        short planes = 1;
        short bits = 32;
        int pixelArrayCompression = 0;
        int rawSize;
        int horizontalPrintResolution = 2835;
        int verticalPrintResolution = 2835;
        int colorsInPallette = 0;
        int importantColors = 0;
        int redChannelBitMask = 0x00ff0000;
        int greenChannelBitMask = 0x0000ff00;
        int blueChannelBitMask = 0x000000ff;
        int alphaChannelBitMask = 0xff000000;
        int logicalColorSpace = 0x57696e20;
        int colorSpaceEndpoints[9];
        int redGamma = 0;
        int greenGamma = 0;
        int blueGamma = 0;
    };
#pragma pack(pop)

    const static int channels = 4;

    byte *data;
    int w, h;

public:
    Image();
    Image(int width, int height);
    Image(const Image &image);
    Image(Image &&image);
    ~Image();

    Image &operator=(const Image &image);
    Image &operator=(Image &&image);

    byte *bits() const;
    byte *at(int x, int y) const;

    void save(const std::string &fileName) const;

    void fill(int rgba);
    void fill(const Color &color);

    int getPixel(int x, int y) const;
    void setPixel(int x, int y, int rgba);
    void setPixel(int x, int y, const Color &color);

    int width() const;
    int height() const;

private:
    int rawSize() const;
    void setupHeaders(BmpHeader &bmpHeader, DibHeader &dibHeader) const;
};
}
