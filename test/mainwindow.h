#pragma once

#include "fr.h"

class MainWindow : public Window {
public:
    MainWindow();

protected:
    void closeEvent();
    void keyPressEvent(KeyEvent *e);
    void paintEvent();
};
