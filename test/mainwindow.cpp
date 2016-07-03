#include "mainwindow.h"

#include <iostream>

MainWindow::MainWindow() {
}

void MainWindow::closeEvent() {
    Application::instance()->quit();
}

void MainWindow::keyPressEvent(KeyEvent *e) {
    switch (e->key()) {
    case VK_ESCAPE:
        close();
        break;

    case VK_F11:
        break;
    }
}
