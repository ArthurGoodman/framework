TEMPLATE = app
CONFIG += windows c++11
CONFIG -= app_bundle qt

LIBS += -L../framework/release -lframework -lgdi32

PRE_TARGETDEPS += ../framework/release/libframework.a

INCLUDEPATH += \
    ../framework

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h
