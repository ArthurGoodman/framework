#pragma once

#include <string>

namespace fr {

class Window;

class Application {
    static Application *application;

public:
    static Application *instance();

    static Window *desktop();

    Application(int argc, const char **argv);

    void exit(int code);
    void quit();

    std::string moduleFilePath();
    std::string moduleFileName();

    int run();
};
}
