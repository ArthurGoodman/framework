TEMPLATE = app
CONFIG += windows c++11
CONFIG -= app_bundle qt

LIBS += -L../release -lframework -lgdi32 -lgdiplus
INCLUDEPATH += ..

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h
