TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

CONFIG += c++11

#Windows Config.
win32 {
INCLUDEPATH += "C:\SDL2\i686-w64-mingw32\include"
LIBS += -L"C:\SDL2\i686-w64-mingw32\lib"

LIBS += -lmingw32       \
        -lSDL2main      \
        -lSDL2          \
        -lSDL2_ttf      \
        -lSDL2_image    \
        -static-libgcc
}

#Linux like config.
LIBS+= -lSDL2 \
       -lSDL2_image \
       -lSDL2_ttf

SOURCES += main.cpp \
    utils.cpp \
    pong.cpp \
    paddle.cpp \
    ball.cpp

HEADERS += \
    utils.hpp \
    pong.hpp \
    paddle.hpp \
    ball.hpp

