#pragma once

#include <string>
#include <iomanip>
#include <sstream>
#include <cmath>

typedef unsigned char byte;
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long long ulong;

template <class T>
std::string toString(T t, int base = 10, int precision = 16) {
    std::ostringstream s;

    s << std::setbase(base) << std::setprecision(precision) << t;

    return s.str();
}

template <class T>
T fromString(const std::string &str) {
    std::istringstream s(str);

    T t;
    s >> t;

    return t;
}

template <>
inline double fromString<double>(const std::string &str) {
    if (str == "inf")
        return INFINITY;

    if (str == "nan")
        return NAN;

    std::istringstream s(str);

    double t;
    s >> t;

    return t;
}
