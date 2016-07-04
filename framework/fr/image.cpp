#include "image.h"

#include <windows.h>

#include <iostream>

fr::Image::Image()
    : data(0), w(0), h(0) {
}

fr::Image::Image(int width, int height)
    : w(width), h(height) {
    data = new byte[rawSize()];
    std::fill((int *)data, (int *)(data + rawSize()), Color::bgra(0, 0, 0, 255));
}

fr::Image::Image(const Image &image)
    : w(image.w), h(image.h) {
    data = new byte[image.rawSize()];
    std::copy(image.data, image.data + image.rawSize(), data);
}

fr::Image::Image(Image &&image)
    : data(image.data), w(image.w), h(image.h) {
    image.data = 0;
    image.w = 0;
    image.h = 0;
}

fr::Image::~Image() {
    delete[] data;
}

fr::Image &fr::Image::operator=(const Image &image) {
    delete[] data;

    data = new byte[image.rawSize()];
    std::copy(image.data, image.data + image.rawSize(), data);

    w = image.w;
    h = image.h;

    return *this;
}

fr::Image &fr::Image::operator=(Image &&image) {
    delete[] data;

    data = image.data;

    w = image.w;
    h = image.h;

    image.data = 0;
    image.w = 0;
    image.h = 0;

    return *this;
}

byte *fr::Image::bits() const {
    return data;
}

byte *fr::Image::at(int x, int y) const {
    return &data[y * w * channels + x * channels];
}

void fr::Image::save(const std::string &fileName) const {
    BmpHeader bmpHeader;
    DibHeader dibHeader;

    setupHeaders(bmpHeader, dibHeader);

    std::ofstream stream(fileName, std::ios::binary);
    stream.write((char *)&bmpHeader, sizeof(bmpHeader));
    stream.write((char *)&dibHeader, sizeof(dibHeader));

    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
            for (int c = 0; c < channels; c++)
                stream.write((char *)&at(x, y)[c], 1);

    stream.close();
}

void fr::Image::fill(int rgba) {
    std::fill((int *)data, (int *)(data + rawSize()), Color(rgba).bgra());
}

void fr::Image::fill(const Color &color) {
    fill(color.rgba());
}

int fr::Image::getPixel(int x, int y) const {
    if (x >= 0 && x < w && y >= 0 && y < h)
        return Color::fromBgra(*(int *)at(x, y)).rgba();

    return 0;
}

void fr::Image::setPixel(int x, int y, int rgba) {
    if (x >= 0 && x < w && y >= 0 && y < h)
        *(int *)at(x, y) = Color(rgba).bgra();
}

void fr::Image::setPixel(int x, int y, const Color &color) {
    Canvas::setPixel(x, y, color);
}

int fr::Image::width() const {
    return w;
}

int fr::Image::height() const {
    return h;
}

int fr::Image::rawSize() const {
    return channels * w * h;
}

void fr::Image::setupHeaders(BmpHeader &bmpHeader, DibHeader &dibHeader) const {
    dibHeader.width = w;
    dibHeader.height = -h;
    dibHeader.rawSize = rawSize();
    bmpHeader.size = bmpHeader.offset + dibHeader.rawSize;

    std::fill(dibHeader.colorSpaceEndpoints, dibHeader.colorSpaceEndpoints + 9, 0);
}
