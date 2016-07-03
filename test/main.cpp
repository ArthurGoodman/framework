#include "mainwindow.h"

int main(int argc, const char **argv) {
    Application app(argc, argv);

    MainWindow w;
    w.resize(800, 600);
    w.move(fr::Application::desktop()->rect().center() - w.rect().center());
    w.show();

    return app.run();
}
